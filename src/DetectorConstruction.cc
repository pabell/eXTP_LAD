#include "DetectorConstruction.hh"
#include "ModuleParameterisation.hh"
#include "SDDParameterisation.hh"

#include "SensitiveDetector.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

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
	sdd_log(0), 
	plateColl_log(0),
	coll_log(0),
    thermalblanket1_log(0),
    thermalblanket2_log(0),
	plateCoating_log(0),
	coating_log(0),
	plateDeadlayer1_log(0),
	deadlayer1_log(0),
	plateDeadlayer2_log(0),
	deadlayer2_log(0),
	plateDeadlayer3_log(0),
	deadlayer3_log(0),
	platePcbs_log(0),
	pcbs_log(0),
	platePcb1_log(0),
	pcb1_log(0),
	platePcb2_log(0),
	pcb2_log(0),
	platePcb3_log(0),
	pcb3_log(0),
	plateBack1_log(0),
	back1_log(0),
	plateBack2_log(0),
	back2_log(0),	
	plateFrame_log(0),
	frame_log(0),
	sideframe1_log(0),
	sideframe2_log(0),
	opticalbench_log(0),
	tower_log(0),
	servicemodule_log(0),
//    solarpanel_log(0),
    opticalbenchcover_log(0),
    sunshade_log(0),
	sddParam(0),
	collParam(0),
	coatingParam(0),
	pcbsParam(0),
	pcb1Param(0),
	pcb2Param(0),
	pcb3Param(0),
	back1Param(0),
	back2Param(0),
	frameParam(0),
	experimentalHall_phys(0), 
	sdd_phys(0), 
	plateColl_phys(0),
	coll_phys(0),
	thermalblanket1_phys(0),
	thermalblanket2_phys(0),
	plateCoating_phys(0),
	coating_phys(0),
	plateDeadlayer1_phys(0),
	deadlayer1_phys(0),
	plateDeadlayer2_phys(0),
	deadlayer2_phys(0),
	plateDeadlayer3_phys(0),
	deadlayer3_phys(0),
	platePcbs_phys(0),
	pcbs_phys(0),
	platePcb1_phys(0),
	pcb1_phys(0),
	platePcb2_phys(0),
	pcb2_phys(0),
	platePcb3_phys(0),
	pcb3_phys(0),	
	plateBack1_phys(0),
	back1_phys(0),
	plateBack2_phys(0),
	back2_phys(0),
	plateFrame_phys(0),
	frame_phys(0),
	sideframe1_phys(0),
	sideframe2_phys(0),
	opticalbench_phys(0),
	tower_phys(0),
	servicemodule_phys(0),
    solarpanel1_phys(0),
    solarpanel2_phys(0),
    opticalbenchcover_phys(0),
    sunshade_phys(0),
	defaultMaterial(0)
{
	// Size of the experimental hall
    worldSide         = 100.0 *m;

	// Define the materials
	DefineMaterials();	

	// Define the parameters
	DefineParameters();
		
	// Print parameters
	PrintParameters();
	
;}		



