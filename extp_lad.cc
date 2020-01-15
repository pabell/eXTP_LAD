#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "DetectorConstruction.hh"
#include "UserActionInitialization.hh"

#include "PhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "G4VUserPhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "UserRunAction.hh"
#include "UserEventAction.hh"




int main(int argc, char **argv)
{
//    G4Random::setTheEngine(new CLHEP::RanecuEngine);
//    G4Random::setTheSeed(time(0));
    
    // Construct the run manager
#ifdef G4MULTITHREADED
    G4MTRunManager * runManager = new G4MTRunManager;
//    runManager->SetNumberOfThreads(1);
#else
    G4RunManager * runManager = new G4RunManager;
#endif

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());

    // // User action initialization
    runManager->SetUserInitialization(new UserActionInitialization());
    
    // Initialize G4 kernel
    runManager->Initialize();

    
    G4bool gui = true;
	
    // Handling of Batch and Interactive mode
    G4UImanager* uiManager = G4UImanager::GetUIpointer();
    
    // Activation of atomic EM de-excitation processes
    uiManager->ApplyCommand("/run/initialize");
    uiManager->ApplyCommand("/process/em/deexcitation World true true true");
    uiManager->ApplyCommand("/process/em/fluo true");
    uiManager->ApplyCommand("/process/em/auger true");
    uiManager->ApplyCommand("/run/physicsModified");
    
    if (argc!=1) {
        // General settings for batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        // Initialize the Visualization Manager
#ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        // Execute visualization batch file
        uiManager->ApplyCommand("/control/execute visBatch.mac");
#endif
        if(argc==3){
            // If there are two batch files (e.g. a General Particle Source macro)
            // load this first
            G4String fileGPS = argv[2];
            uiManager->ApplyCommand(command+fileGPS);
            G4cout << "GPS macro file executed: " << fileGPS << G4endl;
        }
        else {
            // Default GPS
            uiManager->ApplyCommand("/gps/particle gamma");
            uiManager->ApplyCommand("/gps/energy 100 keV");
            uiManager->ApplyCommand("/gps/position     0.0  0.0 +50.0 cm");
            uiManager->ApplyCommand("/gps/direction    0.0  0.0 -1.0");
            uiManager->ApplyCommand("/gps/polarization 1.0  0.0  0.0");
        }
        // Execute batch file
        uiManager->ApplyCommand(command+fileName);
        G4cout << "Batch file executed: " << fileName << G4endl;
    }
    
    else {
        // Interactive mode: define visualization verbosities
        uiManager->ApplyCommand("/run/verbose 0");
        uiManager->ApplyCommand("/event/verbose 0");
        uiManager->ApplyCommand("/tracking/verbose 0");
        
        // Set defaults for General Particle Source generation
        uiManager->ApplyCommand("/gps/particle gamma");
        uiManager->ApplyCommand("/gps/energy 100 keV");
        uiManager->ApplyCommand("/gps/position     0.0  0.0 +50.0 cm");
        uiManager->ApplyCommand("/gps/direction    0.0  0.0 -1.0");
        uiManager->ApplyCommand("/gps/polarization 1.0  0.0  0.0");
        
        // Start a run
//        G4int numberOfEvents = 0;
//        runManager->BeamOn(numberOfEvents);
        
        // Initialize the Visualization Manager
#ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
#endif
        if (gui) {
#ifdef G4UI_USE
            G4UIExecutive* ui = new G4UIExecutive(argc, argv);
            uiManager->ApplyCommand("/control/execute visGUI.mac");
            ui->SessionStart();
            delete ui;
#endif
        }
        else {
            // Initialize the Terminal
            G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
            session = new G4UIterminal(new G4UItcsh);
#else
            session = new G4UIterminal();
#endif
            // Apply visualization macro
            uiManager->ApplyCommand("/control/execute vis.mac");
            // Session start
            session->SessionStart();
            delete session;
        }
        // Job termination
#ifdef G4VIS_USE
        delete visManager;
#endif
    }
 
	delete runManager;
	return 0;
}


