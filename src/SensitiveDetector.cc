#include "SensitiveDetector.hh"
#include "DetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4ConversionUtils.hh"

#include <iostream>

// Constructor.
SensitiveDetector::SensitiveDetector(G4String SDuniqueName, int nx,
                                     G4double pixelSizeX, G4double pixelSizeY,
                                     G4int pixelX, G4int pixelY,
                                     G4int n_sdd_per_module, G4int n_modules) :
    G4VSensitiveDetector(SDuniqueName),
    hitsCollectionID(-1),
    numberOfCellsInX(nx),
    numberOfCellsInY(1)
{
    psizeX = pixelSizeX;
    psizeY = pixelSizeY;
    npixelX = pixelX;
    npixelY = pixelY;
    nsdd = n_sdd_per_module;
    nmod = n_modules;
	collectionName.insert(SDuniqueName);
	initArray();
}  


// Method for the array allocation
void SensitiveDetector::initArray()
{
    // Dynamic allocation of 2-D arrays
	// We use the sizeof() a pointer to ensure 32 and 64-bit portability
	CellID = (int **) std::calloc(numberOfCellsInX, sizeof(*CellID));
	for(int iRow=0; iRow < numberOfCellsInX; iRow++) { CellID[iRow] = (int *) std::calloc(numberOfCellsInY, sizeof(*CellID)); }
}



// Destructor
SensitiveDetector::~SensitiveDetector() {std::free(CellID);}	



void SensitiveDetector::Initialize(G4HCofThisEvent* hitsCollEvent) 
{
    // This method is called at each new event, and it gets the HCofThisEvents
    // for the event.
    hitsCollection = new DetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
    
    hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    hitsCollEvent->AddHitsCollection(hitsCollectionID, hitsCollection);
    
    // Initialize vector of cell hits
    for(int iRow=0; iRow < numberOfCellsInX; iRow++) { for(G4int iCol=0; iCol < numberOfCellsInY; iCol++) {CellID[iRow][iCol] = -1;} }
}