// Destructor 
DetectorConstruction::~DetectorConstruction() { } 	



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
	config.readInto(read_int, "N_MOD_X", 28);
	G4int mArray_x = read_int;
	config.readInto(read_int, "N_MOD_Y", 12);
	G4int mArray_y = read_int;
	config.readInto(read, "COLL_THICK", 2.);
	G4double coll_thickness = read *mm;
	config.readInto(read, "THERMALB1_THICK", 5.);
	G4double thermalblanket1_thickness = read *um;
	config.readInto(read, "THERMALB2_THICK", 0.1);
	G4double thermalblanket2_thickness = read *um;
	config.readInto(read, "COATING_THICK", 5.);
	G4double coating_thickness = read *um;
	config.readInto(read, "DEADLAY1_THICK", 1.);
	G4double deadlayer1_thickness = read *um;
	config.readInto(read, "DEADLAY2_THICK", 1.);
	G4double deadlayer2_thickness = read *um;
	config.readInto(read, "DEADLAY3_THICK", 1.);
	G4double deadlayer3_thickness = read *um;
	config.readInto(read, "PCBS_THICK", 100.);
	G4double pcbs_thickness = read *um;
	config.readInto(read, "PCB1_THICK", 1.);
	G4double pcb1_thickness = read *mm;
	config.readInto(read, "PCB2_THICK", 70.);
	G4double pcb2_thickness = read *um;
	config.readInto(read, "PCB3_THICK", 1.);
	G4double pcb3_thickness = read *mm;
	config.readInto(read, "BACKSHIELD1_THICK", 1.);
	G4double backshield1_thickness = read *mm;
	config.readInto(read, "BACKSHIELD2_THICK", 200.);
	G4double backshield2_thickness = read *um;
	config.readInto(read, "FRAME_THICK", 1.);
	G4double frame_thickness = read *cm;
	config.readInto(read, "SIDEFRAME1_WIDTH", 2.);
	G4double sideframe1_w = read *mm;
	config.readInto(read, "SIDEFRAME2_WIDTH", 1.);
	G4double sideframe2_w = read *mm;
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
	SetModuleArrayX(mArray_x) ;
	SetModuleArrayY(mArray_y) ;
	SetCollThick(coll_thickness) ;
	SetThermalblanket1Thick(thermalblanket1_thickness) ;
	SetThermalblanket2Thick(thermalblanket2_thickness) ;	
	SetCoatingThick(coating_thickness) ;
	SetDeadlayer1Thick(deadlayer1_thickness) ;
	SetDeadlayer2Thick(deadlayer2_thickness) ;	
	SetDeadlayer3Thick(deadlayer3_thickness) ;
	SetPcbsThick(pcbs_thickness) ;
	SetPcb1Thick(pcb1_thickness) ;
	SetPcb2Thick(pcb2_thickness) ;
	SetPcb3Thick(pcb3_thickness) ;
	SetBack1Thick(backshield1_thickness) ;
	SetBack2Thick(backshield2_thickness) ;	
	SetFrameThick(frame_thickness) ;
	SetSideframe1Width(sideframe1_w) ;
	SetSideframe2Width(sideframe2_w) ;
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
	config.readInto<G4String>(readm, "SDD_MATERIAL", "SiliconSolid");
	SetSDDMaterial(readm);
	config.readInto<G4String>(readm, "COLL_MATERIAL", "EffectivePhillips3502Glass_oar70");
    SetCollMaterial(readm);
	config.readInto<G4String>(readm, "THERMALBLANKET1_MATERIAL", "Polymide");
    SetThermalblanket1Material(readm);
	config.readInto<G4String>(readm, "THERMALBLANKET2_MATERIAL", "AluminiumSolid");
    SetThermalblanket2Material(readm);
	config.readInto<G4String>(readm, "COATING_MATERIAL", "AluminiumSolid");
    SetCoatingMaterial(readm);
	config.readInto<G4String>(readm, "DEADLAYER1_MATERIAL", "SiliconOxide");
    SetDeadlayer1Material(readm);
	config.readInto<G4String>(readm, "DEADLAYER2_MATERIAL", "AluminiumSolid");
    SetDeadlayer2Material(readm);
	config.readInto<G4String>(readm, "DEADLAYER3_MATERIAL", "SiliconSolid");
	SetDeadlayer3Material(readm);
	config.readInto<G4String>(readm, "PCBS_MATERIAL", "AluminiumSolid");
    SetPcbsMaterial(readm);
	config.readInto<G4String>(readm, "PCB1_MATERIAL", "FR4");
    SetPcb1Material(readm);
	config.readInto<G4String>(readm, "PCB2_MATERIAL", "CopperSolid");
    SetPcb2Material(readm);
	config.readInto<G4String>(readm, "PCB3_MATERIAL", "FR4");
    SetPcb3Material(readm);
	config.readInto<G4String>(readm, "BACK1_MATERIAL", "AluminiumSolid");
    SetBack1Material(readm);
	config.readInto<G4String>(readm, "BACK2_MATERIAL", "LeadSolid");
    SetBack2Material(readm);
	config.readInto<G4String>(readm, "FRAME_MATERIAL", "CarbonFiberReinforcedPlastic");
    SetFrameMaterial(readm);
	config.readInto<G4String>(readm, "SIDEFRAME1_MATERIAL", "CarbonFiberReinforcedPlastic");
    SetSideframe1Material(readm);
	config.readInto<G4String>(readm, "SIDEFRAME2_MATERIAL", "AluminiumSolid");
    SetSideframe2Material(readm);
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
	// G4Element*  Br = new G4Element("Bromine"   , "Br", z = 35., a =  79.90*g/mole);
    G4Element*  Zr = new G4Element("Zirconium" , "Zr", z = 40., a =  91.22*g/mole);
	G4Element*  Mo = new G4Element("Molybdenum", "Mo", z = 42., a =  95.94*g/mole);
	// G4Element*  I  = new G4Element("Iodine"    , "I" , z = 53., a = 126.90*g/mole);
    G4Element*  Cs = new G4Element("Caesium"   , "Cs", z = 55., a = 132.90*g/mole);
    G4Element*  Ba = new G4Element("Barium"    , "Ba", z = 56., a = 137.33*g/mole);
	// G4Element*  La = new G4Element("Lanthanium", "La", z = 57., a = 138.90*g/mole);
	G4Element*  Ta = new G4Element("Tantalum"  , "Ta", z = 73., a = 180.94*g/mole);
	G4Element*  W  = new G4Element("Tungsten"  , "W" , z = 74., a = 183.84*g/mole);
	G4Element*  Pb = new G4Element("Lead"      , "Pb", z = 82., a = 207.20*g/mole);
	G4Element*  Bi = new G4Element("Bismuth"   , "Bi", z = 83., a = 208.98*g/mole);

	// Materials 
	// Vacuum
	G4Material* Vacuum = new G4Material("Vacuum", density = 1.e-25*g/cm3, nel = 1);
	Vacuum -> AddElement(H, 100*perCent);

	// Helium Gas
	G4Material* HeliumGas = new G4Material("HeliumGas", density = 0.18*mg/cm3, nel = 1);
	HeliumGas -> AddElement(He, 100*perCent);

	// Air 
	G4Material* Air = new G4Material("Air", density = 1.29*mg/cm3, nel = 2);
	Air -> AddElement(N, 78*perCent);
	Air -> AddElement(O, 22*perCent);

	// Silicon Solid
	G4Material* SiliconSolid = new G4Material("SiliconSolid", density = 2.33*g/cm3, nel = 1);
	SiliconSolid -> AddElement(Si, 100*perCent);

	// Titanium Solid
	G4Material* TitaniumSolid = new G4Material("TitaniumSolid", density = 4.51*g/cm3, nel = 1);
	TitaniumSolid -> AddElement(Ti, 100*perCent);

	// Aluminium Solid
	G4Material* AluminiumSolid = new G4Material("AluminiumSolid", density = 2.700*g/cm3, nel = 1);
	AluminiumSolid -> AddElement(Al, 100*perCent);

	// Effective Aluminium Solid
	G4Material* EffectiveAluminiumSolid = new G4Material("EffectiveAluminiumSolid", density = 0.81*g/cm3, nel = 1);
	EffectiveAluminiumSolid -> AddElement(Al, 100*perCent);
	
	// Effective Bus Aluminium Solid (volume service module = 1.254 m3, weight = 376.5 kg, therefore density if it were full of aluminium)
	G4Material* EffectiveBusAluminiumSolid = new G4Material("EffectiveBusAluminiumSolid", density = 0.3*g/cm3, nel = 1);
	EffectiveBusAluminiumSolid -> AddElement(Al, 100*perCent);

	// Copper Solid
	G4Material* CopperSolid = new G4Material("CopperSolid", density = 8.94*g/cm3, nel = 1);
	CopperSolid -> AddElement(Cu, 100*perCent);

	// Effective Solid
	G4Material* EffectiveCopperSolid = new G4Material("EffectiveCopperSolid", density = 2.68*g/cm3, nel = 1);
	EffectiveCopperSolid -> AddElement(Cu, 100*perCent);

	// Molybdenum Solid
	G4Material* MolybdenumSolid = new G4Material("MolybdenumSolid", density = 10.28*g/cm3, nel = 1);
	MolybdenumSolid -> AddElement(Mo, 100*perCent);

	// Tungsten Solid
	G4Material* TungstenSolid = new G4Material("TungstenSolid", density = 19.25*g/cm3, nel = 1);
	TungstenSolid -> AddElement(W, 100*perCent);

	// Lead Solid
	G4Material* LeadSolid = new G4Material("LeadSolid", density = 11.34*g/cm3, nel = 1);
	LeadSolid -> AddElement(Pb, 100*perCent);

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
	G4int natoms;
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

	// Carbon fiber reinforced plastic (CFRP)
	G4Material* CarbonFiberReinforcedPlastic = new G4Material("CarbonFiberReinforcedPlastic", density = 1.71*g/cm3, nel = 2);
	CarbonFiberReinforcedPlastic -> AddElement(C, natoms=1);
	CarbonFiberReinforcedPlastic -> AddElement(H, natoms=2);

	// Carbon fiber reinforced plastic (CFRP) with effective 10% density
	G4Material* EffectiveCarbonFiberReinforcedPlastic = new G4Material("EffectiveCarbonFiberReinforcedPlastic", density = 0.171*g/cm3, nel = 2);
	EffectiveCarbonFiberReinforcedPlastic -> AddElement(C, natoms=1);
	EffectiveCarbonFiberReinforcedPlastic -> AddElement(H, natoms=2);

	// Polymide
	G4Material* Polymide = new G4Material("Polymide", density = 1.43*g/cm3, nel = 4);
	Polymide -> AddElement(C, natoms=22);
	Polymide -> AddElement(H, natoms=10);
	Polymide -> AddElement(N, natoms=2);
	Polymide -> AddElement(O, natoms=5);
	
	// Silicon Oxide
	G4Material* SiliconOxide = new G4Material("SiliconOxide", density = 2.65*g/cm3, nel = 2);
	SiliconOxide -> AddElement(Si, natoms=1);
	SiliconOxide -> AddElement(O,  natoms=2);
	
    // Lead Oxide
    G4Material* LeadOxide = new G4Material("LeadOxide", density = 9.53*g/cm3, nel = 2);
    LeadOxide -> AddElement(Pb, natoms=1);
    LeadOxide -> AddElement(O,  natoms=1);

    // Lithium Oxide
    G4Material* LithiumOxide = new G4Material("LithiumOxide", density = 2.01*g/cm3, nel = 2);
    LithiumOxide -> AddElement(Li, natoms=2);
    LithiumOxide -> AddElement(O,  natoms=1);

    // Sodium Oxide
    G4Material* SodiumOxide = new G4Material("SodiumOxide", density = 2.27*g/cm3, nel = 2);
    SodiumOxide -> AddElement(Na, natoms=2);
    SodiumOxide -> AddElement(O,  natoms=1);

    // Potassium Oxide
    G4Material* PotassiumOxide = new G4Material("PotassiumOxide", density = 2.35*g/cm3, nel = 2);
    PotassiumOxide -> AddElement(K, natoms=2);
    PotassiumOxide -> AddElement(O,  natoms=1);
    
    // Cesium Oxide
    G4Material* CesiumOxide = new G4Material("CesiumOxide", density = 4.65*g/cm3, nel = 2);
    CesiumOxide -> AddElement(Cs, natoms=2);
    CesiumOxide -> AddElement(O,  natoms=1);

    // Aluminium Oxide
    G4Material* AluminiumOxide = new G4Material("AluminiumOxide", density = 3.95*g/cm3, nel = 2);
    AluminiumOxide -> AddElement(Al, natoms=2);
    AluminiumOxide -> AddElement(O,  natoms=3);

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
    
    // Hamamatsu Lead Glass OAR 0% (bulk density 3.9 g/cm3)
    G4Material* HamamatsuLeadGlass = new G4Material("HamamatsuLeadGlass", density = 3.9*g/cm3, ncomponents=10);
    HamamatsuLeadGlass -> AddMaterial(SiliconOxide, fractionmass=42*perCent);
    HamamatsuLeadGlass -> AddMaterial(LeadOxide, fractionmass=43*perCent);
    HamamatsuLeadGlass -> AddMaterial(LithiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(SodiumOxide, fractionmass=2*perCent);
    HamamatsuLeadGlass -> AddMaterial(PotassiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass -> AddMaterial(CesiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(AluminiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(BariumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass -> AddMaterial(ZirconiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass -> AddMaterial(BismuthOxide, fractionmass=3*perCent);


    // Hamamatsu Lead Glass OAR 70% (bulk density 3.9 g/cm3)
    G4Material* HamamatsuLeadGlass_oar70 = new G4Material("HamamatsuLeadGlass_oar70", density = 1.17*g/cm3, ncomponents=10);
    HamamatsuLeadGlass_oar70 -> AddMaterial(SiliconOxide, fractionmass=42*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(LeadOxide, fractionmass=43*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(LithiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(SodiumOxide, fractionmass=2*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(PotassiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(CesiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(AluminiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(BariumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(ZirconiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar70 -> AddMaterial(BismuthOxide, fractionmass=3*perCent);

    
    // Hamamatsu Lead Glass OAR 75% (bulk density 3.9 g/cm3)
    G4Material* HamamatsuLeadGlass_oar75 = new G4Material("HamamatsuLeadGlass_oar75", density = 0.975*g/cm3, ncomponents=10);
    HamamatsuLeadGlass_oar75 -> AddMaterial(SiliconOxide, fractionmass=42*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(LeadOxide, fractionmass=43*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(LithiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(SodiumOxide, fractionmass=2*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(PotassiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(CesiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(AluminiumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(BariumOxide, fractionmass=1*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(ZirconiumOxide, fractionmass=3*perCent);
    HamamatsuLeadGlass_oar75 -> AddMaterial(BismuthOxide, fractionmass=3*perCent);

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
	FR4 -> AddMaterial(SiliconOxide, fractionmass=60*perCent);
	FR4 -> AddMaterial(Epoxy_Resin,  fractionmass=40*perCent);
	

	// Effective dummy panel material
	G4Material* EffectiveDummyPanelSolid = new G4Material("EffectiveDummyPanelSolid", density = 1.0*g/cm3, ncomponents=2);
	EffectiveDummyPanelSolid -> AddMaterial(AluminiumSolid, fractionmass=92.4*perCent);
	EffectiveDummyPanelSolid -> AddMaterial(LeadSolid,  fractionmass=7.6*perCent);


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


	// 0. Experimental hall (world volume)
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

    // Module parameterisation
    G4int pixelArray_x  = pixel_x;
    G4int pixelArray_y  = pixel_y;
    G4double pixelSize_x = sdd_x/pixel_x;
    G4double pixelSize_y = sdd_y/pixel_y;

    
	G4int nModules  = moduleArray_x*moduleArray_y;
	G4cout << "Number of modules: " << nModules << "; "
                                    << "Array: "
                                    << moduleArray_x << " x " << moduleArray_y << G4endl;
    
	G4double moduleSpacing_x = sdd_x + sideframe2_width;
	G4double moduleSpacing_y = sdd_y + sideframe2_width;
	G4double plate_x = moduleArray_x * sdd_x + (moduleArray_x + 1) * sideframe2_width;
	G4double plate_y = moduleArray_y * sdd_y + (moduleArray_y + 1) * sideframe2_width;
	G4cout << "Panel dimensions: x = " << plate_x/cm << " cm; y = " << plate_y/cm  << " cm" << G4endl;
    
    G4int nPixelPerModule  = pixelArray_x*pixelArray_y;
    G4cout << "Number of pixels per module: " << nPixelPerModule << "; "
                                    << "Array: "
                                    << pixelArray_x << " x " << pixelArray_y << G4endl;
    G4int nXPixels = pixelArray_x * moduleArray_x;
    G4int nYPixels = pixelArray_y * moduleArray_y;
    G4int nPixels  = nXPixels * nYPixels;
    G4cout << "Number of total pixels: " << nPixels << "; "
                                         << "Array: "
                                         << nXPixels << " x " << nYPixels << G4endl;



	// . SDD detector
	G4double plateSdd_x = plate_x;
	G4double plateSdd_y = plate_y;
	G4double plateSdd_z = sdd_thick;
	
	G4Box* plateSdd_box = new G4Box("plateSdd_box",
									plateSdd_x/2., plateSdd_y/2., plateSdd_z/2.);
	
	plateSdd_log = new G4LogicalVolume(plateSdd_box,
									   sideframe2Material, "plateSdd_log", 0, 0, 0);
	G4double sddPos_x = 0.0*cm;
	G4double sddPos_y = 0.0*cm;
	G4double sddPos_z = 0.0*cm;
	plateSdd_phys = new G4PVPlacement(0,
									  G4ThreeVector(sddPos_x, sddPos_y, sddPos_z),
									  plateSdd_log,
									  "plateSdd_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4Box* sdd_box = new G4Box("SDD_box",
							   pixelSize_x/2., pixelSize_y/2., sdd_thick/2.);
	// Logical
	sdd_log = new G4LogicalVolume(sdd_box,
								  sddMaterial, "SDD_log", 0, 0, 0);
	// Physical
	sddParam = new SDDParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y,
                                       pixelSize_x, pixelSize_y, pixelArray_x, pixelArray_y);
	
//    sddParam = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);

	sdd_phys = new G4PVParameterised("sdd_phys",       		// their name
									 sdd_log,    	        // their logical volume
									 plateSdd_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
//									 nModules,    		// Number of chambers
                                     nPixels,    		// Number of chambers
									 sddParam);   		// The parametrisation


	// // . Collimator
	// 
	G4double plateColl_x = plate_x;
	G4double plateColl_y = plate_y;
	G4double plateColl_z = coll_thick;
	
	G4Box* plateColl_box = new G4Box("plateColl_box",
									plateColl_x/2., plateColl_y/2., plateColl_z/2.);
	
	plateColl_log = new G4LogicalVolume(plateColl_box,
									   sideframe2Material, "plateColl_log", 0, 0, 0);
	G4double collPos_x = sddPos_x;
	G4double collPos_y = sddPos_y;
	G4double collPos_z = coll_thick/2. + deadlayer1_thick + deadlayer2_thick + deadlayer3_thick + coating_thick + sdd_thick/2.; 
	plateColl_phys = new G4PVPlacement(0,
									  G4ThreeVector(collPos_x, collPos_y, collPos_z),
									  plateColl_log,
									  "plateColl_phys",
									  experimentalHall_log,
									  false,
									  0);
	// Solid
	G4double coll_x = sdd_x;
	G4double coll_y = sdd_y;
	G4Box* coll_box = new G4Box("coll_box",
								coll_x/2., coll_y/2., coll_thick/2.);
	// Logical
	coll_log = new G4LogicalVolume(coll_box,
								   collMaterial, "coll_log", 0, 0, 0);
	// Physical
	collParam = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	
	coll_phys = new G4PVParameterised("coll_phys",       		// their name
									 coll_log,    	        // their logical volume
									 plateColl_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 collParam);   		// The parametrisation
									
									
									
	// 4. Thermal blanket
	// 4a. First layer
	// Solid
	G4double thermalblanket1_x = plate_x;
	G4double thermalblanket1_y = plate_y;
	G4Box* thermalblanket1_box = new G4Box("thermalblanket1_box", 
									thermalblanket1_x/2., thermalblanket1_y/2., thermalblanket1_thick/2.);
	// Logical
	thermalblanket1_log = new G4LogicalVolume(thermalblanket1_box,
														thermalblanket1Material, "thermalblanket1_log", 0, 0, 0);
	// Physical
	G4double thermalblanket1Pos_x = sddPos_x;
	G4double thermalblanket1Pos_y = sddPos_y;
	G4double thermalblanket1Pos_z = thermalblanket1_thick/2. + thermalblanket2_thick + coll_thick + coating_thick + deadlayer1_thick + deadlayer2_thick + deadlayer3_thick + sdd_thick/2.; 
	thermalblanket1_phys = new G4PVPlacement(0,
								      G4ThreeVector(thermalblanket1Pos_x, thermalblanket1Pos_y, thermalblanket1Pos_z),
								      thermalblanket1_log,
								      "thermalblanket1_phys", 
								      experimentalHall_log, 
								      false, 
								      0);

	// 4b. Second layer
	// Solid
	G4double thermalblanket2_x = plate_x;
	G4double thermalblanket2_y = plate_y;
	G4Box* thermalblanket2_box = new G4Box("thermalblanket2_box", 
									thermalblanket2_x/2., thermalblanket2_y/2., thermalblanket2_thick/2.);
	// Logical
	thermalblanket2_log = new G4LogicalVolume(thermalblanket2_box,
														thermalblanket2Material, "thermalblanket2_log", 0, 0, 0);
	// Physical
	G4double thermalblanket2Pos_x = sddPos_x;
	G4double thermalblanket2Pos_y = sddPos_y;
	G4double thermalblanket2Pos_z = thermalblanket2_thick/2. + coll_thick + coating_thick + deadlayer1_thick + deadlayer2_thick + deadlayer3_thick + sdd_thick/2.; 
	thermalblanket2_phys = new G4PVPlacement(0,
									  G4ThreeVector(thermalblanket2Pos_x, thermalblanket2Pos_y, thermalblanket2Pos_z),
									  thermalblanket2_log,
									  "thermalblanket2_phys", 
									  experimentalHall_log, 
									  false, 
									  0);

	// . Coating 
	G4double plateCoating_x = plate_x;
	G4double plateCoating_y = plate_y;
	G4double plateCoating_z = coating_thick;
	
	G4Box* plateCoating_box = new G4Box("plateCoating_box",
									plateCoating_x/2., plateCoating_y/2., plateCoating_z/2.);
	
	plateCoating_log = new G4LogicalVolume(plateCoating_box,
									   sideframe2Material, "plateCoating_log", 0, 0, 0);
	G4double coatingPos_x = sddPos_x;
	G4double coatingPos_y = sddPos_y;
	G4double coatingPos_z = coating_thick/2. + deadlayer1_thick + deadlayer2_thick + deadlayer3_thick + sdd_thick/2.; 
	plateCoating_phys = new G4PVPlacement(0,
									  G4ThreeVector(coatingPos_x, coatingPos_y, coatingPos_z),
									  plateCoating_log,
									  "plateCoating_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double coating_x = sdd_x;
	G4double coating_y = sdd_y;
	G4Box* coating_box = new G4Box("coating_box", 
									coating_x/2., coating_y/2., coating_thick/2.);
	// Logical
	coating_log = new G4LogicalVolume(coating_box,
														coatingMaterial, "coating_log", 0, 0, 0);
	// Physical
	coatingParam = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	  
	coating_phys = new G4PVParameterised("coating_phys",        // their name
									 coating_log,    	        // their logical volume
									 plateCoating_log,  		// Mother logical volume
									 kYAxis,          			// Are placed along this axis 
									 nModules,    			// Number of chambers
									 coatingParam);   			// The parametrisation


	// . Deadlayer1 
	G4double plateDeadlayer1_x = plate_x;
	G4double plateDeadlayer1_y = plate_y;
	G4double plateDeadlayer1_z = deadlayer1_thick;
	
	G4Box* plateDeadlayer1_box = new G4Box("plateDeadlayer1_box",
									plateDeadlayer1_x/2., plateDeadlayer1_y/2., plateDeadlayer1_z/2.);
	
	plateDeadlayer1_log = new G4LogicalVolume(plateDeadlayer1_box,
									   sideframe2Material, "plateDeadlayer1_log", 0, 0, 0);
	G4double deadlayer1Pos_x = sddPos_x;
	G4double deadlayer1Pos_y = sddPos_y;
	G4double deadlayer1Pos_z = deadlayer1_thick/2. + deadlayer2_thick + deadlayer3_thick + sdd_thick/2.; 
	plateDeadlayer1_phys = new G4PVPlacement(0,
									  G4ThreeVector(deadlayer1Pos_x, deadlayer1Pos_y, deadlayer1Pos_z),
									  plateDeadlayer1_log,
									  "plateDeadlayer1_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double deadlayer1_x = sdd_x;
	G4double deadlayer1_y = sdd_y;
	G4Box* deadlayer1_box = new G4Box("deadlayer1_box", 
									deadlayer1_x/2., deadlayer1_y/2., deadlayer1_thick/2.);
	// Logical
	deadlayer1_log = new G4LogicalVolume(deadlayer1_box,
														deadlayer1Material, "deadlayer1_log", 0, 0, 0);
	// Physical
	deadlayer1Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	  
	deadlayer1_phys = new G4PVParameterised("deadlayer1_phys",      // their name
									 deadlayer1_log,    	        // their logical volume
									 plateDeadlayer1_log,  			// Mother logical volume
									 kYAxis,          				// Are placed along this axis 
									 nModules,    				// Number of chambers
									 deadlayer1Param);   			// The parametrisation


	// . Deadlayer2 
	G4double plateDeadlayer2_x = plate_x;
	G4double plateDeadlayer2_y = plate_y;
	G4double plateDeadlayer2_z = deadlayer2_thick;
	
	G4Box* plateDeadlayer2_box = new G4Box("plateDeadlayer2_box",
									plateDeadlayer2_x/2., plateDeadlayer2_y/2., plateDeadlayer2_z/2.);
	
	plateDeadlayer2_log = new G4LogicalVolume(plateDeadlayer2_box,
									   sideframe2Material, "plateDeadlayer2_log", 0, 0, 0);
	G4double deadlayer2Pos_x = sddPos_x;
	G4double deadlayer2Pos_y = sddPos_y;
	G4double deadlayer2Pos_z = deadlayer2_thick/2. + deadlayer3_thick + sdd_thick/2.; 
	plateDeadlayer2_phys = new G4PVPlacement(0,
									  G4ThreeVector(deadlayer2Pos_x, deadlayer2Pos_y, deadlayer2Pos_z),
									  plateDeadlayer2_log,
									  "plateDeadlayer2_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double deadlayer2_x = sdd_x;
	G4double deadlayer2_y = sdd_y;
	G4Box* deadlayer2_box = new G4Box("deadlayer2_box", 
									deadlayer2_x/2., deadlayer2_y/2., deadlayer2_thick/2.);
	// Logical
	deadlayer2_log = new G4LogicalVolume(deadlayer2_box,
														deadlayer2Material, "deadlayer2_log", 0, 0, 0);
	// Physical
	deadlayer2Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	  
	deadlayer2_phys = new G4PVParameterised("deadlayer2_phys",      // their name
									 deadlayer2_log,    	        // their logical volume
									 plateDeadlayer2_log,  			// Mother logical volume
									 kYAxis,          				// Are placed along this axis 
									 nModules,    				// Number of chambers
									 deadlayer2Param);   			// The parametrisation


	// . Deadlayer3 
	G4double plateDeadlayer3_x = plate_x;
	G4double plateDeadlayer3_y = plate_y;
	G4double plateDeadlayer3_z = deadlayer3_thick;
	
	G4Box* plateDeadlayer3_box = new G4Box("plateDeadlayer3_box",
									plateDeadlayer3_x/2., plateDeadlayer3_y/2., plateDeadlayer3_z/2.);
	
	plateDeadlayer3_log = new G4LogicalVolume(plateDeadlayer3_box,
									   sideframe2Material, "plateDeadlayer3_log", 0, 0, 0);
	G4double deadlayer3Pos_x = sddPos_x;
	G4double deadlayer3Pos_y = sddPos_y;
	G4double deadlayer3Pos_z = deadlayer3_thick/2. + sdd_thick/2.; 
	plateDeadlayer3_phys = new G4PVPlacement(0,
									  G4ThreeVector(deadlayer3Pos_x, deadlayer3Pos_y, deadlayer3Pos_z),
									  plateDeadlayer3_log,
									  "plateDeadlayer3_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double deadlayer3_x = sdd_x;
	G4double deadlayer3_y = sdd_y;
	G4Box* deadlayer3_box = new G4Box("deadlayer3_box", 
									deadlayer3_x/2., deadlayer3_y/2., deadlayer3_thick/2.);
	// Logical
	deadlayer3_log = new G4LogicalVolume(deadlayer3_box,
														deadlayer3Material, "deadlayer3_log", 0, 0, 0);
	// Physical
	deadlayer3Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	  
	deadlayer3_phys = new G4PVParameterised("deadlayer3_phys",      // their name
									 deadlayer3_log,    	        // their logical volume
									 plateDeadlayer3_log,  			// Mother logical volume
									 kYAxis,          				// Are placed along this axis 
									 nModules,    				// Number of chambers
									 deadlayer3Param);   			// The parametrisation


	// . PCB shielding layer
	G4double platePcbs_x = plate_x;
	G4double platePcbs_y = plate_y;
	G4double platePcbs_z = pcbs_thick;

	G4Box* platePcbs_box = new G4Box("platePcbs_box",
									platePcbs_x/2., platePcbs_y/2., platePcbs_z/2.);

	platePcbs_log = new G4LogicalVolume(platePcbs_box,
									   sideframe2Material, "platePcbs_log", 0, 0, 0);
	G4double pcbsPos_x = sddPos_x;
	G4double pcbsPos_y = sddPos_y;
	G4double pcbsPos_z = -(sdd_thick + pcbs_thick)/2.; 
	platePcbs_phys = new G4PVPlacement(0,
									  G4ThreeVector(pcbsPos_x, pcbsPos_y, pcbsPos_z),
									  platePcbs_log,
									  "platePcbs_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double pcbs_x = sdd_x;
	G4double pcbs_y = sdd_y;
	G4Box* pcbs_box = new G4Box("pcbs_box", 
								  pcbs_x/2., pcbs_y/2., pcbs_thick/2.);
	// Logical
	pcbs_log = new G4LogicalVolume(pcbs_box,
													 pcbsMaterial, "pcbs_log", 0, 0, 0);
	// Physical
	pcbsParam = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);

	pcbs_phys = new G4PVParameterised("pcbs_phys",       	// their name
									 pcbs_log,    	        // their logical volume
									 platePcbs_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 pcbsParam);   			// The parametrisation


	// . PCB 1st layer
	G4double platePcb1_x = plate_x;
	G4double platePcb1_y = plate_y;
	G4double platePcb1_z = pcb1_thick;

	G4Box* platePcb1_box = new G4Box("platePcb1_box",
									platePcb1_x/2., platePcb1_y/2., platePcb1_z/2.);

	platePcb1_log = new G4LogicalVolume(platePcb1_box,
									   sideframe2Material, "platePcb1_log", 0, 0, 0);
	G4double pcb1Pos_x = sddPos_x;
	G4double pcb1Pos_y = sddPos_y;
	G4double pcb1Pos_z = -(sdd_thick/2. + pcbs_thick + pcb1_thick/2.); 
	platePcb1_phys = new G4PVPlacement(0,
									  G4ThreeVector(pcb1Pos_x, pcb1Pos_y, pcb1Pos_z),
									  platePcb1_log,
									  "platePcb1_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double pcb1_x = sdd_x;
	G4double pcb1_y = sdd_y;
	G4Box* pcb1_box = new G4Box("pcb1_box", 
								  pcb1_x/2., pcb1_y/2., pcb1_thick/2.);
	// Logical
	pcb1_log = new G4LogicalVolume(pcb1_box,
													 pcb1Material, "pcb1_log", 0, 0, 0);
	// Physical
	pcb1Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
  
	pcb1_phys = new G4PVParameterised("pcb1_phys",       	// their name
									 pcb1_log,    	        // their logical volume
									 platePcb1_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 pcb1Param);   			// The parametrisation

	// . PCB 2nd layer
	G4double platePcb2_x = plate_x;
	G4double platePcb2_y = plate_y;
	G4double platePcb2_z = pcb2_thick;

	G4Box* platePcb2_box = new G4Box("platePcb2_box",
									platePcb2_x/2., platePcb2_y/2., platePcb2_z/2.);

	platePcb2_log = new G4LogicalVolume(platePcb2_box,
									   sideframe2Material, "platePcb2_log", 0, 0, 0);
	G4double pcb2Pos_x = sddPos_x;
	G4double pcb2Pos_y = sddPos_y;
	G4double pcb2Pos_z = -(sdd_thick/2. + pcbs_thick + pcb1_thick + pcb2_thick/2.); 
	platePcb2_phys = new G4PVPlacement(0,
									  G4ThreeVector(pcb2Pos_x, pcb2Pos_y, pcb2Pos_z),
									  platePcb2_log,
									  "platePcb2_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double pcb2_x = sdd_x;
	G4double pcb2_y = sdd_y;
	G4Box* pcb2_box = new G4Box("pcb2_box", 
								  pcb2_x/2., pcb2_y/2., pcb2_thick/2.);
	// Logical
	pcb2_log = new G4LogicalVolume(pcb2_box,
													 pcb2Material, "pcb2_log", 0, 0, 0);
	// Physical
	pcb2Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
  
	pcb2_phys = new G4PVParameterised("pcb2_phys",       	// their name
									 pcb2_log,    	        // their logical volume
									 platePcb2_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 pcb2Param);   			// The parametrisation

	// . PCB 3rd layer
	G4double platePcb3_x = plate_x;
	G4double platePcb3_y = plate_y;
	G4double platePcb3_z = pcb3_thick;

	G4Box* platePcb3_box = new G4Box("platePcb3_box",
									platePcb3_x/2., platePcb3_y/2., platePcb3_z/2.);

	platePcb3_log = new G4LogicalVolume(platePcb3_box,
									   sideframe2Material, "platePcb3_log", 0, 0, 0);
	G4double pcb3Pos_x = sddPos_x;
	G4double pcb3Pos_y = sddPos_y;
	G4double pcb3Pos_z = -(sdd_thick/2. + pcbs_thick + pcb1_thick + pcb2_thick + pcb3_thick/2.);
	platePcb3_phys = new G4PVPlacement(0,
									  G4ThreeVector(pcb3Pos_x, pcb3Pos_y, pcb3Pos_z),
									  platePcb3_log,
									  "platePcb3_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double pcb3_x = sdd_x;
	G4double pcb3_y = sdd_y;
	G4Box* pcb3_box = new G4Box("pcb3_box", 
								  pcb3_x/2., pcb3_y/2., pcb3_thick/2.);
	// Logical
	pcb3_log = new G4LogicalVolume(pcb3_box,
													 pcb3Material, "pcb3_log", 0, 0, 0);
	// Physical
	pcb3Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
  
	pcb3_phys = new G4PVParameterised("pcb3_phys",       	// their name
									 pcb3_log,    	        // their logical volume
									 platePcb3_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 pcb3Param);   			// The parametrisation
	
	
	// . Radiator
	G4double plateBack1_x = plate_x;
	G4double plateBack1_y = plate_y;
	G4double plateBack1_z = back1_thick;
	
	G4Box* plateBack1_box = new G4Box("plateBack1_box",
									plateBack1_x/2., plateBack1_y/2., plateBack1_z/2.);
	
	plateBack1_log = new G4LogicalVolume(plateBack1_box,
									   sideframe2Material, "plateBack1_log", 0, 0, 0);
	G4double back1Pos_x = sddPos_x;
	G4double back1Pos_y = sddPos_y;
	G4double back1Pos_z = -(sdd_thick/2. + pcbs_thick + pcb1_thick + pcb2_thick + pcb3_thick + back1_thick/2.); 
	plateBack1_phys = new G4PVPlacement(0,
									  G4ThreeVector(back1Pos_x, back1Pos_y, back1Pos_z),
									  plateBack1_log,
									  "plateBack1_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double back1_x = sdd_x;
	G4double back1_y = sdd_y;
	G4Box* back1_box = new G4Box("back1_box", 
								  back1_x/2., back1_y/2., back1_thick/2.);
	// Logical
	back1_log = new G4LogicalVolume(back1_box,
													 back1Material, "back1_log", 0, 0, 0);
	// Physical
	back1Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	
	back1_phys = new G4PVParameterised("back1_phys",       	// their name
									 back1_log,    	        // their logical volume
									 plateBack1_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 back1Param);   		// The parametrisation
								
	// . Backshielding
	G4double plateBack2_x = plate_x;
	G4double plateBack2_y = plate_y;
	G4double plateBack2_z = back2_thick;
	
	G4Box* plateBack2_box = new G4Box("plateBack2_box",
									plateBack2_x/2., plateBack2_y/2., plateBack2_z/2.);
	
	plateBack2_log = new G4LogicalVolume(plateBack2_box,
									   sideframe2Material, "plateBack2_log", 0, 0, 0);
	G4double back2Pos_x = sddPos_x;
	G4double back2Pos_y = sddPos_y;
	G4double back2Pos_z = -(sdd_thick/2. + pcbs_thick + pcb1_thick + pcb2_thick + pcb3_thick + back1_thick + back2_thick/2.); 
	plateBack2_phys = new G4PVPlacement(0,
									  G4ThreeVector(back2Pos_x, back2Pos_y, back2Pos_z),
									  plateBack2_log,
									  "plateBack2_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double back2_x = sdd_x;
	G4double back2_y = sdd_y;
	G4Box* back2_box = new G4Box("back2_box", 
								  back2_x/2., back2_y/2., back2_thick/2.);
	// Logical
	back2_log = new G4LogicalVolume(back2_box,
													 back2Material, "back2_log", 0, 0, 0);
	// Physical
	back2Param = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	
	back2_phys = new G4PVParameterised("back2_phys",       	// their name
									 back2_log,    	        // their logical volume
									 plateBack2_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 back2Param);   		// The parametrisation
								
	// . Backside Frame
	G4double plateFrame_x = plate_x;
	G4double plateFrame_y = plate_y;
	G4double plateFrame_z = frame_thick;
	
	G4Box* plateFrame_box = new G4Box("plateFrame_box",
									plateFrame_x/2., plateFrame_y/2., plateFrame_z/2.);
	
	plateFrame_log = new G4LogicalVolume(plateFrame_box,
									   defaultMaterial, "plateFrame_log", 0, 0, 0);
	G4double framePos_x = sddPos_x;
	G4double framePos_y = sddPos_y;
	G4double framePos_z = -(sdd_thick/2. + pcbs_thick + pcb1_thick + pcb2_thick + pcb3_thick + back1_thick + back2_thick + frame_thick/2.); 
	plateFrame_phys = new G4PVPlacement(0,
									  G4ThreeVector(framePos_x, framePos_y, framePos_z),
									  plateFrame_log,
									  "plateFrame_phys",
									  experimentalHall_log,
									  false,
									  0);

	// Solid
	G4double frame_x = sdd_x;
	G4double frame_y = sdd_y;
	G4Box* frame_box = new G4Box("frame_box", 
								  frame_x/2., frame_y/2., frame_thick/2.);
	// Logical
	frame_log = new G4LogicalVolume(frame_box,
													 frameMaterial, "frame_log", 0, 0, 0);
	// Physical
	frameParam = new ModuleParameterisation(moduleSpacing_x, moduleSpacing_y, moduleArray_x, moduleArray_y);
	
	frame_phys = new G4PVParameterised("frame_phys",       	// their name
									 frame_log,    	        // their logical volume
									 plateFrame_log,  		// Mother logical volume
									 kYAxis,          		// Are placed along this axis 
									 nModules,    		// Number of chambers
									 frameParam);   		// The parametrisation



	// . Side frame 1
	G4double sideframe_thick =  coll_thick + coating_thick + deadlayer1_thick + deadlayer2_thick + deadlayer3_thick + sdd_thick + pcbs_thick + pcb1_thick + pcb2_thick + pcb3_thick + back1_thick + back2_thick + frame_thick;
	
	G4double sideframe1_Ext_x     = 2*sideframe1_width + 2*sideframe2_width + plate_x;
	G4double sideframe1_Ext_y     = 2*sideframe1_width + 2*sideframe2_width + plate_y;
	G4double sideframe1_Int_x     = 2*sideframe2_width + plate_x;
	G4double sideframe1_Int_y     = 2*sideframe2_width + plate_y;
	
	G4VSolid* sideframe1_Externalbox = new G4Box("sideframe1_Externalbox", 
									  			sideframe1_Ext_x/2., sideframe1_Ext_y/2., sideframe_thick/2.);
	G4VSolid* sideframe1_Internalbox = new G4Box("sideframe1_Internalbox", 
									  			sideframe1_Int_x/2., sideframe1_Int_y/2., sideframe_thick/2.);
									
	G4VSolid* sideframe1_booleansolid = new G4SubtractionSolid("sideframe1_booleansolid", 
											sideframe1_Externalbox, sideframe1_Internalbox, 0, G4ThreeVector(0,0.,0.));

	// Logical
	sideframe1_log = new G4LogicalVolume(sideframe1_booleansolid,
	                           			 sideframe1Material, "sideframe1_log", 0, 0, 0);
	// Physical
	G4double sideframe1Pos_x = 0.*cm;
	G4double sideframe1Pos_y = 0.*cm;
	G4double sideframe1Pos_z = 0.*cm; 
	sideframe1_phys = new G4PVPlacement(0,
										 G4ThreeVector(sideframe1Pos_x, sideframe1Pos_y, sideframe1Pos_z),
										 sideframe1_log,
										 "sideframe1_phys", 
										 experimentalHall_log, 
										 false, 
										 0);

	G4double sideframe2_Ext_x     = 2*sideframe2_width + plate_x;
	G4double sideframe2_Ext_y     = 2*sideframe2_width + plate_y;
	G4double sideframe2_Int_x     = plate_x;
	G4double sideframe2_Int_y     = plate_y;
	
	G4VSolid* sideframe2_Externalbox = new G4Box("sideframe2_Externalbox", 
									  			sideframe2_Ext_x/2., sideframe2_Ext_y/2., sideframe_thick/2.);
	G4VSolid* sideframe2_Internalbox = new G4Box("sideframe2_Internalbox", 
									  			sideframe2_Int_x/2., sideframe2_Int_y/2., sideframe_thick/2.);
									
	G4VSolid* sideframe2_booleansolid = new G4SubtractionSolid("sideframe2_booleansolid", 
											sideframe2_Externalbox, sideframe2_Internalbox, 0, G4ThreeVector(0,0.,0.));

	// Logical
	sideframe2_log = new G4LogicalVolume(sideframe2_booleansolid,
	                           			 sideframe2Material, "sideframe2_log", 0, 0, 0);
	// Physical
	G4double sideframe2Pos_x = 0.*cm;
	G4double sideframe2Pos_y = 0.*cm;
	G4double sideframe2Pos_z = 0.*cm; 
	sideframe2_phys = new G4PVPlacement(0,
										 G4ThreeVector(sideframe2Pos_x, sideframe2Pos_y, sideframe2Pos_z),
										 sideframe2_log,
										 "sideframe2_phys", 
										 experimentalHall_log, 
										 false, 
										 0);





    
    // 10. SATELLITE BUS

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
        
        solarpanel1_phys = new G4PVPlacement(solarpanelRot,
                                          G4ThreeVector(solarpanelPos_x, solarpanelPos_y, solarpanelPos_z),
                                          solarpanel_log,
                                          "solarpanel1_phys",
                                          experimentalHall_log,
                                          false,
                                          0);

        // Physical 2
        solarpanelPos_x = bus_distance -tower_diameter/2 - solarpanelGap - solarpanel_side_x/2.;
        solarpanel2_phys = new G4PVPlacement(solarpanelRot,
                                          G4ThreeVector(solarpanelPos_x, solarpanelPos_y, solarpanelPos_z),
                                          solarpanel_log,
                                          "solarpanel2_phys",
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
	else if (flag_satellitebus == false)
	{
        //...
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
//    sdd_log -> SetVisAttributes(SDDVisAtt);
    sdd_log       -> SetVisAttributes(G4VisAttributes::Invisible);
    
//    plateSdd_log        -> SetVisAttributes(G4VisAttributes::Invisible);
	plateColl_log       -> SetVisAttributes(G4VisAttributes::Invisible);
	plateCoating_log    -> SetVisAttributes(G4VisAttributes::Invisible);
	plateDeadlayer1_log -> SetVisAttributes(G4VisAttributes::Invisible);  
	plateDeadlayer2_log -> SetVisAttributes(G4VisAttributes::Invisible);  
	plateDeadlayer3_log -> SetVisAttributes(G4VisAttributes::Invisible);  
	platePcb1_log       -> SetVisAttributes(G4VisAttributes::Invisible);
	platePcb2_log       -> SetVisAttributes(G4VisAttributes::Invisible);
	platePcb3_log       -> SetVisAttributes(G4VisAttributes::Invisible);
	plateBack1_log      -> SetVisAttributes(G4VisAttributes::Invisible);
	plateBack2_log      -> SetVisAttributes(G4VisAttributes::Invisible);
	plateFrame_log      -> SetVisAttributes(G4VisAttributes::Invisible);


	G4VisAttributes* CollimatorVisAtt= new G4VisAttributes(blue);
//    coll_log  -> SetVisAttributes(CollimatorVisAtt);
    coll_log       -> SetVisAttributes(G4VisAttributes::Invisible);

    G4VisAttributes* ThermalBlanketVisAtt = new G4VisAttributes(magenta);
	thermalblanket1_log -> SetVisAttributes(ThermalBlanketVisAtt);  
	thermalblanket2_log -> SetVisAttributes(ThermalBlanketVisAtt);  
	
	G4VisAttributes* CoatingVisAtt= new G4VisAttributes(red);
	coating_log -> SetVisAttributes(CoatingVisAtt);
	
	deadlayer1_log -> SetVisAttributes(G4VisAttributes::Invisible);  
	deadlayer2_log -> SetVisAttributes(G4VisAttributes::Invisible);  
	deadlayer3_log -> SetVisAttributes(G4VisAttributes::Invisible);  
	
	pcbs_log -> SetVisAttributes(G4VisAttributes::Invisible);
	
	G4VisAttributes* PCB1VisAtt= new G4VisAttributes(green);
	pcb1_log -> SetVisAttributes(PCB1VisAtt);
	
	G4VisAttributes* PCB2VisAtt= new G4VisAttributes(red);
	pcb2_log -> SetVisAttributes(PCB2VisAtt);
	
	G4VisAttributes* PCB3VisAtt= new G4VisAttributes(green);
	pcb3_log -> SetVisAttributes(PCB3VisAtt);
	
	G4VisAttributes* Back1VisAtt= new G4VisAttributes(magenta);
	back1_log -> SetVisAttributes(Back1VisAtt);
	
	G4VisAttributes* Back2VisAtt= new G4VisAttributes(green);
	back2_log -> SetVisAttributes(Back2VisAtt);
	
	G4VisAttributes* FrameVisAtt= new G4VisAttributes(cyan);
	frame_log -> SetVisAttributes(FrameVisAtt);

	G4VisAttributes* Sideframe1VisAtt= new G4VisAttributes(cyan);
	sideframe1_log -> SetVisAttributes(Sideframe1VisAtt);

	G4VisAttributes* Sideframe2VisAtt= new G4VisAttributes(red);
	sideframe2_log -> SetVisAttributes(Sideframe2VisAtt);

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
    // *** NOTE: Put the pixel values as parameters?
    G4double pixelsizeX = 0.97*mm;
    G4double pixelsizeY = 35.0*mm;
    G4int sddXsectors  = sdd_x/pixelsizeX;
    G4int sddYsectors  = sdd_y/pixelsizeY;
        
    G4int totalXpixels = sddXsectors*moduleArray_x;
    G4int totalYpixels = sddYsectors*moduleArray_y;
    
    G4cout << "*** DEBUG: totalXpixels " << totalXpixels << " totalYpixels " << totalYpixels << G4endl;
    G4cout << "*** DEBUG: totalXpixels*totalYpixels " << totalXpixels*totalYpixels << G4endl;
        
    SensitiveDetector* sdd_SD = new SensitiveDetector("SDD", totalXpixels, totalYpixels);
    
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


void DetectorConstruction::SetThermalblanket1Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) thermalblanket1Material = pttoMaterial;
}


void DetectorConstruction::SetThermalblanket2Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) thermalblanket2Material = pttoMaterial;
}


void DetectorConstruction::SetCoatingMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) coatingMaterial = pttoMaterial;
}


void DetectorConstruction::SetDeadlayer1Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) deadlayer1Material = pttoMaterial;
}


void DetectorConstruction::SetDeadlayer2Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) deadlayer2Material = pttoMaterial;
}


void DetectorConstruction::SetDeadlayer3Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) deadlayer3Material = pttoMaterial;
}


void DetectorConstruction::SetPcbsMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcbsMaterial = pttoMaterial;
}

void DetectorConstruction::SetPcb1Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcb1Material = pttoMaterial;
}

void DetectorConstruction::SetPcb2Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcb2Material = pttoMaterial;
}

void DetectorConstruction::SetPcb3Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) pcb3Material = pttoMaterial;
}


void DetectorConstruction::SetBack1Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) back1Material = pttoMaterial;
}


void DetectorConstruction::SetBack2Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) back2Material = pttoMaterial;
}


void DetectorConstruction::SetFrameMaterial(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) frameMaterial = pttoMaterial;
}


void DetectorConstruction::SetSideframe1Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) sideframe1Material = pttoMaterial;
}

void DetectorConstruction::SetSideframe2Material(G4String materialChoice)
{
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
	if (pttoMaterial) sideframe2Material = pttoMaterial;
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
			<< "\n Thermal blanket 1 Thickness    (um) : " 	<< thermalblanket1_thick/um
			<< "\n Thermal blanket 1 material          : " 	<< thermalblanket1Material -> GetName()
			<< "\n Thermal blanket 2 Thickness    (um) : " 	<< thermalblanket2_thick/um
			<< "\n Thermal blanket 2 material          : " 	<< thermalblanket2Material -> GetName()
			<< "\n Coating Thickness              (um) : " 	<< coating_thick/um
			<< "\n Coating material                    : " 	<< coatingMaterial -> GetName()
			<< "\n Dead layer 1 Thickness         (um) : " 	<< deadlayer1_thick/um
			<< "\n Dead layer 1 material               : " 	<< deadlayer1Material -> GetName()
			<< "\n Dead layer 2 Thickness         (um) : " 	<< deadlayer2_thick/um
			<< "\n Dead layer 2 material               : " 	<< deadlayer2Material -> GetName()
			<< "\n Dead layer 3 Thickness         (um) : " 	<< deadlayer3_thick/um
			<< "\n Dead layer 3 material               : " 	<< deadlayer3Material -> GetName()
			<< "\n PCB shielding layer Thickness  (um) : " 	<< pcbs_thick/um
			<< "\n PCB shielding layer material        : " 	<< pcbsMaterial -> GetName()
			<< "\n PCB layer 1 Thickness          (mm) : " 	<< pcb1_thick/mm
			<< "\n PCB layer 1 material                : " 	<< pcb1Material -> GetName()
			<< "\n PCB layer 2 Thickness          (um) : " 	<< pcb2_thick/um
			<< "\n PCB layer 2 material                : " 	<< pcb2Material -> GetName()
			<< "\n PCB layer 3 Thickness          (mm) : " 	<< pcb3_thick/mm
			<< "\n PCB layer 3 material                : " 	<< pcb3Material -> GetName()
			<< "\n Backshield 1 Thickness         (mm) : " 	<< back1_thick/mm
			<< "\n Backshield 1 material               : " 	<< back1Material -> GetName()
			<< "\n Backshield 2 Thickness         (mm) : " 	<< back2_thick/mm
			<< "\n Backshield 2 material               : " 	<< back2Material -> GetName()
			<< "\n Frame Thickness                (cm) : " 	<< frame_thick/cm
			<< "\n Frame material                      : " 	<< frameMaterial -> GetName()
			<< "\n External Sideframe Width       (mm) : " 	<< sideframe1_width/mm
			<< "\n External Sideframe material         : " 	<< sideframe1Material -> GetName()
			<< "\n Internal Sideframe Width       (mm) : " 	<< sideframe2_width/mm
			<< "\n Internal Sideframe material         : " 	<< sideframe2Material -> GetName();
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


