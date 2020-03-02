#include "DetectorConstruction.hh"
#include "ModuleParameterisation.hh"
#include "SDDParameterisation.hh"

#include "SensitiveDetector.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4RegionStore.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4Polyhedra.hh"
#include "G4Trap.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Transform3D.hh"
#include "G4VPVParameterisation.hh"
#include "G4PVParameterised.hh"
#include "globals.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include <fstream>
#include <vector>
#include <string>

#include "ConfigFile.hh"

// Constructor 
DetectorConstruction::DetectorConstruction() 
:	experimentalHall_log(0),
    plateSdd_log(0),
	sdd_log(0), 
	plateColl_log(0),
	coll_log(0),
    thermalblanketA_log(0),
    thermalblanketB_log(0),
	plateDeadlayerA_log(0),
	deadlayerA_log(0),
	plateDeadlayerB_log(0),
	deadlayerB_log(0),
	plateDeadlayerC_log(0),
	deadlayerC_log(0),
	platePcbs_log(0),
	pcbs_log(0),
	platePcbA_log(0),
	pcbA_log(0),
	platePcbB_log(0),
	pcbB_log(0),
	platePcbC_log(0),
	pcbC_log(0),
	backshieldA_log(0),
	backshieldB_log(0),
	opticalbench_log(0),
	tower_log(0),
	servicemodule_log(0),
    solarpanel_log(0),
    opticalbenchcover_log(0),
    sunshade_log(0),
	sddParam(0),
	collParam(0),
	pcbsParam(0),
	pcbAParam(0),
	pcbBParam(0),
	pcbCParam(0),
	experimentalHall_phys(0),
    plateSdd00_phys(0),
    plateSdd01_phys(0),
    plateSdd02_phys(0),
    plateSdd03_phys(0),
	sdd_phys(0),
	plateColl00_phys(0),
    plateColl01_phys(0),
    plateColl02_phys(0),
    plateColl03_phys(0),
	coll_phys(0),
	thermalblanketA00_phys(0),
    thermalblanketA01_phys(0),
    thermalblanketA02_phys(0),
    thermalblanketA03_phys(0),
	thermalblanketB00_phys(0),
    thermalblanketB01_phys(0),
    thermalblanketB02_phys(0),
    thermalblanketB03_phys(0),
	plateDeadlayerA00_phys(0),
    plateDeadlayerA01_phys(0),
    plateDeadlayerA02_phys(0),
    plateDeadlayerA03_phys(0),
	deadlayerA_phys(0),
	plateDeadlayerB00_phys(0),
    plateDeadlayerB01_phys(0),
    plateDeadlayerB02_phys(0),
    plateDeadlayerB03_phys(0),
	deadlayerB_phys(0),
	plateDeadlayerC00_phys(0),
    plateDeadlayerC01_phys(0),
    plateDeadlayerC02_phys(0),
    plateDeadlayerC03_phys(0),
	deadlayerC_phys(0),
	platePcbs00_phys(0),
    platePcbs01_phys(0),
    platePcbs02_phys(0),
    platePcbs03_phys(0),
	pcbs_phys(0),
	platePcbA00_phys(0),
    platePcbA01_phys(0),
    platePcbA02_phys(0),
    platePcbA03_phys(0),
	pcbA_phys(0),
	platePcbB00_phys(0),
    platePcbB01_phys(0),
    platePcbB02_phys(0),
    platePcbB03_phys(0),
	pcbB_phys(0),
	platePcbC00_phys(0),
    platePcbC01_phys(0),
    platePcbC02_phys(0),
    platePcbC03_phys(0),
	pcbC_phys(0),
	backshieldA00_phys(0),
    backshieldA01_phys(0),
    backshieldA02_phys(0),
    backshieldA03_phys(0),
	backshieldB00_phys(0),
    backshieldB01_phys(0),
    backshieldB02_phys(0),
    backshieldB03_phys(0),
	opticalbench_phys(0),
	tower_phys(0),
	servicemodule_phys(0),
    solarpanelA_phys(0),
    solarpanelB_phys(0),
    opticalbenchcover_phys(0),
    sunshade_phys(0),
	defaultMaterial(0)
{
	// Size of the experimental hall
    worldSide         = 100.0 *m;

    // Define the frame numbers
    n_sdd_x = 4;
    n_sdd_y = 4;
    n_sdd_per_module = n_sdd_x*n_sdd_y;
    n_modules = 2;

	// Define the materials
	DefineMaterials();	

	// Define the parameters
	DefineParameters();
		
	// Print parameters
	PrintParameters();
	
;}		

// Destructor 
DetectorConstruction::~DetectorConstruction() { } 	

G4ThreeVector DetectorConstruction::moduleLocation(G4int moduleID)
{
    G4double xMod = 0*cm;
    G4double yMod = moduleID * 100*cm;
    G4double zMod = 0*cm;

    if(moduleID == 0)
    {
        xMod = 20*cm;
    }

    return G4ThreeVector(xMod, yMod, zMod);
}

G4RotationMatrix* DetectorConstruction::moduleRotation(G4int moduleID)
{
    G4RotationMatrix* moduleRot = new G4RotationMatrix;

    if(moduleID == 1)
    {
        moduleRot->rotateZ(90*deg);
    }
    
    return moduleRot;
}