G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* ROhist) 
{
	// This method is called when a particle goes through a sensitive 
	// detector. It possibly creates a new hit, and add its to the collection.
	// It eventually returns a boolean value. 
	// The arguments it gets are the G4Step and the G4TouchableHistory.
	//
	// The touchable history that we get in this method contains the full information about the 
	// genealogy of the current volume in the read-out geometry. One can use the touchable to 
	// access the information on the position/rotation of a given volume.

//	if(!ROhist) return false;

    // Retrieve the energy deposited from the step
    G4double energyDeposit = step -> GetTotalEnergyDeposit();
    
    G4double energy_threshold = 0.05 *keV;
    if (energyDeposit < energy_threshold) return false;

	G4Track* track = step -> GetTrack();
	G4double globaltime = track -> GetGlobalTime();

	// debug code
		//G4StepPoint* point1 = step->GetPreStepPoint();
		//const G4VProcess* aProcess1 = point1->GetProcessDefinedStep();
		//G4cout << aProcess1->GetProcessName() << G4endl;
		//G4StepPoint* point2 = step->GetPostStepPoint();
		//const G4VProcess* aProcess2 = point2->GetProcessDefinedStep();
		//G4cout << aProcess2->GetProcessName() << G4endl;
		
	// Get the interaction pixel
    G4int replicaNumber = track -> GetVolume() -> GetCopyNo();
	
    G4int moduleID;

    G4String motherName = track -> GetTouchable() ->GetVolume(1)->GetName();
    
    // Get the module ID from the mother physical volume name string
    G4ConversionUtils::Convert(motherName.remove(0,8).remove(2,5), moduleID);

    
    // Get translation of the SDD wrt module frame of reference
    G4ThreeVector volumeTranslation = track -> GetVolume()->GetTranslation();
    // Get translation of the module wrt absolute frame (from touchable, going upwards one level)
    G4ThreeVector motherVolumeTranslation = track -> GetTouchable() ->GetVolume(1) -> GetTranslation();
    // Get rotation of the module wrt absolute frame
    G4RotationMatrix* rotationMatrix = track -> GetTouchable() ->GetVolume(1) -> GetRotation();
    G4double angle;
    G4ThreeVector axis;
    rotationMatrix->getAngleAxis(angle,axis);
    // Get interaction position
    G4ThreeVector interactionPosition = track -> GetPosition();

    
    
    // A bit of vector magic...(a few strange things with pointers, therefore to obtain direct matrix I have to invert twice)
    G4ThreeVector relativeInteractionPosition = (rotationMatrix->inverse().inverse()) * (interactionPosition-motherVolumeTranslation)-volumeTranslation;


    G4int row = 0;
    G4int col = 0;
    if (relativeInteractionPosition.y() <= 0) {row = 1;} // True only with 2 pixels in Y TODO: generalize
    
    
    // Sometimes (happens only with particles interacting at the very boundary of the SDD, afaik, don't know why)
    // volumeTranslation doesn't return the correct translation of the SDD wrt the module, therefore col goes above the meaningful boundaries.
    // Since it is a very small percentage of events, I'll reassign the col value.
    G4bool outOfBoundary = false;
    if (relativeInteractionPosition.x() < -psizeX*npixelX/2)
    {
        relativeInteractionPosition.setX(-psizeX*npixelX/2);
        outOfBoundary = true;
    }
    else if (relativeInteractionPosition.x() > psizeX*npixelX/2)
    {
        relativeInteractionPosition.setX(psizeX*(npixelX-1)/2);
        outOfBoundary = true;
    }
    
    col = (G4int) ((relativeInteractionPosition.x() + psizeX*npixelX/2)/psizeX);

    if(outOfBoundary)
    {
            G4cout << "*** DEBUG: Hit energy deposit: " << energyDeposit/keV << G4endl;
            G4cout << "*** DEBUG: replicaNumber: " << replicaNumber << G4endl;
            G4cout << "*** DEBUG: mother physical volume: " << motherName << G4endl;
            G4cout << "*** DEBUG: mother physical volume ID: " << moduleID << G4endl;
            G4cout << "*** DEBUG: ROTATION angle, axis: " << angle/deg << " " << axis/cm << G4endl;
            G4cout << "*** DEBUG: SDD translation wrt module: " << volumeTranslation/cm << G4endl;
            G4cout << "*** DEBUG: Module translation: " << motherVolumeTranslation/cm << G4endl;
            G4cout << "*** DEBUG: Absolute SDD translation: " << (volumeTranslation+motherVolumeTranslation)/cm << G4endl;
            G4cout << "*** DEBUG: interaction position: " << interactionPosition/cm << G4endl;
            G4cout << "*** DEBUG: Relative interaction position: " << relativeInteractionPosition/cm << G4endl;
            G4cout << "*** DEBUG: Row " << row << G4endl;
            G4cout << "*** DEBUG: Col " << col << G4endl;
    }
    if(col < 0){col = 0;}
    else if(col >= npixelX) {col = npixelX-1;}

    G4int address = col + row*npixelX + replicaNumber*(npixelX*npixelY) + moduleID*(npixelX*npixelY*nsdd);

	if(CellID[address][0]==-1) // if no energy depositions before in this cell
	{
		// Now we create a new hit object, corresponding to the cell, and fill it with values to be stored
		DetectorHit* hit = new DetectorHit();
		hit -> SetEnergyDeposit(energyDeposit);
		hit -> SetXID(col);
		hit -> SetYID(row);
        hit -> SetSDDID(replicaNumber);
        hit -> SetModuleID(moduleID);
		hit -> SetTime(globaltime);
		G4int icell = hitsCollection -> insert(hit);
		CellID[address][0] = icell - 1;
	} 
	else // if energy depositions before in this cell
	{
		(*hitsCollection)[CellID[address][0]] -> AddEnergyDeposit(energyDeposit);
		(*hitsCollection)[CellID[address][0]] -> SetTime(globaltime);
	}
	return true;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hitsCollEvent) 
{
	// Method called at the end of an event.
//	if(hitsCollectionID < 0) {
//		hitsCollectionID =
//		G4SDManager::GetSDMpointer() -> GetCollectionID(hitsCollection);
//	}
	// Finally, the hits collection just defined (with its ID and its hits)
	// is registered to the HCOfThisEvent of the current event. 
//	hitsCollEvent -> AddHitsCollection(hitsCollectionID, hitsCollection);
}
