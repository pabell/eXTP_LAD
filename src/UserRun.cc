#include "UserRun.hh"

#include "G4SDManager.hh"
#include "DetectorHit.hh"
#include "G4Event.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UIcommand.hh"
#include "tls.hh"

#include "ConfigFile.hh"

#include "g4root.hh"

UserRun::UserRun()
{
    hitsCollectionIndexSDD = G4SDManager::GetSDMpointer()->GetCollectionID("SDD");
}

UserRun::~UserRun() {;}


void UserRun::RecordEvent(const G4Event* event)
{
	// This method specifies the actions that must be performed at the 
	// end of each event (e.g. retrieve information, score, clean up 
	// things, etc.)
	
	// The following line verifies that a valid hits collection has been 
	// found. If not, nothing happens.
	if(hitsCollectionIndexSDD < 0) return;
    
    G4double eventID = event -> GetEventID();
    
    // Now, get the HCofThisEvent: it contains all the hits collections
	// that have been defined.
	G4HCofThisEvent* HCE = event -> GetHCofThisEvent();
    
	// Retrieve the hit collections.
    DetectorHitsCollection* hitsCollectionSDD = 0;
    
	if(HCE) {
	    hitsCollectionSDD = (DetectorHitsCollection*)(HCE -> GetHC(hitsCollectionIndexSDD));
	    //G4cout << "*** DEBUG: hitsCollectionSDD pointer: " << hitsCollectionSDD << G4endl;
	}
    
    // If both hit collections are empty, nothing happens.
    int numberHitsSDD = 0;
    if(hitsCollectionSDD) {numberHitsSDD = hitsCollectionSDD -> entries();}
    if (numberHitsSDD == 0) return;

    
    
    // Get primary event informations
	G4double en_primary    = 0.*MeV;
	G4double x_primary     = 0.*cm;
	G4double y_primary     = 0.*cm;
	G4double z_primary     = 0.*cm;
	G4double theta_primary = 0.*deg;
	G4double phi_primary   = 0.*deg;
	G4int nVertex = event -> GetNumberOfPrimaryVertex();
	// G4cout << " *** DEBUG " << " nVertex " << nVertex << G4endl;
	for ( G4int j = 0; j < nVertex; j++) {
		G4int nPart =  event -> GetPrimaryVertex(j)->GetNumberOfParticle();
		//G4cout << " *** DEBUG " << " nPart " << nVertex << G4endl;
		for ( G4int i = 0; i < nPart; i++) {
			G4ThreeVector position = event -> GetPrimaryVertex(j) -> GetPosition();
			G4ThreeVector direction = event -> GetPrimaryVertex(j) -> GetPrimary(i) -> GetMomentum();
			G4double P = direction.mag();
			en_primary = event->GetPrimaryVertex(j)->GetPrimary(i)->GetMass();
			G4double E0 = event->GetPrimaryVertex(j)->GetPrimary(i)->GetG4code()->GetPDGMass();
			en_primary = std::sqrt(P*P+E0*E0);
			en_primary -= E0;
			direction = direction*(1./direction.mag());
			direction = -direction;  // reverse the direction
			phi_primary = direction.phi();
			if (phi_primary <0) phi_primary = phi_primary + twopi;
			theta_primary = direction.theta();
			x_primary=position.x();
			y_primary=position.y();
			z_primary=position.z();
			//G4cout << " *** DEBUG " << " position " << position << G4endl;
			//G4cout << " *** DEBUG " << " direction " << direction << G4endl;
			//G4cout << " *** DEBUG " << " P " << P << G4endl;
			//G4cout << " *** DEBUG " << " en_primary " << en_primary << G4endl;
			//G4cout << " *** DEBUG " << " x " << x_primary << G4endl;
			//G4cout << " *** DEBUG " << " y " << y_primary << G4endl;
			//G4cout << " *** DEBUG " << " z " << z_primary << G4endl;
			//G4cout << " *** DEBUG " << " Theta " << theta_primary/deg << G4endl;
			//G4cout << " *** DEBUG " << " Phi " << phi_primary/deg << G4endl;
		}
	}
    

    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Process SDD hits
    if(hitsCollectionSDD) {
//	    G4cout << "*** Debug: Got in hitsCollectionSDD: " << hitsCollectionSDD << G4endl;

		for(int i = 0; i < numberHitsSDD ; i++) {
			DetectorHit* ahit = (*hitsCollectionSDD)[i];
			G4double energyDeposit = ahit -> GetEnergyDeposit();
            G4int    xpixel    = ahit -> GetSDDXID();
		    G4int    ypixel    = ahit -> GetSDDYID();
			G4double lastStepGlobalTime = ahit -> GetTime();
            
			
            // Write energy deposit and pixel in the ROOT file
            analysisManager->FillNtupleDColumn(0, eventID);
            analysisManager->FillNtupleDColumn(1, energyDeposit/keV);
            analysisManager->FillNtupleDColumn(2, xpixel);
            analysisManager->FillNtupleDColumn(3, ypixel);
            analysisManager->FillNtupleDColumn(4, x_primary/cm);
            analysisManager->FillNtupleDColumn(5, y_primary/cm);
            analysisManager->FillNtupleDColumn(6, z_primary/cm);
            analysisManager->FillNtupleDColumn(7, theta_primary/deg);
            analysisManager->FillNtupleDColumn(8, phi_primary/deg);
            analysisManager->FillNtupleDColumn(9, en_primary/keV);
            analysisManager->FillNtupleDColumn(10, lastStepGlobalTime/ns);
            analysisManager->AddNtupleRow();
            

		}
	}

    
    
    
    // Record the event
    G4cout << "---> (Record Event) End of event: " << event -> GetEventID() << G4endl;
    G4Run::RecordEvent(event);
}

void UserRun::Merge(const G4Run* run)
{
    G4Run::Merge(run);
}