// Definition of the parameters
void DetectorConstruction::DefineParameters()
{ 
		
	// Configuration file readout
	// Uses the ConfigFile class by Rick Wagner
	// *** NOTE: Parameter filename should not be hardcoded!
	ConfigFile config( "detector_params.inp" );
		
	// The default parameters are inserted as the third argument
	// of the readInto function.
	// Geometrical dimensions
	// Using a std::double variable as a pivot btv. ConfigFile and Geant doubles (with units)
	double read = 0.;
	int read_int = 0;
	config.readInto(read, "SDD_X", 10.864);
	G4double s_x = read *cm;
	config.readInto(read, "SDD_Y", 7.);
	G4double s_y = read *cm;
	config.readInto(read, "SDD_THICK", 450.);
	G4double s_thickness = read *um;
    
    config.readInto(read, "MODULEFRAME_X", 542.);
    G4double mf_x = read *mm;
    config.readInto(read, "MODULEFRAME_Y", 329.);
    G4double mf_y = read *mm;
    config.readInto(read, "INTERNALFRAME_X", 16.45);
    G4double if_x = read *mm;
    config.readInto(read, "INTERNALFRAME_Y", 9.);
    G4double if_y = read *mm;


    config.readInto(read, "COLL_THICK", 2.);
	G4double coll_thickness = read *mm;
    config.readInto(read, "THERMALBLANKET_A_THICK", 5.);
	G4double thermalblanketA_thickness = read *um;
	config.readInto(read, "THERMALBLANKET_B_THICK", 0.1);
	G4double thermalblanketB_thickness = read *um;
	config.readInto(read, "DEADLAYER_A_THICK", 1.);
	G4double deadlayerA_thickness = read *um;
	config.readInto(read, "DEADLAYER_B_THICK", 1.);
	G4double deadlayerB_thickness = read *um;
	config.readInto(read, "DEADLAYER_C_THICK", 1.);
	G4double deadlayerC_thickness = read *um;
	config.readInto(read, "PCBS_THICK", 100.);
	G4double pcbs_thickness = read *um;
	config.readInto(read, "PCB_A_THICK", 1.);
	G4double pcbA_thickness = read *mm;
	config.readInto(read, "PCB_B_THICK", 70.);
	G4double pcbB_thickness = read *um;
	config.readInto(read, "PCB_C_THICK", 1.);
	G4double pcbC_thickness = read *mm;
	config.readInto(read, "BACKSHIELD_A_THICK", 1.);
	G4double backshieldA_thickness = read *mm;
	config.readInto(read, "BACKSHIELD_B_THICK", 0.3);
	G4double backshieldB_thickness = read *mm;
	config.readInto(read, "OPTICALBENCH_SIDE", 90.);
	G4double ob_side= read *cm;
	config.readInto(read, "OPTICALBENCH_THICK", 18.);
	G4double ob_thickness= read *cm;
	config.readInto(read, "TOWER_HEIGHT", 255.);
	G4double t_height= read *cm;
	config.readInto(read, "TOWER_DIAMETER", 95.);
	G4double t_diameter = read *cm;
	config.readInto(read, "SERVICEMODULE_SIDE", 90.);
	G4double sm_side= read *cm;
	config.readInto(read, "SERVICEMODULE_THICK", 95.);
	G4double sm_thickness= read *cm;
    config.readInto(read, "SOLARPANEL_SIDE_X", 750.);
    G4double sp_sx = read *cm;
    config.readInto(read, "SOLARPANEL_SIDE_Y", 160.);
    G4double sp_sy= read *cm;
    config.readInto(read, "SOLARPANEL_THICK", 2.);
    G4double sp_thickness = read *cm;
    config.readInto(read, "OPTICALBCOVER_DIAMETER", 247.);
    G4double obc_diameter = read *cm;
    config.readInto(read, "OPTICALBCOVER_THICK", 3.);
    G4double obc_thick = read *cm;
    config.readInto(read, "SUNSHADE_SIDE_X", 615.);
    G4double snsh_sx = read *cm;
    config.readInto(read, "SUNSHADE_SIDE_Y", 320.);
    G4double snsh_sy= read *cm;
    config.readInto(read, "SUNSHADE_THICK", 2.);
    G4double snsh_thickness = read *cm;



	config.readInto(read, "BUS_DISTANCE", 2.6);
	G4double b_distance= read *m;
    config.readInto(read, "PIXEL_X", 112.);
    G4int xpix = (int) read;
    config.readInto(read, "PIXEL_Y", 2.);
    G4int ypix = (int) read;


	SetSDDSideX(s_x) ;
	SetSDDSideY(s_y) ;
	SetSDDThick(s_thickness) ;
    
    SetModuleframeX(mf_x);
    SetModuleframeY(mf_y);
    SetInternalframeX(if_x);
    SetInternalframeY(if_y);

	SetCollThick(coll_thickness) ;
	SetThermalblanketAThick(thermalblanketA_thickness) ;
	SetThermalblanketBThick(thermalblanketB_thickness) ;
	SetDeadlayerAThick(deadlayerA_thickness) ;
	SetDeadlayerBThick(deadlayerB_thickness) ;
	SetDeadlayerCThick(deadlayerC_thickness) ;
	SetPcbsThick(pcbs_thickness) ;
	SetPcbAThick(pcbA_thickness) ;
	SetPcbBThick(pcbB_thickness) ;
	SetPcbCThick(pcbC_thickness) ;
	SetBackshieldAThick(backshieldA_thickness) ;
	SetBackshieldBThick(backshieldB_thickness) ;
    SetOpticalbenchSide(ob_side);
    SetOpticalbenchThick(ob_thickness);
    SetTowerHeight(t_height) ;
    SetTowerDiameter(t_diameter) ;
    SetServicemoduleSide(sm_side);
    SetServicemoduleThick(sm_thickness);
    SetSolarPanelSideX(sp_sx);
    SetSolarPanelSideY(sp_sy);
    SetSolarPanelThick(sp_thickness);
    SetOpticalBenchCoverDiameter(obc_diameter);
    SetOpticalBenchCoverThick(obc_thick);
    SetSunshadeSideX(snsh_sx);
    SetSunshadeSideY(snsh_sy);
    SetSunshadeThick(snsh_thickness);
	SetBusDistance(b_distance) ;
    SetPixelX(xpix);
    SetPixelY(ypix);


	
	// Materials
	G4String readm;
	config.readInto<G4String>(readm, "SDD_MATERIAL", "G4_Si");
	SetSDDMaterial(readm);
	config.readInto<G4String>(readm, "COLL_MATERIAL", "EffectivePhillips3502Glass_oar70");
    SetCollMaterial(readm);
	config.readInto<G4String>(readm, "THERMALBLANKET_A_MATERIAL", "G4_KAPTON");
    SetThermalblanketAMaterial(readm);
	config.readInto<G4String>(readm, "THERMALBLANKET_B_MATERIAL", "G4_Al");
    SetThermalblanketBMaterial(readm);
	config.readInto<G4String>(readm, "DEADLAYER_A_MATERIAL", "G4_SILICON_DIOXIDE");
    SetDeadlayerAMaterial(readm);
	config.readInto<G4String>(readm, "DEADLAYER_B_MATERIAL", "G4_Al");
    SetDeadlayerBMaterial(readm);
	config.readInto<G4String>(readm, "DEADLAYER_C_MATERIAL", "G4_Si");
	SetDeadlayerCMaterial(readm);
	config.readInto<G4String>(readm, "PCB_S_MATERIAL", "G4_Al");
    SetPcbsMaterial(readm);
	config.readInto<G4String>(readm, "PCB_A_MATERIAL", "FR4");
    SetPcbAMaterial(readm);
	config.readInto<G4String>(readm, "PCB_B_MATERIAL", "G4_Cu");
    SetPcbBMaterial(readm);
	config.readInto<G4String>(readm, "PCB_C_MATERIAL", "FR4");
    SetPcbCMaterial(readm);
	config.readInto<G4String>(readm, "BACKSHIELD_A_MATERIAL", "G4_Al");
    SetBackshieldAMaterial(readm);
	config.readInto<G4String>(readm, "BACKSHIELD_B_MATERIAL", "G4_Pb");
    SetBackshieldBMaterial(readm);
    config.readInto<G4String>(readm, "MODULEFRAME_MATERIAL", "G4_Al");
    SetModuleframeMaterial(readm);
	config.readInto<G4String>(readm, "OPTICALBENCH_MATERIAL", "CarbonFiberReinforcedPlastic");
    SetOpticalbenchMaterial(readm);
	config.readInto<G4String>(readm, "TOWER_MATERIAL", "CarbonFiberReinforcedPlastic");
    SetTowerMaterial(readm);
	config.readInto<G4String>(readm, "SERVICEMODULE_MATERIAL", "EffectiveBusAluminiumSolid");
    SetServicemoduleMaterial(readm);
    config.readInto<G4String>(readm, "SOLARPANEL_MATERIAL", "EffectiveBusAluminiumSolid");
    SetSolarPanelMaterial(readm);
    config.readInto<G4String>(readm, "OPTICALBCOVER_MATERIAL", "EffectiveBusAluminiumSolid");
    SetOpticalBenchCoverMaterial(readm);
    config.readInto<G4String>(readm, "SUNSHADE_MATERIAL", "EffectiveBusAluminiumSolid");
    SetSunshadeMaterial(readm);


	// Booleans
	G4bool readb;
	config.readInto<G4bool>(readb, "FLAG_ACTIVATEBUS", true);
	SetFlagSatellitebus(readb);
	
}


