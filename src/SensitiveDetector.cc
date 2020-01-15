#include "SensitiveDetector.hh"
#include "DetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include <iostream>

// Constructor.
SensitiveDetector::SensitiveDetector(G4String SDuniqueName, int nx, int ny) :
    G4VSensitiveDetector(SDuniqueName),
    hitsCollectionID(-1),
    numberOfCellsInX(nx),
    numberOfCellsInY(ny)
{
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
    
    if (energyDeposit == 0.) return false;
    
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
    G4int copyIDinX   =  replicaNumber % numberOfCellsInX;
    G4int copyIDinY   =  replicaNumber / numberOfCellsInX;
	
//    G4cout << "*** DEBUG: got here " << energyDeposit/keV << " replicaNumber " << replicaNumber << G4endl;
//    G4cout << "*** DEBUG: replicaNumber " << replicaNumber << "  x " << copyIDinX << " y " << copyIDinY << G4endl;

	if(CellID[copyIDinX][copyIDinY]==-1) // if no energy depositions before in this cell
	{
		// Now we create a new hit object, corresponding to the cell, and fill it with values to be stored
		DetectorHit* hit = new DetectorHit(copyIDinX, copyIDinY);
		hit -> SetEnergyDeposit(energyDeposit);
		hit -> SetSDDXID(copyIDinX);
		hit -> SetSDDYID(copyIDinY);
		hit -> SetTime(globaltime);
		G4int icell = hitsCollection -> insert(hit);
		CellID[copyIDinX][copyIDinY] = icell - 1;
	} 
	else // if energy depositions before in this cell
	{
		(*hitsCollection)[CellID[copyIDinX][copyIDinY]] -> AddEnergyDeposit(energyDeposit);
		(*hitsCollection)[CellID[copyIDinX][copyIDinY]] -> SetTime(globaltime);
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