// Definition of the materials
void DetectorConstruction::DefineMaterials()
{ 
	G4double a;			// Atomic mass
	G4double z;			// Atomic number
	G4double density;	// Density
	G4int nel;			// Number of elements in a compound
	G4int ncomponents;	// Number of components in a mixture
	G4double fractionmass;
    G4int natoms;

	// Elements
	G4Element*  H  = new G4Element("Hydrogen"  , "H" , z = 1. , a =  1.008*g/mole);
	G4Element*  He = new G4Element("Helium"    , "He", z = 2. , a =  4.003*g/mole);
    G4Element*  Li = new G4Element("Lithium"   , "Li", z = 3. , a =  6.941*g/mole);
	G4Element*  C  = new G4Element("Carbon"    , "C" , z = 6. , a =  12.01*g/mole);
	G4Element*  N  = new G4Element("Nitrogen"  , "N" , z = 7. , a =  14.01*g/mole);
	G4Element*  O  = new G4Element("Oxygen"    , "O" , z = 8. , a =  16.00*g/mole);
	G4Element*  Na = new G4Element("Sodium"    , "Na", z = 11., a =  22.99*g/mole);
	G4Element*  Al = new G4Element("Aluminium" , "Al", z = 13., a =  26.98*g/mole);
	G4Element*  Si = new G4Element("Silicon"   , "Si", z = 14., a =  28.08*g/mole);
	G4Element*  K  = new G4Element("Potassium" , "K" , z = 19., a =  39.10*g/mole);
	G4Element*  Ti = new G4Element("Titanium"  , "Ti", z = 22., a =  47.87*g/mole);
	G4Element*  Cu = new G4Element("Copper"    , "Cu", z = 29., a =  63.55*g/mole);
	G4Element*  As = new G4Element("Arsenic"   , "As", z = 33., a =  74.92*g/mole);
    G4Element*  Zr = new G4Element("Zirconium" , "Zr", z = 40., a =  91.22*g/mole);
	G4Element*  Mo = new G4Element("Molybdenum", "Mo", z = 42., a =  95.94*g/mole);
    G4Element*  Cs = new G4Element("Caesium"   , "Cs", z = 55., a = 132.90*g/mole);
    G4Element*  Ba = new G4Element("Barium"    , "Ba", z = 56., a = 137.33*g/mole);
	G4Element*  Ta = new G4Element("Tantalum"  , "Ta", z = 73., a = 180.94*g/mole);
	G4Element*  W  = new G4Element("Tungsten"  , "W" , z = 74., a = 183.84*g/mole);
	G4Element*  Pb = new G4Element("Lead"      , "Pb", z = 82., a = 207.20*g/mole);
	G4Element*  Bi = new G4Element("Bismuth"   , "Bi", z = 83., a = 208.98*g/mole);

	// Materials 
	// Vacuum
	G4Material* Vacuum = new G4Material("Vacuum", density = 1.e-25*g/cm3, nel = 1);
	Vacuum -> AddElement(H, 100*perCent);
    
    // From NIST database
    G4NistManager* man = G4NistManager::Instance();

    G4Material* G4_Si = man->FindOrBuildMaterial("G4_Si");
    G4Material* G4_Ti = man->FindOrBuildMaterial("G4_Ti");
    G4Material* G4_Al = man->FindOrBuildMaterial("G4_Al");
    G4Material* G4_Fe = man->FindOrBuildMaterial("G4_Fe");
    G4Material* G4_Cu = man->FindOrBuildMaterial("G4_Cu");
    G4Material* G4_Mo = man->FindOrBuildMaterial("G4_Mo");
    G4Material* G4_W = man->FindOrBuildMaterial("G4_W");
    G4Material* G4_Pb = man->FindOrBuildMaterial("G4_Pb");
    
    G4Material* G4_AIR = man->FindOrBuildMaterial("G4_AIR");
    G4Material* G4_KAPTON = man->FindOrBuildMaterial("G4_KAPTON");

    G4Material* G4_SILICON_DIOXIDE = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    G4Material* G4_LITHIUM_OXIDE = man->FindOrBuildMaterial("G4_LITHIUM_OXIDE");
    G4Material* G4_LEAD_OXIDE = man->FindOrBuildMaterial("G4_LEAD_OXIDE");
    G4Material* G4_SODIUM_MONOXIDE = man->FindOrBuildMaterial("G4_SODIUM_MONOXIDE");
    G4Material* G4_POTASSIUM_OXIDE = man->FindOrBuildMaterial("G4_POTASSIUM_OXIDE");
    G4Material* G4_ALUMINUM_OXIDE = man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");

    // Cesium Oxide
    G4Material* CesiumOxide = new G4Material("CesiumOxide", density = 4.65*g/cm3, nel = 2);
    CesiumOxide -> AddElement(Cs, natoms=2);
    CesiumOxide -> AddElement(O,  natoms=1);
    
    // Barium Oxide
    G4Material* BariumOxide = new G4Material("BariumOxide", density = 5.72*g/cm3, nel = 2);
    BariumOxide -> AddElement(Ba, natoms=1);
    BariumOxide -> AddElement(O,  natoms=1);
    
    // Zirconium Oxide
    G4Material* ZirconiumOxide = new G4Material("ZirconiumOxide", density = 5.72*g/cm3, nel = 2);
    ZirconiumOxide -> AddElement(Zr, natoms=1);
    ZirconiumOxide -> AddElement(O,  natoms=1);
    
    // Bismuth Oxide
    G4Material* BismuthOxide = new G4Material("BismuthOxide", density = 5.72*g/cm3, nel = 2);
    BismuthOxide -> AddElement(Ba, natoms=1);
    BismuthOxide -> AddElement(O,  natoms=1);
    

    
    // Effective Aluminium Solid
	G4Material* EffectiveAluminiumSolid = new G4Material("EffectiveAluminiumSolid", density = 0.81*g/cm3, nel = 1);
	EffectiveAluminiumSolid -> AddElement(Al, 100*perCent);
	
	// Effective Bus Aluminium Solid (volume service module = 1.254 m3, weight = 376.5 kg, therefore density if it were full of aluminium)
	G4Material* EffectiveBusAluminiumSolid = new G4Material("EffectiveBusAluminiumSolid", density = 0.3*g/cm3, nel = 1);
	EffectiveBusAluminiumSolid -> AddElement(Al, 100*perCent);

	// Effective Copper Solid
	G4Material* EffectiveCopperSolid = new G4Material("EffectiveCopperSolid", density = 2.68*g/cm3, nel = 1);
	EffectiveCopperSolid -> AddElement(Cu, 100*perCent);

	// Effective Lead Solid
	G4Material* EffectiveLeadSolid = new G4Material("EffectiveLeadSolid", density = 0.93*g/cm3, nel = 1);
	EffectiveLeadSolid -> AddElement(Pb, 100*perCent);

	// Effective Tantalum Collimator (OAR 70.2%)
	G4Material* EffectiveTantalumSolid = new G4Material("EffectiveTantalumSolid", density = 4.97*g/cm3, nel = 1);
	EffectiveTantalumSolid -> AddElement(Ta, 100*perCent);

	// Lead Glass (NIST composition, see G4_GLASS_LEAD material table)
	G4Material* LeadGlass = new G4Material("LeadGlass", density = 6.22*g/cm3, nel = 5);
	LeadGlass -> AddElement(O, 15.7*perCent);
	LeadGlass -> AddElement(Si, 8.0*perCent);
	LeadGlass -> AddElement(Ti, 0.8*perCent);
	LeadGlass -> AddElement(As, 0.3*perCent);
	LeadGlass -> AddElement(Pb, 75.2*perCent);

	// Effective (with open elements) Lead Glass (NIST composition, see G4_GLASS_LEAD material table)
	G4Material* EffectiveLeadGlass = new G4Material("EffectiveLeadGlass", density = 1.87*g/cm3, nel = 5);
	EffectiveLeadGlass -> AddElement(O, 15.7*perCent);
	EffectiveLeadGlass -> AddElement(Si, 8.0*perCent);
	EffectiveLeadGlass -> AddElement(Ti, 0.8*perCent);
	EffectiveLeadGlass -> AddElement(As, 0.3*perCent);
	EffectiveLeadGlass -> AddElement(Pb, 75.2*perCent);

	// Simplified Effective Lead Glass. 45% by weight PbO, OAR 70% (bulk density 3.813 g/cm3)
	G4Material* EffectiveLeadGlass_45_oar70 = new G4Material("EffectiveLeadGlass_45_oar70", density = 1.144*g/cm3, nel = 3);
	EffectiveLeadGlass_45_oar70 -> AddElement(O,  32.0*perCent);
	EffectiveLeadGlass_45_oar70 -> AddElement(Si, 26.0*perCent);
	EffectiveLeadGlass_45_oar70 -> AddElement(Pb, 42.0*perCent);

	// Effective Phillips 3502 Glass. OAR 60% (bulk density 3.3 g/cm3) [Ref: Fraser (1982) NIMA 195, 523]
	G4Material* EffectivePhillips3502Glass_oar60 = new G4Material("EffectivePhillips3502Glass_oar60", density = 1.32*g/cm3, nel = 6);
	EffectivePhillips3502Glass_oar60 -> AddElement(O,  natoms=82);
	EffectivePhillips3502Glass_oar60 -> AddElement(Si, natoms=30);
	EffectivePhillips3502Glass_oar60 -> AddElement(Na, natoms=5);
	EffectivePhillips3502Glass_oar60 -> AddElement(K,  natoms=7);
	EffectivePhillips3502Glass_oar60 -> AddElement(Bi, natoms=1);
	EffectivePhillips3502Glass_oar60 -> AddElement(Pb, natoms=5);

	// Effective Phillips 3502 Glass. OAR 70% (bulk density 3.3 g/cm3) [Ref: Fraser (1982) NIMA 195, 523]
	G4Material* EffectivePhillips3502Glass_oar70 = new G4Material("EffectivePhillips3502Glass_oar70", density = 0.99*g/cm3, nel = 6);
	EffectivePhillips3502Glass_oar70 -> AddElement(O,  natoms=82);
	EffectivePhillips3502Glass_oar70 -> AddElement(Si, natoms=30);
	EffectivePhillips3502Glass_oar70 -> AddElement(Na, natoms=5);
	EffectivePhillips3502Glass_oar70 -> AddElement(K,  natoms=7);
	EffectivePhillips3502Glass_oar70 -> AddElement(Bi, natoms=1);
	EffectivePhillips3502Glass_oar70 -> AddElement(Pb, natoms=5);

	// Effective Phillips 3502 Glass. OAR 80% (bulk density 3.3 g/cm3) [Ref: Fraser (1982) NIMA 195, 523]
	G4Material* EffectivePhillips3502Glass_oar80 = new G4Material("EffectivePhillips3502Glass_oar80", density = 0.66*g/cm3, nel = 6);
	EffectivePhillips3502Glass_oar80 -> AddElement(O,  natoms=82);
	EffectivePhillips3502Glass_oar80 -> AddElement(Si, natoms=30);
	EffectivePhillips3502Glass_oar80 -> AddElement(Na, natoms=5);
	EffectivePhillips3502Glass_oar80 -> AddElement(K,  natoms=7);
	EffectivePhillips3502Glass_oar80 -> AddElement(Bi, natoms=1);
	EffectivePhillips3502Glass_oar80 -> AddElement(Pb, natoms=5);
	
    // Hamamatsu Lead Glass OAR 0% (bulk density 3.9 g/cm3)
    G4Material* HamamatsuLeadGlass = new G4Material("HamamatsuLeadGlass", density = 3.9*g/cm3, ncomponents=10);
    HamamatsuLeadGlass -> AddMaterial(G4_SILICON_DIOXIDE, fractionmass=42*perCent);
    HamamatsuLeadGlass -> AddMaterial(G4_LEAD_OXIDE, fractionmass=43*perCent);
    HamamatsuLeadGlass -> AddMaterial(G4_LITHIUM_OXIDE, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(G4_SODIUM_MONOXIDE, fractionmass=2*perCent);
    HamamatsuLeadGlass -> AddMaterial(G4_POTASSIUM_OXIDE, fractionmass=3*perCent);
    HamamatsuLeadGlass -> AddMaterial(G4_ALUMINUM_OXIDE, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(CesiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(BariumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(ZirconiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass -> AddMaterial(BismuthOxide, fractionmass=3*perCent);


    // Hamamatsu Lead Glass OAR 70% (bulk density 3.9 g/cm3)
    G4Material* HamamatsuLeadGlass_oar70 = new G4Material("HamamatsuLeadGlass_oar70", density = 1.17*g/cm3, ncomponents=10);
    HamamatsuLeadGlass_oar70 -> AddMaterial(G4_SILICON_DIOXIDE, fractionmass=42*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(G4_LEAD_OXIDE, fractionmass=43*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(G4_LITHIUM_OXIDE, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(G4_SODIUM_MONOXIDE, fractionmass=2*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(G4_POTASSIUM_OXIDE, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(G4_ALUMINUM_OXIDE, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(CesiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(BariumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(ZirconiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(BismuthOxide, fractionmass=3*perCent);

    
    // Hamamatsu Lead Glass OAR 75% (bulk density 3.9 g/cm3)
    G4Material* HamamatsuLeadGlass_oar75 = new G4Material("HamamatsuLeadGlass_oar75", density = 0.975*g/cm3, ncomponents=10);
    HamamatsuLeadGlass_oar75 -> AddMaterial(G4_SILICON_DIOXIDE, fractionmass=42*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(G4_LEAD_OXIDE, fractionmass=43*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(G4_LITHIUM_OXIDE, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(G4_SODIUM_MONOXIDE, fractionmass=2*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(G4_POTASSIUM_OXIDE, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(G4_ALUMINUM_OXIDE, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(CesiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(BariumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(ZirconiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(BismuthOxide, fractionmass=3*perCent);

    
    // Carbon fiber reinforced plastic (CFRP)
    G4Material* CarbonFiberReinforcedPlastic = new G4Material("CarbonFiberReinforcedPlastic", density = 1.71*g/cm3, nel = 2);
    CarbonFiberReinforcedPlastic -> AddElement(C, natoms=1);
    CarbonFiberReinforcedPlastic -> AddElement(H, natoms=2);
    
    // Carbon fiber reinforced plastic (CFRP) with effective 10% density
    G4Material* EffectiveCarbonFiberReinforcedPlastic = new G4Material("EffectiveCarbonFiberReinforcedPlastic", density = 0.171*g/cm3, nel = 2);
    EffectiveCarbonFiberReinforcedPlastic -> AddElement(C, natoms=1);
    EffectiveCarbonFiberReinforcedPlastic -> AddElement(H, natoms=2);

	// Diglycidyl Ether of Bisphenol A (First compound of epoxy resin Epotek 301-1)
	G4Material* Epoxy_1 = new G4Material("Epoxy_1", density = 1.16*g/cm3, nel = 3);
	Epoxy_1 -> AddElement(C, natoms=19);
	Epoxy_1 -> AddElement(H, natoms=20);
	Epoxy_1 -> AddElement(O, natoms=4);
	
	// 1,4-Butanediol Diglycidyl Ether (Second compound of epoxy resin Epotek 301-1)
	G4Material* Epoxy_2 = new G4Material("Epoxy_2", density = 1.10*g/cm3, nel = 3);
	Epoxy_2 -> AddElement(C, natoms=10);
	Epoxy_2 -> AddElement(H, natoms=18);
	Epoxy_2 -> AddElement(O, natoms=4);

	// 1,6-Hexanediamine 2,2,4-trimetyl (Third compound of epoxy resin Epotek 301-1)
	G4Material* Epoxy_3 = new G4Material("Epoxy_3", density = 1.16*g/cm3, nel = 3);
	Epoxy_3 -> AddElement(C, natoms=9);
	Epoxy_3 -> AddElement(H, natoms=22);
	Epoxy_3 -> AddElement(N, natoms=2);

	// Epoxy resin Epotek 301-1
	G4Material* Epoxy_Resin = new G4Material("Epoxy_Resin", density = 1.19*g/cm3, ncomponents = 3);
	Epoxy_Resin -> AddMaterial(Epoxy_1, fractionmass=56*perCent);
	Epoxy_Resin -> AddMaterial(Epoxy_2, fractionmass=24*perCent);
	Epoxy_Resin -> AddMaterial(Epoxy_3, fractionmass=20*perCent);
	
	// FR4 PCB material
	G4Material* FR4 = new G4Material("FR4", density = 1.8*g/cm3, ncomponents=2);
	FR4 -> AddMaterial(G4_SILICON_DIOXIDE, fractionmass=60*perCent);
	FR4 -> AddMaterial(Epoxy_Resin,  fractionmass=40*perCent);
	

	// Effective dummy panel material
	G4Material* EffectiveDummyPanelSolid = new G4Material("EffectiveDummyPanelSolid", density = 1.0*g/cm3, ncomponents=2);
	EffectiveDummyPanelSolid -> AddMaterial(G4_Al, fractionmass=92.4*perCent);
	EffectiveDummyPanelSolid -> AddMaterial(G4_Pb,  fractionmass=7.6*perCent);


	// Default materials of the World: vacuum
	defaultMaterial  = Vacuum;
}



// Detector construction
G4VPhysicalVolume* DetectorConstruction::Construct()
{
	// Clean old geometry, if any
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();


	// 1. Experimental hall (world volume)
	// Solid
	G4Box* experimentalHall_box = new G4Box("experimentalHall_box",
									  		worldSide/2., worldSide/2., worldSide/2.);
	// Logical
	experimentalHall_log  = new G4LogicalVolume(experimentalHall_box,
	                                            defaultMaterial, "experimentalHall_log", 0, 0, 0);
	// Physical
	experimentalHall_phys = new G4PVPlacement(0,
											  G4ThreeVector(0,0,0),
											  experimentalHall_log,
											  "experimentalHall_phys",
											  0,
											  false,
											  0);

    // Calculate necessary quantities
    G4int n_sdd_total = n_sdd_per_module*n_modules;
    
    G4double spacing_sdd_x = (moduleframe_side_x - internalframe_side_x*2 - n_sdd_x*sdd_x) / (n_sdd_x-1);
    G4double spacing_sdd_y = (moduleframe_side_y - internalframe_side_y*2 - n_sdd_y*sdd_y) / (n_sdd_y-1);

    G4double plate_z = thermalblanketA_thick + thermalblanketB_thick + coll_thick + deadlayerA_thick + deadlayerB_thick + deadlayerC_thick
                        + sdd_thick + pcbs_thick + pcbA_thick + pcbB_thick + pcbC_thick + backshieldA_thick + backshieldB_thick;
    
    G4cout << "MODULE CONFIGURATION:" << G4endl;
    G4cout << "No. of SDDs per X side: "<< n_sdd_x << G4endl;
    G4cout << "No. of SDDs per Y side: "<< n_sdd_y << G4endl;
    G4cout << "No. of SDDs per module: "<< n_sdd_per_module << G4endl;
    G4cout << "No. of modules: "<< n_modules << G4endl;
    G4cout << "Total no. of SDDs: "<< n_sdd_total << G4endl;
    G4cout << G4endl;
    G4cout << "MODULE DIMENSIONS: " << G4endl;
    G4cout << "Module X side (mm): "<< moduleframe_side_x/mm << G4endl;
    G4cout << "Module Y side (mm): "<< moduleframe_side_y/mm << G4endl;
    G4cout << "Internal frame on X side (mm): "<< internalframe_side_x/mm << G4endl;
    G4cout << "Internal frame on Y side (mm): "<< internalframe_side_y/mm << G4endl;
    G4cout << "Spacing btw. SDDs on X side (mm): "<< spacing_sdd_x/mm << G4endl;
    G4cout << "Spacing btw. SDDs on Y side (mm): "<< spacing_sdd_y/mm << G4endl;
    G4cout << "Module thickness (mm): "<< plate_z/mm << G4endl;

    
    // 2. SDD
    // Solid
    G4double plateSdd_x = moduleframe_side_x;
    G4double plateSdd_y = moduleframe_side_y;
    G4double plateSdd_z = sdd_thick;
    
    G4Box* plateSdd_box = new G4Box("plateSdd_box",
                                    plateSdd_x/2., plateSdd_y/2., plateSdd_z/2.);
    
    // Logical
    plateSdd_log = new G4LogicalVolume(plateSdd_box,
                                       moduleframeMaterial, "plateSdd_log", 0, 0, 0);
    
    
    // Physical
    plateSdd00_phys = new G4PVPlacement(moduleRotation(0),
                                      moduleLocation(0),
                                      plateSdd_log,
                                      "plateSdd00_phys",
                                      experimentalHall_log,
                                      false,
                                      0);

    plateSdd01_phys = new G4PVPlacement(moduleRotation(1),
                                       moduleLocation(1),
                                       plateSdd_log,
                                       "plateSdd01_phys",
                                       experimentalHall_log,
                                       false,
                                       0);

    
	// Solid
	G4Box* sdd_box = new G4Box("SDD_box",
							   sdd_x/2., sdd_y/2., sdd_thick/2.);
	// Logical
	sdd_log = new G4LogicalVolume(sdd_box,
								  sddMaterial, "SDD_log", 0, 0, 0);
	// Physical
    sddParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));

	sdd_phys = new G4PVParameterised("sdd_phys",       		// their name
									 sdd_log,    	        // their logical volume
									 plateSdd_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
                                     16,    		// Number of chambers
									 sddParam);   		// The parametrisation


    
	// 3. Collimator
    G4double plateColl_x = moduleframe_side_x;
    G4double plateColl_y = moduleframe_side_y;
    G4double plateColl_z = coll_thick;
    
    G4Box* plateColl_box = new G4Box("plateColl_box",
                                     plateColl_x/2., plateColl_y/2., plateColl_z/2.);
    
    // Logical
    plateColl_log = new G4LogicalVolume(plateColl_box,
                                        moduleframeMaterial, "plateColl_log", 0, 0, 0);
    
    
    // Physical
    G4double coll_loc_z = sdd_thick/2. + deadlayerA_thick + deadlayerB_thick + deadlayerC_thick + coll_thick/2.;
    plateColl00_phys = new G4PVPlacement(moduleRotation(0),
                                        G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),coll_loc_z),
                                        plateColl_log,
                                        "plateColl00_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    
    plateColl01_phys = new G4PVPlacement(moduleRotation(1),
                                        G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),coll_loc_z),
                                        plateColl_log,
                                        "plateColl01_phys",
                                        experimentalHall_log,
                                        false,
                                        0);

    // Solid
    G4Box* coll_box = new G4Box("coll_box",
                                sdd_x/2., sdd_y/2., coll_thick/2.);
    // Logical
    coll_log = new G4LogicalVolume(coll_box,
                                   collMaterial, "coll_log", 0, 0, 0);
    // Physical
    collParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    coll_phys = new G4PVParameterised("coll_phys",               // their name
                                      coll_log,                // their logical volume
                                      plateColl_log,          // Mother logical volume
                                      kYAxis,                  // Are placed along this axis
                                      16,            // Number of chambers
                                      collParam);           // The parametrisation

									
    

	// 4. Thermal blanket
	// 4a. First layer
	// Solid
    G4double thermalblanketA_x = moduleframe_side_x;
    G4double thermalblanketA_y = moduleframe_side_y;
    G4double thermalblanketA_z = thermalblanketA_thick;
    
    G4Box* thermalblanketA_box = new G4Box("thermalblanketA_box",
                                     thermalblanketA_x/2., thermalblanketA_y/2., thermalblanketA_z/2.);
    
    // Logical
    thermalblanketA_log = new G4LogicalVolume(thermalblanketA_box,
                                        thermalblanketAMaterial, "thermalblanketA_log", 0, 0, 0);
    
    
    // Physical
    G4double thermalblanketA_loc_z = sdd_thick/2. + deadlayerA_thick + deadlayerB_thick + deadlayerC_thick + coll_thick + thermalblanketB_thick + thermalblanketA_thick/2.;
    thermalblanketA00_phys = new G4PVPlacement(moduleRotation(0),
                                        G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),thermalblanketA_loc_z),
                                        thermalblanketA_log,
                                        "thermalblanketA00_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    
    thermalblanketA01_phys = new G4PVPlacement(moduleRotation(1),
                                        G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),thermalblanketA_loc_z),
                                        thermalblanketA_log,
                                        "thermalblanketA01_phys",
                                        experimentalHall_log,
                                        false,
                                        0);

	// 4b. Second layer
	// Solid
    G4double thermalblanketB_x = moduleframe_side_x;
    G4double thermalblanketB_y = moduleframe_side_y;
    G4double thermalblanketB_z = thermalblanketB_thick;
    
    G4Box* thermalblanketB_box = new G4Box("thermalblanketB_box",
                                           thermalblanketB_x/2., thermalblanketB_y/2., thermalblanketB_z/2.);
    
    // Logical
    thermalblanketB_log = new G4LogicalVolume(thermalblanketB_box,
                                              thermalblanketBMaterial, "thermalblanketB_log", 0, 0, 0);
    
    
    // Physical
    G4double thermalblanketB_loc_z = sdd_thick/2. + deadlayerA_thick + deadlayerB_thick + deadlayerC_thick + coll_thick + thermalblanketB_thick/2.;
    thermalblanketB00_phys = new G4PVPlacement(moduleRotation(0),
                                              G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),thermalblanketB_loc_z),
                                              thermalblanketB_log,
                                              "thermalblanketB00_phys",
                                              experimentalHall_log,
                                              false,
                                              0);
    
    thermalblanketB01_phys = new G4PVPlacement(moduleRotation(1),
                                              G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),thermalblanketB_loc_z),
                                              thermalblanketB_log,
                                              "thermalblanketB01_phys",
                                              experimentalHall_log,
                                              false,
                                              0);


 
	// 5. Deadlayer A
    G4double plateDeadlayerA_x = moduleframe_side_x;
    G4double plateDeadlayerA_y = moduleframe_side_y;
    G4double plateDeadlayerA_z = deadlayerA_thick;
    
    G4Box* plateDeadlayerA_box = new G4Box("plateDeadlayerA_box",
                                           plateDeadlayerA_x/2., plateDeadlayerA_y/2., plateDeadlayerA_z/2.);
    
    // Logical
    plateDeadlayerA_log = new G4LogicalVolume(plateDeadlayerA_box,
                                              moduleframeMaterial, "plateDeadlayerA_log", 0, 0, 0);
    
    
    // Physical
    G4double deadlayerA_loc_z = sdd_thick/2. + deadlayerC_thick + deadlayerB_thick + deadlayerA_thick/2.;
    plateDeadlayerA00_phys = new G4PVPlacement(moduleRotation(0),
                                               G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    plateDeadlayerA01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    // Solid
    G4Box* deadlayerA_box = new G4Box("deadlayerA_box",
                                sdd_x/2., sdd_y/2., deadlayerA_thick/2.);
    // Logical
    deadlayerA_log = new G4LogicalVolume(deadlayerA_box,
                                   deadlayerAMaterial, "coll_log", 0, 0, 0);
    // Physical
    deadlayerAParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    deadlayerA_phys = new G4PVParameterised("deadlayerA_phys",      // their name
                                      deadlayerA_log,               // their logical volume
                                      plateDeadlayerA_log,          // Mother logical volume
                                      kYAxis,                       // Are placed along this axis
                                      16,                           // Number of chambers
                                      deadlayerAParam);             // The parametrisation

    // 6. Deadlayer B
    G4double plateDeadlayerB_x = moduleframe_side_x;
    G4double plateDeadlayerB_y = moduleframe_side_y;
    G4double plateDeadlayerB_z = deadlayerB_thick;
    
    G4Box* plateDeadlayerB_box = new G4Box("plateDeadlayerB_box",
                                           plateDeadlayerB_x/2., plateDeadlayerB_y/2., plateDeadlayerB_z/2.);
    
    // Logical
    plateDeadlayerB_log = new G4LogicalVolume(plateDeadlayerB_box,
                                              moduleframeMaterial, "plateDeadlayerB_log", 0, 0, 0);
    
    
    // Physical
    G4double deadlayerB_loc_z = sdd_thick/2. + deadlayerC_thick + deadlayerB_thick/2.;
    plateDeadlayerB00_phys = new G4PVPlacement(moduleRotation(0),
                                               G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    plateDeadlayerB01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    // Solid
    G4Box* deadlayerB_box = new G4Box("deadlayerB_box",
                                      sdd_x/2., sdd_y/2., deadlayerB_thick/2.);
    // Logical
    deadlayerB_log = new G4LogicalVolume(deadlayerB_box,
                                         deadlayerBMaterial, "coll_log", 0, 0, 0);
    // Physical
    deadlayerBParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    deadlayerB_phys = new G4PVParameterised("deadlayerB_phys",      // their name
                                            deadlayerB_log,               // their logical volume
                                            plateDeadlayerB_log,          // Mother logical volume
                                            kYAxis,                       // Are placed along this axis
                                            16,                           // Number of chambers
                                            deadlayerBParam);             // The parametrisation


    // 5. Deadlayer A
    G4double plateDeadlayerC_x = moduleframe_side_x;
    G4double plateDeadlayerC_y = moduleframe_side_y;
    G4double plateDeadlayerC_z = deadlayerC_thick;
    
    G4Box* plateDeadlayerC_box = new G4Box("plateDeadlayerC_box",
                                           plateDeadlayerC_x/2., plateDeadlayerC_y/2., plateDeadlayerC_z/2.);
    
    // Logical
    plateDeadlayerC_log = new G4LogicalVolume(plateDeadlayerC_box,
                                              moduleframeMaterial, "plateDeadlayerC_log", 0, 0, 0);
    
    
    // Physical
    G4double deadlayerC_loc_z = sdd_thick/2. + deadlayerC_thick/2.;
    plateDeadlayerC00_phys = new G4PVPlacement(moduleRotation(0),
                                               G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    plateDeadlayerC01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    // Solid
    G4Box* deadlayerC_box = new G4Box("deadlayerC_box",
                                      sdd_x/2., sdd_y/2., deadlayerC_thick/2.);
    // Logical
    deadlayerC_log = new G4LogicalVolume(deadlayerC_box,
                                         deadlayerCMaterial, "coll_log", 0, 0, 0);
    // Physical
    deadlayerCParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    deadlayerC_phys = new G4PVParameterised("deadlayerC_phys",      // their name
                                            deadlayerC_log,               // their logical volume
                                            plateDeadlayerC_log,          // Mother logical volume
                                            kYAxis,                       // Are placed along this axis
                                            16,                           // Number of chambers
                                            deadlayerCParam);             // The parametrisation

    // 8. PCB shielding layer
	G4double platePcbs_x = moduleframe_side_x;
	G4double platePcbs_y = moduleframe_side_y;
	G4double platePcbs_z = pcbs_thick;

	G4Box* platePcbs_box = new G4Box("platePcbs_box",
									platePcbs_x/2., platePcbs_y/2., platePcbs_z/2.);

	platePcbs_log = new G4LogicalVolume(platePcbs_box,
                                        moduleframeMaterial, "platePcbs_log", 0, 0, 0);
	G4double pcbs_loc_z = -(sdd_thick/2. + pcbs_thick/2.);
    
    platePcbs00_phys = new G4PVPlacement(moduleRotation(0),
                                         G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);


    // Solid
    G4Box* pcbs_box = new G4Box("pcbs_box",
                                sdd_x/2., sdd_y/2., pcbs_thick/2.);
    // Logical
    pcbs_log = new G4LogicalVolume(pcbs_box,
                                   pcbsMaterial, "pcbs_log", 0, 0, 0);
    // Physical
    pcbsParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    pcbs_phys = new G4PVParameterised("pcbs_phys",               // their name
                                      pcbs_log,                // their logical volume
                                      platePcbs_log,          // Mother logical volume
                                      kYAxis,                  // Are placed along this axis
                                      16,            // Number of chambers
                                      pcbsParam);           // The parametrisation


	// 9. PCB 1st layer (A)
	G4double platePcbA_x = moduleframe_side_x;
	G4double platePcbA_y = moduleframe_side_y;
	G4double platePcbA_z = pcbA_thick;

	G4Box* platePcbA_box = new G4Box("platePcbA_box",
									platePcbA_x/2., platePcbA_y/2., platePcbA_z/2.);

	platePcbA_log = new G4LogicalVolume(platePcbA_box,
									   moduleframeMaterial, "platePcbA_log", 0, 0, 0);

    G4double pcbA_loc_z = -(sdd_thick/2. + pcbs_thick + pcbA_thick/2.);
    platePcbA00_phys = new G4PVPlacement(moduleRotation(0),
                                         G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);

    platePcbA01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);

    // Solid
    G4Box* pcbA_box = new G4Box("pcbA_box",
                                sdd_x/2., sdd_y/2., pcbA_thick/2.);
    // Logical
    pcbA_log = new G4LogicalVolume(pcbA_box,
                                   pcbAMaterial, "pcbA_log", 0, 0, 0);
    // Physical
    pcbAParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    pcbA_phys = new G4PVParameterised("pcbA_phys",               // their name
                                      pcbA_log,                // their logical volume
                                      platePcbA_log,          // Mother logical volume
                                      kYAxis,                  // Are placed along this axis
                                      16,            // Number of chambers
                                      pcbAParam);           // The parametrisation

	// 10. PCB 2nd layer (B)
    G4double platePcbB_x = moduleframe_side_x;
    G4double platePcbB_y = moduleframe_side_y;
    G4double platePcbB_z = pcbB_thick;
    
    G4Box* platePcbB_box = new G4Box("platePcbB_box",
                                     platePcbB_x/2., platePcbB_y/2., platePcbB_z/2.);
    
    platePcbB_log = new G4LogicalVolume(platePcbB_box,
                                        moduleframeMaterial, "platePcbB_log", 0, 0, 0);
    
    G4double pcbB_loc_z = -(sdd_thick/2. + pcbs_thick + pcbA_thick + pcbB_thick/2.);
    platePcbB00_phys = new G4PVPlacement(moduleRotation(0),
                                         G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);

    
    // Solid
    G4Box* pcbB_box = new G4Box("pcbB_box",
                                sdd_x/2., sdd_y/2., pcbB_thick/2.);
    // Logical
    pcbB_log = new G4LogicalVolume(pcbB_box,
                                   pcbBMaterial, "pcbB_log", 0, 0, 0);
    // Physical
    pcbBParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    pcbB_phys = new G4PVParameterised("pcbB_phys",               // their name
                                      pcbB_log,                // their logical volume
                                      platePcbB_log,          // Mother logical volume
                                      kYAxis,                  // Are placed along this axis
                                      16,            // Number of chambers
                                      pcbBParam);           // The parametrisation

	// 11. PCB 3rd layer (C)
    G4double platePcbC_x = moduleframe_side_x;
    G4double platePcbC_y = moduleframe_side_y;
    G4double platePcbC_z = pcbC_thick;
    
    G4Box* platePcbC_box = new G4Box("platePcbC_box",
                                     platePcbC_x/2., platePcbC_y/2., platePcbC_z/2.);
    
    platePcbC_log = new G4LogicalVolume(platePcbC_box,
                                        moduleframeMaterial, "platePcbC_log", 0, 0, 0);
    
    G4double pcbC_loc_z = -(sdd_thick/2. + pcbs_thick + pcbA_thick + pcbB_thick + pcbC_thick/2.);
    platePcbC00_phys = new G4PVPlacement(moduleRotation(0),
                                         G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);

    
    // Solid
    G4Box* pcbC_box = new G4Box("pcbC_box",
                                sdd_x/2., sdd_y/2., pcbC_thick/2.);
    // Logical
    pcbC_log = new G4LogicalVolume(pcbC_box,
                                   pcbCMaterial, "pcbC_log", 0, 0, 0);
    // Physical
    pcbCParam = new SDDParameterisation(sdd_x, sdd_y, (sdd_x+spacing_sdd_x), (sdd_y+spacing_sdd_y));
    
    pcbC_phys = new G4PVParameterised("pcbC_phys",               // their name
                                      pcbC_log,                // their logical volume
                                      platePcbC_log,          // Mother logical volume
                                      kYAxis,                  // Are placed along this axis
                                      16,            // Number of chambers
                                      pcbCParam);           // The parametrisation

	
	// 12. Backshield A
    G4double backshieldA_x = moduleframe_side_x;
    G4double backshieldA_y = moduleframe_side_y;
    G4double backshieldA_z = backshieldA_thick;
    
    G4Box* backshieldA_box = new G4Box("backshieldA_box",
                                     backshieldA_x/2., backshieldA_y/2., backshieldA_z/2.);
    
    backshieldA_log = new G4LogicalVolume(backshieldA_box,
                                        backshieldAMaterial, "backshieldA_log", 0, 0, 0);
    G4double backshieldA_loc_z = -(sdd_thick/2. + pcbs_thick + pcbA_thick + pcbB_thick + pcbC_thick + backshieldA_thick/2.);
    
    backshieldA00_phys = new G4PVPlacement(moduleRotation(0),
                                         G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),backshieldA_loc_z),
                                         backshieldA_log,
                                         "backshieldA00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    backshieldA01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),backshieldA_loc_z),
                                         backshieldA_log,
                                         "backshieldA01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);

    // 13. Backshield B
    G4double backshieldB_x = moduleframe_side_x;
    G4double backshieldB_y = moduleframe_side_y;
    G4double backshieldB_z = backshieldB_thick;
    
    G4Box* backshieldB_box = new G4Box("backshieldB_box",
                                       backshieldB_x/2., backshieldB_y/2., backshieldB_z/2.);
    
    backshieldB_log = new G4LogicalVolume(backshieldB_box,
                                          backshieldBMaterial, "backshieldB_log", 0, 0, 0);
    G4double backshieldB_loc_z = -(sdd_thick/2. + pcbs_thick + pcbA_thick + pcbB_thick + pcbC_thick + backshieldA_thick + backshieldB_thick/2.);
    
    backshieldB00_phys = new G4PVPlacement(moduleRotation(0),
                                           G4ThreeVector(moduleLocation(0).x(), moduleLocation(0).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB00_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB01_phys = new G4PVPlacement(moduleRotation(1),
                                           G4ThreeVector(moduleLocation(1).x(), moduleLocation(1).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB01_phys",
                                           experimentalHall_log,
                                           false,
                                           0);


    
    
    
    
    // 14. SATELLITE BUS

	if (flag_satellitebus == true) {
		// a. Optical bench
		// Solid
	    const G4double Z[2]= {0*cm, -opticalbench_thick};
	    const G4double rInner[2]= {0*cm, 0*cm};
	    const G4double rOuter[2]= {opticalbench_side, opticalbench_side};
	    G4Polyhedra* opticalbench_Ext_Polyhedra = new G4Polyhedra("opticalbench_Ext_Polyhedra",
												0.*deg,
												360.*deg,
												6,
												2,
												Z, 
												rInner, 
												rOuter);
        
        G4Tubs* opticalbench_Int_Tubs = new G4Tubs("opticalbench_Int_Tubs",
                                                   0.,                        // inner radius
                                                   tower_diameter/2.,         // outer radius
                                                   opticalbench_thick,        // height
                                                   0.0 * deg, 360.0 * deg);   // segment angles

        G4VSolid* opticalbench_Boolean = new G4SubtractionSolid("opticalbench_Boolean", opticalbench_Ext_Polyhedra, opticalbench_Int_Tubs);
		// Logical
		opticalbench_log = new G4LogicalVolume(opticalbench_Boolean,
		                                       opticalbenchMaterial, "opticalbench_log", 0, 0, 0);
	
		// Physical
		G4double opticalbenchPos_x = bus_distance;
		G4double opticalbenchPos_y = 0*cm;
		G4double opticalbenchPos_z = 0*cm ;
//        G4RotationMatrix* opticalbenchRot = new G4RotationMatrix;
//        opticalbenchRot->rotateZ(22.5*deg);
		opticalbench_phys = new G4PVPlacement(0,
									          G4ThreeVector(opticalbenchPos_x, opticalbenchPos_y, opticalbenchPos_z),
									          opticalbench_log,
									          "opticalbench_phys", 
									          experimentalHall_log, 
									          false, 
									          0);
	
		// b. Tower (telescope tube)
		// Solid
	    G4double tower_wall = 1.5*cm;
		G4VSolid* tower_Tubs = new G4Tubs("tower_Tubs", 
										(tower_diameter-tower_wall)/2.,	 // inner radius 
										tower_diameter/2.,	     // outer radius 
										tower_height/2.,	             // height 
										0.0 * deg, 360.0 * deg); // segment angles
		// Logical
		tower_log = new G4LogicalVolume(tower_Tubs,
		                              towerMaterial, "tower_log", 0, 0, 0);
		// Physical
		G4double towerPos_x = bus_distance;
		G4double towerPos_y = 0*m;
		G4double towerPos_z = -(opticalbench_thick + tower_height/2.) ;
		tower_phys = new G4PVPlacement(0,
									  G4ThreeVector(towerPos_x, towerPos_y, towerPos_z),
									  tower_log,
									  "tower_phys", 
									  experimentalHall_log, 
									  false, 
									  0);
        
		// c. Service module (focal plane assembly)
		// Solid
	    const G4double Z_sm[2]= {0*cm, -servicemodule_thick};
	    const G4double rInner_sm[2]= {50*cm, 50*cm};
	    const G4double rOuter_sm[2]= {servicemodule_side*sqrt(3)/2., servicemodule_side*sqrt(3)/2.};
	    G4Polyhedra* servicemodule_Polyhedra = new G4Polyhedra("servicemodule_Polyhedra",
												0.*deg,
												360.*deg,
												6,
												2,
												Z_sm, 
												rInner_sm, 
												rOuter_sm);
		// Logical
		servicemodule_log = new G4LogicalVolume(servicemodule_Polyhedra,
		                                       servicemoduleMaterial, "servicemodule_log", 0, 0, 0);
	
		// Physical
		G4double servicemodulePos_x = bus_distance;
		G4double servicemodulePos_y = 0*cm;
		G4double servicemodulePos_z = -(opticalbench_thick + tower_height) ;
//        G4RotationMatrix* servicemoduleRot = new G4RotationMatrix;
//        servicemoduleRot->rotateZ(30*deg);
		servicemodule_phys = new G4PVPlacement(0,
									          G4ThreeVector(servicemodulePos_x, servicemodulePos_y, servicemodulePos_z),
									          servicemodule_log,
									          "servicemodule_phys", 
									          experimentalHall_log, 
									          false, 
									          0);
        
        // d. Solar panels
        // Solid
        G4Box* solarpanel_Box = new G4Box("solarpanel_Box", solarpanel_side_x/2., solarpanel_side_y/2., solarpanel_thick/2.);
        
        // Logical
        solarpanel_log = new G4LogicalVolume(solarpanel_Box,
                                           solarpanelMaterial, "solarpanel_log", 0, 0, 0);
        // Physical 1
        G4double solarpanelGap = 118.2 *cm;
        G4double solarpanelPos_x = bus_distance + tower_diameter/2 + solarpanelGap + solarpanel_side_x/2.;
        G4double solarpanelPos_y = 0.*cm;
        G4double solarpanelPos_z = - opticalbench_thick - tower_height/2.;
        G4RotationMatrix* solarpanelRot = new G4RotationMatrix;
        solarpanelRot->rotateX(90*deg);
        
        solarpanelA_phys = new G4PVPlacement(solarpanelRot,
                                          G4ThreeVector(solarpanelPos_x, solarpanelPos_y, solarpanelPos_z),
                                          solarpanel_log,
                                          "solarpanelA_phys",
                                          experimentalHall_log,
                                          false,
                                          0);

        // Physical 2
        solarpanelPos_x = bus_distance -tower_diameter/2 - solarpanelGap - solarpanel_side_x/2.;
        solarpanelB_phys = new G4PVPlacement(solarpanelRot,
                                          G4ThreeVector(solarpanelPos_x, solarpanelPos_y, solarpanelPos_z),
                                          solarpanel_log,
                                          "solarpanelB_phys",
                                          experimentalHall_log,
                                          false,
                                          0);

        
        // e. Optical bench cover
        // Solid
        G4VSolid* opticalBenchCover_Tubs = new G4Tubs("opticalBenchCover_Tubs",
                                          0.,     // inner radius
                                          opticalbenchcover_diameter/2.,         // outer radius
                                          opticalbenchcover_thick/2.,                 // height
                                          0.0 * deg, 360.0 * deg); // segment angles
        // Logical
        opticalbenchcover_log = new G4LogicalVolume(opticalBenchCover_Tubs,
                                        opticalbenchcoverMaterial, "opticalbenchcover_log", 0, 0, 0);
        // Physical
        G4double opticalbenchcoverPos_x = bus_distance;
        G4double opticalbenchcoverPos_y = opticalbench_side*sqrt(5)/2. + opticalbenchcover_thick;
        G4double opticalbenchcoverPos_z = opticalbenchcover_diameter/2. ;
        G4RotationMatrix* opticalbenchcoverRot = new G4RotationMatrix;
        opticalbenchcoverRot->rotateX(90*deg);
        opticalbenchcover_phys = new G4PVPlacement(opticalbenchcoverRot,
                                       G4ThreeVector(opticalbenchcoverPos_x, opticalbenchcoverPos_y, opticalbenchcoverPos_z),
                                       opticalbenchcover_log,
                                       "opticalbenchcover_phys",
                                       experimentalHall_log,
                                       false,
                                       0);

        // f. Sunshade
        // Solid
        G4Box* sunshade_Box = new G4Box("sunshade_Box", sunshade_side_x/2., sunshade_side_y/2., sunshade_thick/2.);
                                        
        // Logical
        sunshade_log = new G4LogicalVolume(sunshade_Box,
                                                    sunshadeMaterial, "sunshade_log", 0, 0, 0);
        // Physical
        G4double sunshadePos_x = bus_distance;
        G4double sunshadePos_y = opticalbench_side*sqrt(5)/2. + opticalbenchcover_thick + sunshade_thick;
        G4double sunshadePos_z = sunshade_side_y/2. - opticalbench_thick ;
        G4RotationMatrix* sunshadeRot = new G4RotationMatrix;
        sunshadeRot->rotateX(90*deg);
        sunshade_phys = new G4PVPlacement(sunshadeRot,
                                                   G4ThreeVector(sunshadePos_x, sunshadePos_y, sunshadePos_z),
                                                   sunshade_log,
                                                   "sunshade_phys",
                                                   experimentalHall_log,
                                                   false,
                                                   0);


	}




	// Set visualization attributes
	// RGB components
	G4Colour white   (1.0, 1.0, 1.0);
	G4Colour red     (1.0, 0.0, 0.0);
	G4Colour green   (0.0, 1.0, 0.0);
	G4Colour blue    (0.0, 0.0, 1.0);
	G4Colour yellow  (1.0, 1.0, 0.0);
	G4Colour magenta (1.0, 0.0, 1.0);
	G4Colour cyan    (0.0, 1.0, 1.0);

	experimentalHall_log -> SetVisAttributes(G4VisAttributes::Invisible);  

	G4VisAttributes* SDDVisAtt= new G4VisAttributes(yellow);
    sdd_log -> SetVisAttributes(SDDVisAtt);
    
    plateSdd_log        -> SetVisAttributes(white);
    plateColl_log       -> SetVisAttributes(G4VisAttributes::Invisible);
    plateDeadlayerA_log -> SetVisAttributes(G4VisAttributes::Invisible);
    plateDeadlayerB_log -> SetVisAttributes(G4VisAttributes::Invisible);
    plateDeadlayerC_log -> SetVisAttributes(G4VisAttributes::Invisible);
    platePcbA_log       -> SetVisAttributes(G4VisAttributes::Invisible);
    platePcbB_log       -> SetVisAttributes(G4VisAttributes::Invisible);
    platePcbC_log       -> SetVisAttributes(G4VisAttributes::Invisible);


	G4VisAttributes* CollimatorVisAtt= new G4VisAttributes(blue);
    coll_log  -> SetVisAttributes(CollimatorVisAtt);

    G4VisAttributes* ThermalBlanketVisAtt = new G4VisAttributes(magenta);
    thermalblanketA_log -> SetVisAttributes(ThermalBlanketVisAtt);
    thermalblanketB_log -> SetVisAttributes(ThermalBlanketVisAtt);
	
	
    deadlayerA_log -> SetVisAttributes(G4VisAttributes::Invisible);
    deadlayerB_log -> SetVisAttributes(G4VisAttributes::Invisible);
    deadlayerC_log -> SetVisAttributes(G4VisAttributes::Invisible);
    
    pcbs_log -> SetVisAttributes(G4VisAttributes::Invisible);
	
	G4VisAttributes* PCBAVisAtt= new G4VisAttributes(green);
    pcbA_log -> SetVisAttributes(PCBAVisAtt);
	
	G4VisAttributes* PCBBVisAtt= new G4VisAttributes(red);
    pcbB_log -> SetVisAttributes(PCBBVisAtt);
	
	G4VisAttributes* PCBCVisAtt= new G4VisAttributes(green);
    pcbC_log -> SetVisAttributes(PCBCVisAtt);
	
	G4VisAttributes* BackshieldAVisAtt= new G4VisAttributes(magenta);
    backshieldA_log -> SetVisAttributes(BackshieldAVisAtt);
	
	G4VisAttributes* BackshieldBVisAtt= new G4VisAttributes(green);
    backshieldB_log -> SetVisAttributes(BackshieldBVisAtt);
	

    
	if (flag_satellitebus == true) 
	{
		G4VisAttributes* OpticalbenchVisAtt= new G4VisAttributes(magenta);
		opticalbench_log -> SetVisAttributes(OpticalbenchVisAtt);
	
		G4VisAttributes* TowerVisAtt= new G4VisAttributes(red);
		tower_log -> SetVisAttributes(TowerVisAtt);
	
		G4VisAttributes* ServicemoduleVisAtt= new G4VisAttributes(magenta);
		servicemodule_log -> SetVisAttributes(ServicemoduleVisAtt);
        
        G4VisAttributes* SolarpanelVisAtt= new G4VisAttributes(cyan);
        solarpanel_log -> SetVisAttributes(SolarpanelVisAtt);

        G4VisAttributes* OpticalBenchCoverVisAtt= new G4VisAttributes(red);
        opticalbenchcover_log -> SetVisAttributes(OpticalBenchCoverVisAtt);

        G4VisAttributes* SunshadeVisAtt= new G4VisAttributes(white);
        sunshade_log -> SetVisAttributes(SunshadeVisAtt);

	}
	
	
    
	// The function must return the physical volume of the world
	return experimentalHall_phys;
	
}



void DetectorConstruction::ConstructSDandField()
{
    // Sensitive volume
    // So far, the detector created above is not yet a real detector: it is just
    // a geometrical object (with some attributes) placed within the world volume.
    // To make the volume a detector, which can record e.g. hits, one must
    // define a sensitive volume associated with it.
    // For this purpose, a SensitiveDetector object is instantiated.

    auto sdman = G4SDManager::GetSDMpointer(); // Mandatory since Geant v. 4.10.03

    // Pixelization for the readout with 0.97 mm x 35 mm size
    G4int total_addresses = pixel_x*pixel_y*n_sdd_per_module*n_modules;
    G4cout << "Total allocated addresses "<< total_addresses << G4endl;
    SensitiveDetector* sdd_SD = new SensitiveDetector("SDD", total_addresses,
                                                      sdd_x/pixel_x, sdd_y/pixel_y,
                                                      pixel_x, pixel_y,
                                                      n_sdd_per_module, n_modules);
    

    sdman->AddNewDetector(sdd_SD); // Mandatory since Geant v. 4.10.03
    SetSensitiveDetector(sdd_log, sdd_SD);
}



void DetectorConstruction::SetSDDMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) sddMaterial = pttoMaterial;
}

void DetectorConstruction::SetCollMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) collMaterial = pttoMaterial;
}

void DetectorConstruction::SetThermalblanketAMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) thermalblanketAMaterial = pttoMaterial;
}

void DetectorConstruction::SetThermalblanketBMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) thermalblanketBMaterial = pttoMaterial;
}


void DetectorConstruction::SetDeadlayerAMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) deadlayerAMaterial = pttoMaterial;
}

void DetectorConstruction::SetDeadlayerBMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) deadlayerBMaterial = pttoMaterial;
}

void DetectorConstruction::SetDeadlayerCMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) deadlayerCMaterial = pttoMaterial;
}

void DetectorConstruction::SetPcbsMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcbsMaterial = pttoMaterial;
}

void DetectorConstruction::SetPcbAMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcbAMaterial = pttoMaterial;
}

void DetectorConstruction::SetPcbBMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcbBMaterial = pttoMaterial;
}

void DetectorConstruction::SetPcbCMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcbCMaterial = pttoMaterial;
}

void DetectorConstruction::SetBackshieldAMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) backshieldAMaterial = pttoMaterial;
}

void DetectorConstruction::SetBackshieldBMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) backshieldBMaterial = pttoMaterial;
}

void DetectorConstruction::SetModuleframeMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) moduleframeMaterial = pttoMaterial;
}

void DetectorConstruction::SetOpticalbenchMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) opticalbenchMaterial = pttoMaterial;
}

void DetectorConstruction::SetTowerMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) towerMaterial = pttoMaterial;
}

void DetectorConstruction::SetServicemoduleMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) servicemoduleMaterial = pttoMaterial;
}

void DetectorConstruction::SetSolarPanelMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) solarpanelMaterial = pttoMaterial;
}

void DetectorConstruction::SetOpticalBenchCoverMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) opticalbenchcoverMaterial = pttoMaterial;
}

void DetectorConstruction::SetSunshadeMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) sunshadeMaterial = pttoMaterial;
}




// TODO: update
void DetectorConstruction::PrintParameters()
{
	G4cout  << "\n-----------------------------------------------------------------------------------\n"
			<< "          Geometrical and physical parameters: "
			<< "\n SDD Side X                     (cm) : " 	<< sdd_x/cm
			<< "\n SDD Side Y                     (cm) : " 	<< sdd_y/cm
			<< "\n SDD Thickness                  (um) : " 	<< sdd_thick/um
			<< "\n SDD material                        : " 	<< sddMaterial -> GetName() 
			<< "\n Collimator Thickness           (mm) : " 	<< coll_thick/mm
			<< "\n Collimator material                 : " 	<< collMaterial -> GetName() 
			<< "\n Thermal blanket A Thickness    (um) : " 	<< thermalblanketA_thick/um
			<< "\n Thermal blanket A material          : " 	<< thermalblanketAMaterial -> GetName()
			<< "\n Thermal blanket B Thickness    (um) : " 	<< thermalblanketB_thick/um
			<< "\n Thermal blanket B material          : " 	<< thermalblanketBMaterial -> GetName()
			<< "\n Dead layer A Thickness         (um) : " 	<< deadlayerA_thick/um
			<< "\n Dead layer A material               : " 	<< deadlayerAMaterial -> GetName()
			<< "\n Dead layer B Thickness         (um) : " 	<< deadlayerB_thick/um
			<< "\n Dead layer B material               : " 	<< deadlayerBMaterial -> GetName()
			<< "\n Dead layer C Thickness         (um) : " 	<< deadlayerC_thick/um
			<< "\n Dead layer C material               : " 	<< deadlayerCMaterial -> GetName()
			<< "\n PCB shielding layer Thickness  (um) : " 	<< pcbs_thick/um
			<< "\n PCB shielding layer material        : " 	<< pcbsMaterial -> GetName()
			<< "\n PCB layer A Thickness          (mm) : " 	<< pcbA_thick/mm
			<< "\n PCB layer A material                : " 	<< pcbAMaterial -> GetName()
			<< "\n PCB layer B Thickness          (um) : " 	<< pcbB_thick/um
			<< "\n PCB layer B material                : " 	<< pcbBMaterial -> GetName()
			<< "\n PCB layer C Thickness          (mm) : " 	<< pcbC_thick/mm
			<< "\n PCB layer C material                : " 	<< pcbCMaterial -> GetName()
			<< "\n Backshield A Thickness         (mm) : " 	<< backshieldA_thick/mm
			<< "\n Backshield A material               : " 	<< backshieldAMaterial -> GetName()
			<< "\n Backshield B Thickness         (mm) : " 	<< backshieldB_thick/mm
            << "\n Backshield B material               : " 	<< backshieldBMaterial -> GetName();
	G4cout  << "\n";
			if(flag_satellitebus == true) {
				G4cout  << "\n Bus enabled."
						<< "\n Optical bench Side             (cm) : " 	<< opticalbench_side/cm
						<< "\n Optical bench Thickness        (cm) : " 	<< opticalbench_thick/cm
						<< "\n Optical bench material              : " 	<< opticalbenchMaterial -> GetName()
						<< "\n Tower Diameter                 (cm) : " 	<< tower_diameter/cm
						<< "\n Tower Height                   (cm) : " 	<< tower_height/cm
						<< "\n Tower material                      : " 	<< towerMaterial -> GetName()
						<< "\n Service module Side            (cm) : " 	<< servicemodule_side/cm
						<< "\n Service module Thickness       (cm) : " 	<< servicemodule_thick/cm
						<< "\n Service module material             : " 	<< servicemoduleMaterial -> GetName()
						<< "\n Distance bus-panel             (m)  : " 	<< bus_distance/m;
		    	G4cout  << "\n";
			} else {
				G4cout 	<< "\n Bus disabled.\n";
			}
	G4cout  << "\n-----------------------------------------------------------------------------------\n";
}



void DetectorConstruction::UpdateGeometry()
{  
	G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
	G4RunManager::GetRunManager()->GeometryHasBeenModified();
}


