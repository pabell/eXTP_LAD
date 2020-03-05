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
#include "G4Trd.hh"
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

#include "globals.hh"

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
    mountingplate_log(0),
    optics_log(0),
    wfmdummy_log(0),
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
    plateSdd04_phys(0),
    plateSdd05_phys(0),
    plateSdd06_phys(0),
    plateSdd07_phys(0),
    plateSdd08_phys(0),
    plateSdd09_phys(0),
    plateSdd10_phys(0),
    plateSdd11_phys(0),
    plateSdd12_phys(0),
    plateSdd13_phys(0),
    plateSdd14_phys(0),
    plateSdd15_phys(0),
    plateSdd16_phys(0),
    plateSdd17_phys(0),
    plateSdd18_phys(0),
    plateSdd19_phys(0),
    plateSdd20_phys(0),
    plateSdd21_phys(0),
    plateSdd22_phys(0),
    plateSdd23_phys(0),
    plateSdd24_phys(0),
    plateSdd25_phys(0),
    plateSdd26_phys(0),
    plateSdd27_phys(0),
    plateSdd28_phys(0),
    plateSdd29_phys(0),
    plateSdd30_phys(0),
    plateSdd31_phys(0),
    plateSdd32_phys(0),
    plateSdd33_phys(0),
    plateSdd34_phys(0),
    plateSdd35_phys(0),
    plateSdd36_phys(0),
    plateSdd37_phys(0),
    plateSdd38_phys(0),
    plateSdd39_phys(0),
    sdd_phys(0),
    plateColl00_phys(0),
    plateColl01_phys(0),
    plateColl02_phys(0),
    plateColl03_phys(0),
    plateColl04_phys(0),
    plateColl05_phys(0),
    plateColl06_phys(0),
    plateColl07_phys(0),
    plateColl08_phys(0),
    plateColl09_phys(0),
    plateColl10_phys(0),
    plateColl11_phys(0),
    plateColl12_phys(0),
    plateColl13_phys(0),
    plateColl14_phys(0),
    plateColl15_phys(0),
    plateColl16_phys(0),
    plateColl17_phys(0),
    plateColl18_phys(0),
    plateColl19_phys(0),
    plateColl20_phys(0),
    plateColl21_phys(0),
    plateColl22_phys(0),
    plateColl23_phys(0),
    plateColl24_phys(0),
    plateColl25_phys(0),
    plateColl26_phys(0),
    plateColl27_phys(0),
    plateColl28_phys(0),
    plateColl29_phys(0),
    plateColl30_phys(0),
    plateColl31_phys(0),
    plateColl32_phys(0),
    plateColl33_phys(0),
    plateColl34_phys(0),
    plateColl35_phys(0),
    plateColl36_phys(0),
    plateColl37_phys(0),
    plateColl38_phys(0),
    plateColl39_phys(0),
	coll_phys(0),
    thermalblanketA00_phys(0),
    thermalblanketA01_phys(0),
    thermalblanketA02_phys(0),
    thermalblanketA03_phys(0),
    thermalblanketA04_phys(0),
    thermalblanketA05_phys(0),
    thermalblanketA06_phys(0),
    thermalblanketA07_phys(0),
    thermalblanketA08_phys(0),
    thermalblanketA09_phys(0),
    thermalblanketA10_phys(0),
    thermalblanketA11_phys(0),
    thermalblanketA12_phys(0),
    thermalblanketA13_phys(0),
    thermalblanketA14_phys(0),
    thermalblanketA15_phys(0),
    thermalblanketA16_phys(0),
    thermalblanketA17_phys(0),
    thermalblanketA18_phys(0),
    thermalblanketA19_phys(0),
    thermalblanketA20_phys(0),
    thermalblanketA21_phys(0),
    thermalblanketA22_phys(0),
    thermalblanketA23_phys(0),
    thermalblanketA24_phys(0),
    thermalblanketA25_phys(0),
    thermalblanketA26_phys(0),
    thermalblanketA27_phys(0),
    thermalblanketA28_phys(0),
    thermalblanketA29_phys(0),
    thermalblanketA30_phys(0),
    thermalblanketA31_phys(0),
    thermalblanketA32_phys(0),
    thermalblanketA33_phys(0),
    thermalblanketA34_phys(0),
    thermalblanketA35_phys(0),
    thermalblanketA36_phys(0),
    thermalblanketA37_phys(0),
    thermalblanketA38_phys(0),
    thermalblanketA39_phys(0),
    thermalblanketB00_phys(0),
    thermalblanketB01_phys(0),
    thermalblanketB02_phys(0),
    thermalblanketB03_phys(0),
    thermalblanketB04_phys(0),
    thermalblanketB05_phys(0),
    thermalblanketB06_phys(0),
    thermalblanketB07_phys(0),
    thermalblanketB08_phys(0),
    thermalblanketB09_phys(0),
    thermalblanketB10_phys(0),
    thermalblanketB11_phys(0),
    thermalblanketB12_phys(0),
    thermalblanketB13_phys(0),
    thermalblanketB14_phys(0),
    thermalblanketB15_phys(0),
    thermalblanketB16_phys(0),
    thermalblanketB17_phys(0),
    thermalblanketB18_phys(0),
    thermalblanketB19_phys(0),
    thermalblanketB20_phys(0),
    thermalblanketB21_phys(0),
    thermalblanketB22_phys(0),
    thermalblanketB23_phys(0),
    thermalblanketB24_phys(0),
    thermalblanketB25_phys(0),
    thermalblanketB26_phys(0),
    thermalblanketB27_phys(0),
    thermalblanketB28_phys(0),
    thermalblanketB29_phys(0),
    thermalblanketB30_phys(0),
    thermalblanketB31_phys(0),
    thermalblanketB32_phys(0),
    thermalblanketB33_phys(0),
    thermalblanketB34_phys(0),
    thermalblanketB35_phys(0),
    thermalblanketB36_phys(0),
    thermalblanketB37_phys(0),
    thermalblanketB38_phys(0),
    thermalblanketB39_phys(0),
    plateDeadlayerA00_phys(0),
    plateDeadlayerA01_phys(0),
    plateDeadlayerA02_phys(0),
    plateDeadlayerA03_phys(0),
    plateDeadlayerA04_phys(0),
    plateDeadlayerA05_phys(0),
    plateDeadlayerA06_phys(0),
    plateDeadlayerA07_phys(0),
    plateDeadlayerA08_phys(0),
    plateDeadlayerA09_phys(0),
    plateDeadlayerA10_phys(0),
    plateDeadlayerA11_phys(0),
    plateDeadlayerA12_phys(0),
    plateDeadlayerA13_phys(0),
    plateDeadlayerA14_phys(0),
    plateDeadlayerA15_phys(0),
    plateDeadlayerA16_phys(0),
    plateDeadlayerA17_phys(0),
    plateDeadlayerA18_phys(0),
    plateDeadlayerA19_phys(0),
    plateDeadlayerA20_phys(0),
    plateDeadlayerA21_phys(0),
    plateDeadlayerA22_phys(0),
    plateDeadlayerA23_phys(0),
    plateDeadlayerA24_phys(0),
    plateDeadlayerA25_phys(0),
    plateDeadlayerA26_phys(0),
    plateDeadlayerA27_phys(0),
    plateDeadlayerA28_phys(0),
    plateDeadlayerA29_phys(0),
    plateDeadlayerA30_phys(0),
    plateDeadlayerA31_phys(0),
    plateDeadlayerA32_phys(0),
    plateDeadlayerA33_phys(0),
    plateDeadlayerA34_phys(0),
    plateDeadlayerA35_phys(0),
    plateDeadlayerA36_phys(0),
    plateDeadlayerA37_phys(0),
    plateDeadlayerA38_phys(0),
    plateDeadlayerA39_phys(0),
	deadlayerA_phys(0),
    plateDeadlayerB00_phys(0),
    plateDeadlayerB01_phys(0),
    plateDeadlayerB02_phys(0),
    plateDeadlayerB03_phys(0),
    plateDeadlayerB04_phys(0),
    plateDeadlayerB05_phys(0),
    plateDeadlayerB06_phys(0),
    plateDeadlayerB07_phys(0),
    plateDeadlayerB08_phys(0),
    plateDeadlayerB09_phys(0),
    plateDeadlayerB10_phys(0),
    plateDeadlayerB11_phys(0),
    plateDeadlayerB12_phys(0),
    plateDeadlayerB13_phys(0),
    plateDeadlayerB14_phys(0),
    plateDeadlayerB15_phys(0),
    plateDeadlayerB16_phys(0),
    plateDeadlayerB17_phys(0),
    plateDeadlayerB18_phys(0),
    plateDeadlayerB19_phys(0),
    plateDeadlayerB20_phys(0),
    plateDeadlayerB21_phys(0),
    plateDeadlayerB22_phys(0),
    plateDeadlayerB23_phys(0),
    plateDeadlayerB24_phys(0),
    plateDeadlayerB25_phys(0),
    plateDeadlayerB26_phys(0),
    plateDeadlayerB27_phys(0),
    plateDeadlayerB28_phys(0),
    plateDeadlayerB29_phys(0),
    plateDeadlayerB30_phys(0),
    plateDeadlayerB31_phys(0),
    plateDeadlayerB32_phys(0),
    plateDeadlayerB33_phys(0),
    plateDeadlayerB34_phys(0),
    plateDeadlayerB35_phys(0),
    plateDeadlayerB36_phys(0),
    plateDeadlayerB37_phys(0),
    plateDeadlayerB38_phys(0),
    plateDeadlayerB39_phys(0),
	deadlayerB_phys(0),
    plateDeadlayerC00_phys(0),
    plateDeadlayerC01_phys(0),
    plateDeadlayerC02_phys(0),
    plateDeadlayerC03_phys(0),
    plateDeadlayerC04_phys(0),
    plateDeadlayerC05_phys(0),
    plateDeadlayerC06_phys(0),
    plateDeadlayerC07_phys(0),
    plateDeadlayerC08_phys(0),
    plateDeadlayerC09_phys(0),
    plateDeadlayerC10_phys(0),
    plateDeadlayerC11_phys(0),
    plateDeadlayerC12_phys(0),
    plateDeadlayerC13_phys(0),
    plateDeadlayerC14_phys(0),
    plateDeadlayerC15_phys(0),
    plateDeadlayerC16_phys(0),
    plateDeadlayerC17_phys(0),
    plateDeadlayerC18_phys(0),
    plateDeadlayerC19_phys(0),
    plateDeadlayerC20_phys(0),
    plateDeadlayerC21_phys(0),
    plateDeadlayerC22_phys(0),
    plateDeadlayerC23_phys(0),
    plateDeadlayerC24_phys(0),
    plateDeadlayerC25_phys(0),
    plateDeadlayerC26_phys(0),
    plateDeadlayerC27_phys(0),
    plateDeadlayerC28_phys(0),
    plateDeadlayerC29_phys(0),
    plateDeadlayerC30_phys(0),
    plateDeadlayerC31_phys(0),
    plateDeadlayerC32_phys(0),
    plateDeadlayerC33_phys(0),
    plateDeadlayerC34_phys(0),
    plateDeadlayerC35_phys(0),
    plateDeadlayerC36_phys(0),
    plateDeadlayerC37_phys(0),
    plateDeadlayerC38_phys(0),
    plateDeadlayerC39_phys(0),
	deadlayerC_phys(0),
    platePcbs00_phys(0),
    platePcbs01_phys(0),
    platePcbs02_phys(0),
    platePcbs03_phys(0),
    platePcbs04_phys(0),
    platePcbs05_phys(0),
    platePcbs06_phys(0),
    platePcbs07_phys(0),
    platePcbs08_phys(0),
    platePcbs09_phys(0),
    platePcbs10_phys(0),
    platePcbs11_phys(0),
    platePcbs12_phys(0),
    platePcbs13_phys(0),
    platePcbs14_phys(0),
    platePcbs15_phys(0),
    platePcbs16_phys(0),
    platePcbs17_phys(0),
    platePcbs18_phys(0),
    platePcbs19_phys(0),
    platePcbs20_phys(0),
    platePcbs21_phys(0),
    platePcbs22_phys(0),
    platePcbs23_phys(0),
    platePcbs24_phys(0),
    platePcbs25_phys(0),
    platePcbs26_phys(0),
    platePcbs27_phys(0),
    platePcbs28_phys(0),
    platePcbs29_phys(0),
    platePcbs30_phys(0),
    platePcbs31_phys(0),
    platePcbs32_phys(0),
    platePcbs33_phys(0),
    platePcbs34_phys(0),
    platePcbs35_phys(0),
    platePcbs36_phys(0),
    platePcbs37_phys(0),
    platePcbs38_phys(0),
    platePcbs39_phys(0),
	pcbs_phys(0),
    platePcbA00_phys(0),
    platePcbA01_phys(0),
    platePcbA02_phys(0),
    platePcbA03_phys(0),
    platePcbA04_phys(0),
    platePcbA05_phys(0),
    platePcbA06_phys(0),
    platePcbA07_phys(0),
    platePcbA08_phys(0),
    platePcbA09_phys(0),
    platePcbA10_phys(0),
    platePcbA11_phys(0),
    platePcbA12_phys(0),
    platePcbA13_phys(0),
    platePcbA14_phys(0),
    platePcbA15_phys(0),
    platePcbA16_phys(0),
    platePcbA17_phys(0),
    platePcbA18_phys(0),
    platePcbA19_phys(0),
    platePcbA20_phys(0),
    platePcbA21_phys(0),
    platePcbA22_phys(0),
    platePcbA23_phys(0),
    platePcbA24_phys(0),
    platePcbA25_phys(0),
    platePcbA26_phys(0),
    platePcbA27_phys(0),
    platePcbA28_phys(0),
    platePcbA29_phys(0),
    platePcbA30_phys(0),
    platePcbA31_phys(0),
    platePcbA32_phys(0),
    platePcbA33_phys(0),
    platePcbA34_phys(0),
    platePcbA35_phys(0),
    platePcbA36_phys(0),
    platePcbA37_phys(0),
    platePcbA38_phys(0),
    platePcbA39_phys(0),
	pcbA_phys(0),
    platePcbB00_phys(0),
    platePcbB01_phys(0),
    platePcbB02_phys(0),
    platePcbB03_phys(0),
    platePcbB04_phys(0),
    platePcbB05_phys(0),
    platePcbB06_phys(0),
    platePcbB07_phys(0),
    platePcbB08_phys(0),
    platePcbB09_phys(0),
    platePcbB10_phys(0),
    platePcbB11_phys(0),
    platePcbB12_phys(0),
    platePcbB13_phys(0),
    platePcbB14_phys(0),
    platePcbB15_phys(0),
    platePcbB16_phys(0),
    platePcbB17_phys(0),
    platePcbB18_phys(0),
    platePcbB19_phys(0),
    platePcbB20_phys(0),
    platePcbB21_phys(0),
    platePcbB22_phys(0),
    platePcbB23_phys(0),
    platePcbB24_phys(0),
    platePcbB25_phys(0),
    platePcbB26_phys(0),
    platePcbB27_phys(0),
    platePcbB28_phys(0),
    platePcbB29_phys(0),
    platePcbB30_phys(0),
    platePcbB31_phys(0),
    platePcbB32_phys(0),
    platePcbB33_phys(0),
    platePcbB34_phys(0),
    platePcbB35_phys(0),
    platePcbB36_phys(0),
    platePcbB37_phys(0),
    platePcbB38_phys(0),
    platePcbB39_phys(0),
	pcbB_phys(0),
    platePcbC00_phys(0),
    platePcbC01_phys(0),
    platePcbC02_phys(0),
    platePcbC03_phys(0),
    platePcbC04_phys(0),
    platePcbC05_phys(0),
    platePcbC06_phys(0),
    platePcbC07_phys(0),
    platePcbC08_phys(0),
    platePcbC09_phys(0),
    platePcbC10_phys(0),
    platePcbC11_phys(0),
    platePcbC12_phys(0),
    platePcbC13_phys(0),
    platePcbC14_phys(0),
    platePcbC15_phys(0),
    platePcbC16_phys(0),
    platePcbC17_phys(0),
    platePcbC18_phys(0),
    platePcbC19_phys(0),
    platePcbC20_phys(0),
    platePcbC21_phys(0),
    platePcbC22_phys(0),
    platePcbC23_phys(0),
    platePcbC24_phys(0),
    platePcbC25_phys(0),
    platePcbC26_phys(0),
    platePcbC27_phys(0),
    platePcbC28_phys(0),
    platePcbC29_phys(0),
    platePcbC30_phys(0),
    platePcbC31_phys(0),
    platePcbC32_phys(0),
    platePcbC33_phys(0),
    platePcbC34_phys(0),
    platePcbC35_phys(0),
    platePcbC36_phys(0),
    platePcbC37_phys(0),
    platePcbC38_phys(0),
    platePcbC39_phys(0),
	pcbC_phys(0),
    backshieldA00_phys(0),
    backshieldA01_phys(0),
    backshieldA02_phys(0),
    backshieldA03_phys(0),
    backshieldA04_phys(0),
    backshieldA05_phys(0),
    backshieldA06_phys(0),
    backshieldA07_phys(0),
    backshieldA08_phys(0),
    backshieldA09_phys(0),
    backshieldA10_phys(0),
    backshieldA11_phys(0),
    backshieldA12_phys(0),
    backshieldA13_phys(0),
    backshieldA14_phys(0),
    backshieldA15_phys(0),
    backshieldA16_phys(0),
    backshieldA17_phys(0),
    backshieldA18_phys(0),
    backshieldA19_phys(0),
    backshieldA20_phys(0),
    backshieldA21_phys(0),
    backshieldA22_phys(0),
    backshieldA23_phys(0),
    backshieldA24_phys(0),
    backshieldA25_phys(0),
    backshieldA26_phys(0),
    backshieldA27_phys(0),
    backshieldA28_phys(0),
    backshieldA29_phys(0),
    backshieldA30_phys(0),
    backshieldA31_phys(0),
    backshieldA32_phys(0),
    backshieldA33_phys(0),
    backshieldA34_phys(0),
    backshieldA35_phys(0),
    backshieldA36_phys(0),
    backshieldA37_phys(0),
    backshieldA38_phys(0),
    backshieldA39_phys(0),
    backshieldB00_phys(0),
    backshieldB01_phys(0),
    backshieldB02_phys(0),
    backshieldB03_phys(0),
    backshieldB04_phys(0),
    backshieldB05_phys(0),
    backshieldB06_phys(0),
    backshieldB07_phys(0),
    backshieldB08_phys(0),
    backshieldB09_phys(0),
    backshieldB10_phys(0),
    backshieldB11_phys(0),
    backshieldB12_phys(0),
    backshieldB13_phys(0),
    backshieldB14_phys(0),
    backshieldB15_phys(0),
    backshieldB16_phys(0),
    backshieldB17_phys(0),
    backshieldB18_phys(0),
    backshieldB19_phys(0),
    backshieldB20_phys(0),
    backshieldB21_phys(0),
    backshieldB22_phys(0),
    backshieldB23_phys(0),
    backshieldB24_phys(0),
    backshieldB25_phys(0),
    backshieldB26_phys(0),
    backshieldB27_phys(0),
    backshieldB28_phys(0),
    backshieldB29_phys(0),
    backshieldB30_phys(0),
    backshieldB31_phys(0),
    backshieldB32_phys(0),
    backshieldB33_phys(0),
    backshieldB34_phys(0),
    backshieldB35_phys(0),
    backshieldB36_phys(0),
    backshieldB37_phys(0),
    backshieldB38_phys(0),
    backshieldB39_phys(0),
	opticalbench_phys(0),
	tower_phys(0),
	servicemodule_phys(0),
    solarpanelA_phys(0),
    solarpanelB_phys(0),
    opticalbenchcover_phys(0),
    sunshade_phys(0),
    mountingplate_phys(0),
    optics00_phys(0),
    optics01_phys(0),
    optics02_phys(0),
    optics03_phys(0),
    optics04_phys(0),
    optics05_phys(0),
    optics06_phys(0),
    optics07_phys(0),
    optics08_phys(0),
    optics09_phys(0),
    optics10_phys(0),
    optics11_phys(0),
    optics12_phys(0),
    wfmdummy00_phys(0),
    wfmdummy01_phys(0),
    wfmdummy02_phys(0),
    wfmdummy03_phys(0),
    wfmdummy04_phys(0),
    wfmdummy05_phys(0),
    defaultMaterial(0)
{
	// Size of the experimental hall
    worldSide         = 100.0 *m;

    // Define the frame numbers
    n_sdd_x = 4;
    n_sdd_y = 4;
    n_sdd_per_module = n_sdd_x*n_sdd_y;
    n_modules = 40;

	// Define the materials
	DefineMaterials();	

	// Define the parameters
	DefineParameters();
		
	// Print parameters
	PrintParameters();
	
;}		

// Destructor 
DetectorConstruction::~DetectorConstruction() { } 	

G4ThreeVector DetectorConstruction::moduleLocation(G4int moduleID, G4double innerRingRadius, G4double outerRingRadius)
{
    G4double xMod = 0*cm;
    G4double yMod = 0*cm;
    G4double zMod = 0*cm;

    G4int n_innerRingModules = 20;
    G4double innerRingGap = 75*deg;
    G4double innerRingSpacing = (360*deg - innerRingGap)/(n_innerRingModules-1);

    G4int n_outerRingModules = 16;
    G4double outerRingGap = 90*deg;
    G4double outerRingSpacing = (360*deg - outerRingGap)/(n_outerRingModules);


    G4double outerRingIsolatedDistance = outerRingRadius -  20*cm;
    
    if(moduleID < 20) // Inner ring
    {
        xMod = innerRingRadius * cos( (moduleID)*innerRingSpacing/rad + 3.1415936/2. + (innerRingGap/2.)/rad);
        yMod = innerRingRadius * sin( (moduleID)*innerRingSpacing/rad + 3.1415936/2. + (innerRingGap/2.)/rad);
    }
    else if (moduleID >= 20  && moduleID < 28) { // Outer ring, 1st sector
        xMod = outerRingRadius * cos( (moduleID-20)*outerRingSpacing/rad + 3.1415936/2. + (outerRingGap/2.)/rad);
        yMod = outerRingRadius * sin( (moduleID-20)*outerRingSpacing/rad + 3.1415936/2. + (outerRingGap/2.)/rad);
    }
    else if (moduleID >= 28  && moduleID < 36) { // Outer ring, 2nd sector
        xMod = outerRingRadius * cos( (moduleID+1-20)*outerRingSpacing/rad + 3.1415936/2. + (outerRingGap/2.)/rad);
        yMod = outerRingRadius * sin( (moduleID+1-20)*outerRingSpacing/rad + 3.1415936/2. + (outerRingGap/2.)/rad);
    }
    else if (moduleID == 36){
        xMod = 100*cm;
        yMod = outerRingIsolatedDistance;
    }
    else if (moduleID == 37){
        xMod = 30*cm;
        yMod = outerRingIsolatedDistance-15*cm;
    }
    else if (moduleID == 38){
        xMod = -30*cm;
        yMod = outerRingIsolatedDistance-15*cm;
    }
    else if (moduleID == 39){
        xMod = -100*cm;
        yMod = outerRingIsolatedDistance;
    }
    else {
        xMod = 0*cm;
        yMod = 0*cm;
    }

//    G4cout << "*** MODULE No. " << moduleID << " LOCATION X (cm): " << xMod/cm << ", Y (cm): " << yMod/cm << G4endl;
    return G4ThreeVector(xMod, yMod, zMod);
}

G4RotationMatrix* DetectorConstruction::moduleRotation(G4int moduleID)
{
    G4RotationMatrix* moduleRot = new G4RotationMatrix;

    G4int n_innerRingModules = 20;
    G4double innerRingGap = 75*deg;
    G4double innerRingSpacing = (360*deg - innerRingGap)/(n_innerRingModules-1);

    G4int n_outerRingModules = 16;
    G4double outerRingGap = 90*deg;
    G4double outerRingSpacing = (360*deg - outerRingGap)/(n_outerRingModules);

    if(moduleID < 20) // Inner ring
    {
        moduleRot->rotateZ(-((moduleID)*innerRingSpacing + 3.1415936/2. + innerRingGap/2.));
    }
    else if (moduleID >= 20  && moduleID < 28) { // Outer ring, 1st sector
        moduleRot->rotateZ(-((moduleID-20)*outerRingSpacing  + outerRingGap/2.));
    }
    else if (moduleID >= 28  && moduleID < 36) { // Outer ring, 2nd sector
        moduleRot->rotateZ(-((moduleID-20+1)*outerRingSpacing  + outerRingGap/2.));
    }
    else if (moduleID == 37){
        moduleRot->rotateZ(90*deg);
    }
    else if (moduleID == 38){
        moduleRot->rotateZ(90*deg);
    }


//    G4cout << "*** MODULE No. " << moduleID << " Rotation (deg): " << -((moduleID)*innerRingSpacing + 3.1415936/2. + innerRingGap/2.) << G4endl;
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
    config.readInto(read, "MOUNTINGPLATE_DIAMETER", 200.);
    G4double mntp_diameter = read *cm;
    config.readInto(read, "MOUNTINGPLATE_THICK", 2.);
    G4double mntp_thickness = read *cm;
    config.readInto(read, "OPTICS_DIAMETER", 20.);
    G4double opt_diameter = read *cm;
    config.readInto(read, "OPTICS_THICK", 20.);
    G4double opt_thickness = read *cm;

    config.readInto(read, "WFMDUMMY_DETSIDE", 15.);
    G4double wfm_ds = read *cm;
    config.readInto(read, "WFMDUMMY_MASKSIDE", 30.);
    G4double wfm_ms = read *cm;
    config.readInto(read, "WFMDUMMY_HEIGHT", 30.);
    G4double wfm_h = read *cm;



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
    SetMountingplateDiameter(mntp_diameter);
    SetMountingplateThick(mntp_thickness);
    SetOpticsDiameter(opt_diameter);
    SetOpticsThick(opt_thickness);
    
    SetWFMDummyDetside(wfm_ds);
    SetWFMDummyMaskside(wfm_ms);
    SetWFMDummyHeight(wfm_h);

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
    config.readInto<G4String>(readm, "MOUNTINGPLATE_MATERIAL", "G4_Al");
    SetMountingplateMaterial(readm);
    config.readInto<G4String>(readm, "OPTICS_MATERIAL", "EffectiveBusAluminiumSolid");
    SetOpticsMaterial(readm);
    config.readInto<G4String>(readm, "WFMDUMMY_MATERIAL", "EffectiveBusAluminiumSolid");
    SetWFMDummyMaterial(readm);


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
    G4Material* CarbonFiberReinforcedPlastic = new G4Material("CarbonFiberReinforcedPlastic", density = 1.6*g/cm3, nel = 2);
    CarbonFiberReinforcedPlastic -> AddElement(C, natoms=1);
    CarbonFiberReinforcedPlastic -> AddElement(H, natoms=2);
    
    // Fiberglass
    G4Material* Fiberglass = new G4Material("Fiberglass", density = 2.56*g/cm3, nel = 2);
    Fiberglass -> AddElement(Si, natoms=1);
    Fiberglass -> AddElement(O, natoms=2);


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
    
    G4double bus_offset_z = sdd_thick/2. + pcbs_thick + pcbA_thick + pcbB_thick + pcbC_thick + backshieldA_thick + backshieldB_thick;

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

    G4double offsetRingRadius = 10*cm; // TODO: do not hardcode offset
    G4double innerRingRadius = tower_diameter/2. + moduleframe_side_x/2. + offsetRingRadius;
    G4double outerRingRadius = innerRingRadius +  moduleframe_side_x/2. +  moduleframe_side_y/2. + offsetRingRadius;

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
                                      moduleLocation(0, innerRingRadius, outerRingRadius),
                                      plateSdd_log,
                                      "plateSdd00_phys",
                                      experimentalHall_log,
                                      false,
                                      0);

    plateSdd01_phys = new G4PVPlacement(moduleRotation(1),
                                       moduleLocation(1, innerRingRadius, outerRingRadius),
                                       plateSdd_log,
                                       "plateSdd01_phys",
                                       experimentalHall_log,
                                       false,
                                       0);
    plateSdd02_phys = new G4PVPlacement(moduleRotation(2),
                                        moduleLocation(2, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd02_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd03_phys = new G4PVPlacement(moduleRotation(3),
                                        moduleLocation(3, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd03_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd04_phys = new G4PVPlacement(moduleRotation(4),
                                        moduleLocation(4, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd04_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd05_phys = new G4PVPlacement(moduleRotation(5),
                                        moduleLocation(5, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd05_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd06_phys = new G4PVPlacement(moduleRotation(6),
                                        moduleLocation(6, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd06_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd07_phys = new G4PVPlacement(moduleRotation(7),
                                        moduleLocation(7, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd07_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd08_phys = new G4PVPlacement(moduleRotation(8),
                                        moduleLocation(8, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd08_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd09_phys = new G4PVPlacement(moduleRotation(9),
                                        moduleLocation(9, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd09_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd10_phys = new G4PVPlacement(moduleRotation(10),
                                        moduleLocation(10, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd10_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd11_phys = new G4PVPlacement(moduleRotation(11),
                                        moduleLocation(11, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd11_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd12_phys = new G4PVPlacement(moduleRotation(12),
                                        moduleLocation(12, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd12_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd13_phys = new G4PVPlacement(moduleRotation(13),
                                        moduleLocation(13, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd13_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd14_phys = new G4PVPlacement(moduleRotation(14),
                                        moduleLocation(14, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd14_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd15_phys = new G4PVPlacement(moduleRotation(15),
                                        moduleLocation(15, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd15_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd16_phys = new G4PVPlacement(moduleRotation(16),
                                        moduleLocation(16, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd16_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd17_phys = new G4PVPlacement(moduleRotation(17),
                                        moduleLocation(17, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd17_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd18_phys = new G4PVPlacement(moduleRotation(18),
                                        moduleLocation(18, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd18_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd19_phys = new G4PVPlacement(moduleRotation(19),
                                        moduleLocation(19, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd19_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd20_phys = new G4PVPlacement(moduleRotation(20),
                                        moduleLocation(20, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd20_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd21_phys = new G4PVPlacement(moduleRotation(21),
                                        moduleLocation(21, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd21_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd22_phys = new G4PVPlacement(moduleRotation(22),
                                        moduleLocation(22, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd22_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd23_phys = new G4PVPlacement(moduleRotation(23),
                                        moduleLocation(23, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd23_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd24_phys = new G4PVPlacement(moduleRotation(24),
                                        moduleLocation(24, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd24_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd25_phys = new G4PVPlacement(moduleRotation(25),
                                        moduleLocation(25, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd25_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd26_phys = new G4PVPlacement(moduleRotation(26),
                                        moduleLocation(26, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd26_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd27_phys = new G4PVPlacement(moduleRotation(27),
                                        moduleLocation(27, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd27_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd28_phys = new G4PVPlacement(moduleRotation(28),
                                        moduleLocation(28, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd28_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd29_phys = new G4PVPlacement(moduleRotation(29),
                                        moduleLocation(29, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd29_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd30_phys = new G4PVPlacement(moduleRotation(30),
                                        moduleLocation(30, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd30_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd31_phys = new G4PVPlacement(moduleRotation(31),
                                        moduleLocation(31, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd31_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd32_phys = new G4PVPlacement(moduleRotation(32),
                                        moduleLocation(32, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd32_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd33_phys = new G4PVPlacement(moduleRotation(33),
                                        moduleLocation(33, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd33_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd34_phys = new G4PVPlacement(moduleRotation(34),
                                        moduleLocation(34, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd34_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd35_phys = new G4PVPlacement(moduleRotation(35),
                                        moduleLocation(35, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd35_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd36_phys = new G4PVPlacement(moduleRotation(36),
                                        moduleLocation(36, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd36_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd37_phys = new G4PVPlacement(moduleRotation(37),
                                        moduleLocation(37, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd37_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd38_phys = new G4PVPlacement(moduleRotation(38),
                                        moduleLocation(38, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd38_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateSdd39_phys = new G4PVPlacement(moduleRotation(39),
                                        moduleLocation(39, innerRingRadius, outerRingRadius),
                                        plateSdd_log,
                                        "plateSdd39_phys",
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
                                        G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                        plateColl_log,
                                        "plateColl00_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    
    plateColl01_phys = new G4PVPlacement(moduleRotation(1),
                                        G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                        plateColl_log,
                                        "plateColl01_phys",
                                        experimentalHall_log,
                                        false,
                                        0);
    plateColl02_phys = new G4PVPlacement(moduleRotation(2),
                                         G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl02_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl03_phys = new G4PVPlacement(moduleRotation(3),
                                         G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl03_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl04_phys = new G4PVPlacement(moduleRotation(4),
                                         G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl04_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl05_phys = new G4PVPlacement(moduleRotation(5),
                                         G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl05_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl06_phys = new G4PVPlacement(moduleRotation(6),
                                         G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl06_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl07_phys = new G4PVPlacement(moduleRotation(7),
                                         G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl07_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl08_phys = new G4PVPlacement(moduleRotation(8),
                                         G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl08_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl09_phys = new G4PVPlacement(moduleRotation(9),
                                         G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl09_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl10_phys = new G4PVPlacement(moduleRotation(10),
                                         G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl10_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl11_phys = new G4PVPlacement(moduleRotation(11),
                                         G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl11_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl12_phys = new G4PVPlacement(moduleRotation(12),
                                         G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl12_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl13_phys = new G4PVPlacement(moduleRotation(13),
                                         G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl13_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl14_phys = new G4PVPlacement(moduleRotation(14),
                                         G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl14_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl15_phys = new G4PVPlacement(moduleRotation(15),
                                         G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl15_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl16_phys = new G4PVPlacement(moduleRotation(16),
                                         G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl16_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl17_phys = new G4PVPlacement(moduleRotation(17),
                                         G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl17_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl18_phys = new G4PVPlacement(moduleRotation(18),
                                         G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl18_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl19_phys = new G4PVPlacement(moduleRotation(19),
                                         G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl19_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl20_phys = new G4PVPlacement(moduleRotation(20),
                                         G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl20_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl21_phys = new G4PVPlacement(moduleRotation(21),
                                         G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl21_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl22_phys = new G4PVPlacement(moduleRotation(22),
                                         G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl22_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl23_phys = new G4PVPlacement(moduleRotation(23),
                                         G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl23_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl24_phys = new G4PVPlacement(moduleRotation(24),
                                         G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl24_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl25_phys = new G4PVPlacement(moduleRotation(25),
                                         G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl25_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl26_phys = new G4PVPlacement(moduleRotation(26),
                                         G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl26_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl27_phys = new G4PVPlacement(moduleRotation(27),
                                         G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl27_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl28_phys = new G4PVPlacement(moduleRotation(28),
                                         G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl28_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl29_phys = new G4PVPlacement(moduleRotation(29),
                                         G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl29_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl30_phys = new G4PVPlacement(moduleRotation(30),
                                         G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl30_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl31_phys = new G4PVPlacement(moduleRotation(31),
                                         G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl31_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl32_phys = new G4PVPlacement(moduleRotation(32),
                                         G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl32_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl33_phys = new G4PVPlacement(moduleRotation(33),
                                         G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl33_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl34_phys = new G4PVPlacement(moduleRotation(34),
                                         G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl34_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl35_phys = new G4PVPlacement(moduleRotation(35),
                                         G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl35_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl36_phys = new G4PVPlacement(moduleRotation(36),
                                         G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl36_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl37_phys = new G4PVPlacement(moduleRotation(37),
                                         G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl37_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl38_phys = new G4PVPlacement(moduleRotation(38),
                                         G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl38_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    plateColl39_phys = new G4PVPlacement(moduleRotation(39),
                                         G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),coll_loc_z),
                                         plateColl_log,
                                         "plateColl39_phys",
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
                                               G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    thermalblanketA01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA02_phys = new G4PVPlacement(moduleRotation(2),
                                               G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA02_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA03_phys = new G4PVPlacement(moduleRotation(3),
                                               G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA03_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA04_phys = new G4PVPlacement(moduleRotation(4),
                                               G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA04_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA05_phys = new G4PVPlacement(moduleRotation(5),
                                               G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA05_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA06_phys = new G4PVPlacement(moduleRotation(6),
                                               G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA06_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA07_phys = new G4PVPlacement(moduleRotation(7),
                                               G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA07_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA08_phys = new G4PVPlacement(moduleRotation(8),
                                               G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA08_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA09_phys = new G4PVPlacement(moduleRotation(9),
                                               G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA09_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA10_phys = new G4PVPlacement(moduleRotation(10),
                                               G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA10_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA11_phys = new G4PVPlacement(moduleRotation(11),
                                               G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA11_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA12_phys = new G4PVPlacement(moduleRotation(12),
                                               G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA12_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA13_phys = new G4PVPlacement(moduleRotation(13),
                                               G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA13_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA14_phys = new G4PVPlacement(moduleRotation(14),
                                               G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA14_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA15_phys = new G4PVPlacement(moduleRotation(15),
                                               G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA15_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA16_phys = new G4PVPlacement(moduleRotation(16),
                                               G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA16_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA17_phys = new G4PVPlacement(moduleRotation(17),
                                               G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA17_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA18_phys = new G4PVPlacement(moduleRotation(18),
                                               G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA18_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA19_phys = new G4PVPlacement(moduleRotation(19),
                                               G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA19_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA20_phys = new G4PVPlacement(moduleRotation(20),
                                               G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA20_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA21_phys = new G4PVPlacement(moduleRotation(21),
                                               G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA21_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA22_phys = new G4PVPlacement(moduleRotation(22),
                                               G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA22_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA23_phys = new G4PVPlacement(moduleRotation(23),
                                               G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA23_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA24_phys = new G4PVPlacement(moduleRotation(24),
                                               G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA24_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA25_phys = new G4PVPlacement(moduleRotation(25),
                                               G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA25_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA26_phys = new G4PVPlacement(moduleRotation(26),
                                               G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA26_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA27_phys = new G4PVPlacement(moduleRotation(27),
                                               G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA27_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA28_phys = new G4PVPlacement(moduleRotation(28),
                                               G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA28_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA29_phys = new G4PVPlacement(moduleRotation(29),
                                               G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA29_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA30_phys = new G4PVPlacement(moduleRotation(30),
                                               G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA30_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA31_phys = new G4PVPlacement(moduleRotation(31),
                                               G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA31_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA32_phys = new G4PVPlacement(moduleRotation(32),
                                               G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA32_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA33_phys = new G4PVPlacement(moduleRotation(33),
                                               G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA33_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA34_phys = new G4PVPlacement(moduleRotation(34),
                                               G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA34_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA35_phys = new G4PVPlacement(moduleRotation(35),
                                               G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA35_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA36_phys = new G4PVPlacement(moduleRotation(36),
                                               G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA36_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA37_phys = new G4PVPlacement(moduleRotation(37),
                                               G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA37_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA38_phys = new G4PVPlacement(moduleRotation(38),
                                               G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA38_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketA39_phys = new G4PVPlacement(moduleRotation(39),
                                               G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),thermalblanketA_loc_z),
                                               thermalblanketA_log,
                                               "thermalblanketA39_phys",
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
                                               G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    thermalblanketB01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB02_phys = new G4PVPlacement(moduleRotation(2),
                                               G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB02_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB03_phys = new G4PVPlacement(moduleRotation(3),
                                               G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB03_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB04_phys = new G4PVPlacement(moduleRotation(4),
                                               G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB04_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB05_phys = new G4PVPlacement(moduleRotation(5),
                                               G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB05_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB06_phys = new G4PVPlacement(moduleRotation(6),
                                               G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB06_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB07_phys = new G4PVPlacement(moduleRotation(7),
                                               G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB07_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB08_phys = new G4PVPlacement(moduleRotation(8),
                                               G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB08_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB09_phys = new G4PVPlacement(moduleRotation(9),
                                               G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB09_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB10_phys = new G4PVPlacement(moduleRotation(10),
                                               G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB10_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB11_phys = new G4PVPlacement(moduleRotation(11),
                                               G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB11_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB12_phys = new G4PVPlacement(moduleRotation(12),
                                               G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB12_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB13_phys = new G4PVPlacement(moduleRotation(13),
                                               G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB13_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB14_phys = new G4PVPlacement(moduleRotation(14),
                                               G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB14_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB15_phys = new G4PVPlacement(moduleRotation(15),
                                               G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB15_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB16_phys = new G4PVPlacement(moduleRotation(16),
                                               G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB16_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB17_phys = new G4PVPlacement(moduleRotation(17),
                                               G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB17_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB18_phys = new G4PVPlacement(moduleRotation(18),
                                               G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB18_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB19_phys = new G4PVPlacement(moduleRotation(19),
                                               G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB19_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB20_phys = new G4PVPlacement(moduleRotation(20),
                                               G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB20_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB21_phys = new G4PVPlacement(moduleRotation(21),
                                               G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB21_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB22_phys = new G4PVPlacement(moduleRotation(22),
                                               G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB22_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB23_phys = new G4PVPlacement(moduleRotation(23),
                                               G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB23_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB24_phys = new G4PVPlacement(moduleRotation(24),
                                               G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB24_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB25_phys = new G4PVPlacement(moduleRotation(25),
                                               G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB25_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB26_phys = new G4PVPlacement(moduleRotation(26),
                                               G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB26_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB27_phys = new G4PVPlacement(moduleRotation(27),
                                               G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB27_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB28_phys = new G4PVPlacement(moduleRotation(28),
                                               G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB28_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB29_phys = new G4PVPlacement(moduleRotation(29),
                                               G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB29_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB30_phys = new G4PVPlacement(moduleRotation(30),
                                               G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB30_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB31_phys = new G4PVPlacement(moduleRotation(31),
                                               G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB31_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB32_phys = new G4PVPlacement(moduleRotation(32),
                                               G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB32_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB33_phys = new G4PVPlacement(moduleRotation(33),
                                               G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB33_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB34_phys = new G4PVPlacement(moduleRotation(34),
                                               G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB34_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB35_phys = new G4PVPlacement(moduleRotation(35),
                                               G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB35_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB36_phys = new G4PVPlacement(moduleRotation(36),
                                               G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB36_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB37_phys = new G4PVPlacement(moduleRotation(37),
                                               G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB37_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB38_phys = new G4PVPlacement(moduleRotation(38),
                                               G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB38_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    thermalblanketB39_phys = new G4PVPlacement(moduleRotation(39),
                                               G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),thermalblanketB_loc_z),
                                               thermalblanketB_log,
                                               "thermalblanketB39_phys",
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
                                               G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    plateDeadlayerA01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA02_phys = new G4PVPlacement(moduleRotation(2),
                                               G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA02_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA03_phys = new G4PVPlacement(moduleRotation(3),
                                               G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA03_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA04_phys = new G4PVPlacement(moduleRotation(4),
                                               G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA04_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA05_phys = new G4PVPlacement(moduleRotation(5),
                                               G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA05_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA06_phys = new G4PVPlacement(moduleRotation(6),
                                               G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA06_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA07_phys = new G4PVPlacement(moduleRotation(7),
                                               G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA07_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA08_phys = new G4PVPlacement(moduleRotation(8),
                                               G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA08_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA09_phys = new G4PVPlacement(moduleRotation(9),
                                               G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA09_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA10_phys = new G4PVPlacement(moduleRotation(10),
                                               G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA10_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA11_phys = new G4PVPlacement(moduleRotation(11),
                                               G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA11_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA12_phys = new G4PVPlacement(moduleRotation(12),
                                               G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA12_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA13_phys = new G4PVPlacement(moduleRotation(13),
                                               G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA13_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA14_phys = new G4PVPlacement(moduleRotation(14),
                                               G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA14_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA15_phys = new G4PVPlacement(moduleRotation(15),
                                               G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA15_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA16_phys = new G4PVPlacement(moduleRotation(16),
                                               G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA16_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA17_phys = new G4PVPlacement(moduleRotation(17),
                                               G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA17_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA18_phys = new G4PVPlacement(moduleRotation(18),
                                               G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA18_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA19_phys = new G4PVPlacement(moduleRotation(19),
                                               G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA19_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA20_phys = new G4PVPlacement(moduleRotation(20),
                                               G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA20_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA21_phys = new G4PVPlacement(moduleRotation(21),
                                               G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA21_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA22_phys = new G4PVPlacement(moduleRotation(22),
                                               G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA22_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA23_phys = new G4PVPlacement(moduleRotation(23),
                                               G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA23_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA24_phys = new G4PVPlacement(moduleRotation(24),
                                               G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA24_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA25_phys = new G4PVPlacement(moduleRotation(25),
                                               G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA25_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA26_phys = new G4PVPlacement(moduleRotation(26),
                                               G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA26_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA27_phys = new G4PVPlacement(moduleRotation(27),
                                               G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA27_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA28_phys = new G4PVPlacement(moduleRotation(28),
                                               G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA28_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA29_phys = new G4PVPlacement(moduleRotation(29),
                                               G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA29_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA30_phys = new G4PVPlacement(moduleRotation(30),
                                               G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA30_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA31_phys = new G4PVPlacement(moduleRotation(31),
                                               G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA31_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA32_phys = new G4PVPlacement(moduleRotation(32),
                                               G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA32_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA33_phys = new G4PVPlacement(moduleRotation(33),
                                               G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA33_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA34_phys = new G4PVPlacement(moduleRotation(34),
                                               G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA34_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA35_phys = new G4PVPlacement(moduleRotation(35),
                                               G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA35_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA36_phys = new G4PVPlacement(moduleRotation(36),
                                               G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA36_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA37_phys = new G4PVPlacement(moduleRotation(37),
                                               G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA37_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA38_phys = new G4PVPlacement(moduleRotation(38),
                                               G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA38_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerA39_phys = new G4PVPlacement(moduleRotation(39),
                                               G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),deadlayerA_loc_z),
                                               plateDeadlayerA_log,
                                               "plateDeadlayerA39_phys",
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
                                               G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    plateDeadlayerB01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB02_phys = new G4PVPlacement(moduleRotation(2),
                                               G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB02_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB03_phys = new G4PVPlacement(moduleRotation(3),
                                               G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB03_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB04_phys = new G4PVPlacement(moduleRotation(4),
                                               G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB04_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB05_phys = new G4PVPlacement(moduleRotation(5),
                                               G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB05_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB06_phys = new G4PVPlacement(moduleRotation(6),
                                               G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB06_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB07_phys = new G4PVPlacement(moduleRotation(7),
                                               G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB07_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB08_phys = new G4PVPlacement(moduleRotation(8),
                                               G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB08_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB09_phys = new G4PVPlacement(moduleRotation(9),
                                               G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB09_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB10_phys = new G4PVPlacement(moduleRotation(10),
                                               G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB10_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB11_phys = new G4PVPlacement(moduleRotation(11),
                                               G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB11_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB12_phys = new G4PVPlacement(moduleRotation(12),
                                               G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB12_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB13_phys = new G4PVPlacement(moduleRotation(13),
                                               G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB13_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB14_phys = new G4PVPlacement(moduleRotation(14),
                                               G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB14_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB15_phys = new G4PVPlacement(moduleRotation(15),
                                               G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB15_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB16_phys = new G4PVPlacement(moduleRotation(16),
                                               G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB16_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB17_phys = new G4PVPlacement(moduleRotation(17),
                                               G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB17_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB18_phys = new G4PVPlacement(moduleRotation(18),
                                               G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB18_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB19_phys = new G4PVPlacement(moduleRotation(19),
                                               G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB19_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB20_phys = new G4PVPlacement(moduleRotation(20),
                                               G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB20_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB21_phys = new G4PVPlacement(moduleRotation(21),
                                               G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB21_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB22_phys = new G4PVPlacement(moduleRotation(22),
                                               G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB22_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB23_phys = new G4PVPlacement(moduleRotation(23),
                                               G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB23_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB24_phys = new G4PVPlacement(moduleRotation(24),
                                               G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB24_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB25_phys = new G4PVPlacement(moduleRotation(25),
                                               G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB25_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB26_phys = new G4PVPlacement(moduleRotation(26),
                                               G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB26_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB27_phys = new G4PVPlacement(moduleRotation(27),
                                               G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB27_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB28_phys = new G4PVPlacement(moduleRotation(28),
                                               G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB28_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB29_phys = new G4PVPlacement(moduleRotation(29),
                                               G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB29_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB30_phys = new G4PVPlacement(moduleRotation(30),
                                               G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB30_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB31_phys = new G4PVPlacement(moduleRotation(31),
                                               G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB31_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB32_phys = new G4PVPlacement(moduleRotation(32),
                                               G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB32_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB33_phys = new G4PVPlacement(moduleRotation(33),
                                               G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB33_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB34_phys = new G4PVPlacement(moduleRotation(34),
                                               G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB34_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB35_phys = new G4PVPlacement(moduleRotation(35),
                                               G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB35_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB36_phys = new G4PVPlacement(moduleRotation(36),
                                               G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB36_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB37_phys = new G4PVPlacement(moduleRotation(37),
                                               G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB37_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB38_phys = new G4PVPlacement(moduleRotation(38),
                                               G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB38_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerB39_phys = new G4PVPlacement(moduleRotation(39),
                                               G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),deadlayerB_loc_z),
                                               plateDeadlayerB_log,
                                               "plateDeadlayerB39_phys",
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
                                               G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    
    plateDeadlayerC01_phys = new G4PVPlacement(moduleRotation(1),
                                               G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC01_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC02_phys = new G4PVPlacement(moduleRotation(2),
                                               G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC02_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC03_phys = new G4PVPlacement(moduleRotation(3),
                                               G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC03_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC04_phys = new G4PVPlacement(moduleRotation(4),
                                               G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC04_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC05_phys = new G4PVPlacement(moduleRotation(5),
                                               G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC05_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC06_phys = new G4PVPlacement(moduleRotation(6),
                                               G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC06_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC07_phys = new G4PVPlacement(moduleRotation(7),
                                               G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC07_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC08_phys = new G4PVPlacement(moduleRotation(8),
                                               G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC08_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC09_phys = new G4PVPlacement(moduleRotation(9),
                                               G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC09_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC10_phys = new G4PVPlacement(moduleRotation(10),
                                               G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC10_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC11_phys = new G4PVPlacement(moduleRotation(11),
                                               G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC11_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC12_phys = new G4PVPlacement(moduleRotation(12),
                                               G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC12_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC13_phys = new G4PVPlacement(moduleRotation(13),
                                               G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC13_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC14_phys = new G4PVPlacement(moduleRotation(14),
                                               G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC14_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC15_phys = new G4PVPlacement(moduleRotation(15),
                                               G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC15_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC16_phys = new G4PVPlacement(moduleRotation(16),
                                               G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC16_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC17_phys = new G4PVPlacement(moduleRotation(17),
                                               G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC17_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC18_phys = new G4PVPlacement(moduleRotation(18),
                                               G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC18_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC19_phys = new G4PVPlacement(moduleRotation(19),
                                               G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC19_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC20_phys = new G4PVPlacement(moduleRotation(20),
                                               G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC20_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC21_phys = new G4PVPlacement(moduleRotation(21),
                                               G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC21_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC22_phys = new G4PVPlacement(moduleRotation(22),
                                               G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC22_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC23_phys = new G4PVPlacement(moduleRotation(23),
                                               G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC23_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC24_phys = new G4PVPlacement(moduleRotation(24),
                                               G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC24_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC25_phys = new G4PVPlacement(moduleRotation(25),
                                               G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC25_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC26_phys = new G4PVPlacement(moduleRotation(26),
                                               G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC26_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC27_phys = new G4PVPlacement(moduleRotation(27),
                                               G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC27_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC28_phys = new G4PVPlacement(moduleRotation(28),
                                               G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC28_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC29_phys = new G4PVPlacement(moduleRotation(29),
                                               G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC29_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC30_phys = new G4PVPlacement(moduleRotation(30),
                                               G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC30_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC31_phys = new G4PVPlacement(moduleRotation(31),
                                               G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC31_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC32_phys = new G4PVPlacement(moduleRotation(32),
                                               G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC32_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC33_phys = new G4PVPlacement(moduleRotation(33),
                                               G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC33_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC34_phys = new G4PVPlacement(moduleRotation(34),
                                               G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC34_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC35_phys = new G4PVPlacement(moduleRotation(35),
                                               G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC35_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC36_phys = new G4PVPlacement(moduleRotation(36),
                                               G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC36_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC37_phys = new G4PVPlacement(moduleRotation(37),
                                               G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC37_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC38_phys = new G4PVPlacement(moduleRotation(38),
                                               G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC38_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
    plateDeadlayerC39_phys = new G4PVPlacement(moduleRotation(39),
                                               G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),deadlayerC_loc_z),
                                               plateDeadlayerC_log,
                                               "plateDeadlayerC39_phys",
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
                                         G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    
    platePcbs01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs02_phys = new G4PVPlacement(moduleRotation(2),
                                         G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs02_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs03_phys = new G4PVPlacement(moduleRotation(3),
                                         G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs03_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs04_phys = new G4PVPlacement(moduleRotation(4),
                                         G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs04_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs05_phys = new G4PVPlacement(moduleRotation(5),
                                         G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs05_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs06_phys = new G4PVPlacement(moduleRotation(6),
                                         G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs06_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs07_phys = new G4PVPlacement(moduleRotation(7),
                                         G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs07_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs08_phys = new G4PVPlacement(moduleRotation(8),
                                         G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs08_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs09_phys = new G4PVPlacement(moduleRotation(9),
                                         G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs09_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs10_phys = new G4PVPlacement(moduleRotation(10),
                                         G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs10_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs11_phys = new G4PVPlacement(moduleRotation(11),
                                         G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs11_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs12_phys = new G4PVPlacement(moduleRotation(12),
                                         G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs12_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs13_phys = new G4PVPlacement(moduleRotation(13),
                                         G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs13_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs14_phys = new G4PVPlacement(moduleRotation(14),
                                         G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs14_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs15_phys = new G4PVPlacement(moduleRotation(15),
                                         G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs15_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs16_phys = new G4PVPlacement(moduleRotation(16),
                                         G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs16_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs17_phys = new G4PVPlacement(moduleRotation(17),
                                         G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs17_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs18_phys = new G4PVPlacement(moduleRotation(18),
                                         G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs18_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs19_phys = new G4PVPlacement(moduleRotation(19),
                                         G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs19_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs20_phys = new G4PVPlacement(moduleRotation(20),
                                         G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs20_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs21_phys = new G4PVPlacement(moduleRotation(21),
                                         G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs21_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs22_phys = new G4PVPlacement(moduleRotation(22),
                                         G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs22_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs23_phys = new G4PVPlacement(moduleRotation(23),
                                         G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs23_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs24_phys = new G4PVPlacement(moduleRotation(24),
                                         G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs24_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs25_phys = new G4PVPlacement(moduleRotation(25),
                                         G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs25_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs26_phys = new G4PVPlacement(moduleRotation(26),
                                         G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs26_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs27_phys = new G4PVPlacement(moduleRotation(27),
                                         G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs27_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs28_phys = new G4PVPlacement(moduleRotation(28),
                                         G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs28_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs29_phys = new G4PVPlacement(moduleRotation(29),
                                         G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs29_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs30_phys = new G4PVPlacement(moduleRotation(30),
                                         G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs30_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs31_phys = new G4PVPlacement(moduleRotation(31),
                                         G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs31_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs32_phys = new G4PVPlacement(moduleRotation(32),
                                         G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs32_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs33_phys = new G4PVPlacement(moduleRotation(33),
                                         G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs33_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs34_phys = new G4PVPlacement(moduleRotation(34),
                                         G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs34_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs35_phys = new G4PVPlacement(moduleRotation(35),
                                         G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs35_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs36_phys = new G4PVPlacement(moduleRotation(36),
                                         G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs36_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs37_phys = new G4PVPlacement(moduleRotation(37),
                                         G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs37_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs38_phys = new G4PVPlacement(moduleRotation(38),
                                         G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs38_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbs39_phys = new G4PVPlacement(moduleRotation(39),
                                         G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),pcbs_loc_z),
                                         platePcbs_log,
                                         "platePcbs39_phys",
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
                                         G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    
    platePcbA01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA02_phys = new G4PVPlacement(moduleRotation(2),
                                         G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA02_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA03_phys = new G4PVPlacement(moduleRotation(3),
                                         G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA03_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA04_phys = new G4PVPlacement(moduleRotation(4),
                                         G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA04_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA05_phys = new G4PVPlacement(moduleRotation(5),
                                         G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA05_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA06_phys = new G4PVPlacement(moduleRotation(6),
                                         G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA06_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA07_phys = new G4PVPlacement(moduleRotation(7),
                                         G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA07_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA08_phys = new G4PVPlacement(moduleRotation(8),
                                         G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA08_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA09_phys = new G4PVPlacement(moduleRotation(9),
                                         G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA09_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA10_phys = new G4PVPlacement(moduleRotation(10),
                                         G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA10_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA11_phys = new G4PVPlacement(moduleRotation(11),
                                         G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA11_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA12_phys = new G4PVPlacement(moduleRotation(12),
                                         G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA12_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA13_phys = new G4PVPlacement(moduleRotation(13),
                                         G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA13_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA14_phys = new G4PVPlacement(moduleRotation(14),
                                         G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA14_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA15_phys = new G4PVPlacement(moduleRotation(15),
                                         G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA15_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA16_phys = new G4PVPlacement(moduleRotation(16),
                                         G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA16_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA17_phys = new G4PVPlacement(moduleRotation(17),
                                         G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA17_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA18_phys = new G4PVPlacement(moduleRotation(18),
                                         G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA18_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA19_phys = new G4PVPlacement(moduleRotation(19),
                                         G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA19_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA20_phys = new G4PVPlacement(moduleRotation(20),
                                         G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA20_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA21_phys = new G4PVPlacement(moduleRotation(21),
                                         G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA21_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA22_phys = new G4PVPlacement(moduleRotation(22),
                                         G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA22_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA23_phys = new G4PVPlacement(moduleRotation(23),
                                         G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA23_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA24_phys = new G4PVPlacement(moduleRotation(24),
                                         G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA24_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA25_phys = new G4PVPlacement(moduleRotation(25),
                                         G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA25_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA26_phys = new G4PVPlacement(moduleRotation(26),
                                         G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA26_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA27_phys = new G4PVPlacement(moduleRotation(27),
                                         G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA27_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA28_phys = new G4PVPlacement(moduleRotation(28),
                                         G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA28_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA29_phys = new G4PVPlacement(moduleRotation(29),
                                         G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA29_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA30_phys = new G4PVPlacement(moduleRotation(30),
                                         G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA30_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA31_phys = new G4PVPlacement(moduleRotation(31),
                                         G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA31_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA32_phys = new G4PVPlacement(moduleRotation(32),
                                         G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA32_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA33_phys = new G4PVPlacement(moduleRotation(33),
                                         G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA33_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA34_phys = new G4PVPlacement(moduleRotation(34),
                                         G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA34_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA35_phys = new G4PVPlacement(moduleRotation(35),
                                         G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA35_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA36_phys = new G4PVPlacement(moduleRotation(36),
                                         G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA36_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA37_phys = new G4PVPlacement(moduleRotation(37),
                                         G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA37_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA38_phys = new G4PVPlacement(moduleRotation(38),
                                         G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA38_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbA39_phys = new G4PVPlacement(moduleRotation(39),
                                         G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),pcbA_loc_z),
                                         platePcbA_log,
                                         "platePcbA39_phys",
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
                                         G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    
    platePcbB01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB02_phys = new G4PVPlacement(moduleRotation(2),
                                         G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB02_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB03_phys = new G4PVPlacement(moduleRotation(3),
                                         G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB03_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB04_phys = new G4PVPlacement(moduleRotation(4),
                                         G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB04_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB05_phys = new G4PVPlacement(moduleRotation(5),
                                         G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB05_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB06_phys = new G4PVPlacement(moduleRotation(6),
                                         G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB06_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB07_phys = new G4PVPlacement(moduleRotation(7),
                                         G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB07_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB08_phys = new G4PVPlacement(moduleRotation(8),
                                         G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB08_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB09_phys = new G4PVPlacement(moduleRotation(9),
                                         G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB09_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB10_phys = new G4PVPlacement(moduleRotation(10),
                                         G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB10_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB11_phys = new G4PVPlacement(moduleRotation(11),
                                         G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB11_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB12_phys = new G4PVPlacement(moduleRotation(12),
                                         G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB12_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB13_phys = new G4PVPlacement(moduleRotation(13),
                                         G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB13_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB14_phys = new G4PVPlacement(moduleRotation(14),
                                         G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB14_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB15_phys = new G4PVPlacement(moduleRotation(15),
                                         G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB15_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB16_phys = new G4PVPlacement(moduleRotation(16),
                                         G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB16_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB17_phys = new G4PVPlacement(moduleRotation(17),
                                         G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB17_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB18_phys = new G4PVPlacement(moduleRotation(18),
                                         G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB18_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB19_phys = new G4PVPlacement(moduleRotation(19),
                                         G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB19_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB20_phys = new G4PVPlacement(moduleRotation(20),
                                         G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB20_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB21_phys = new G4PVPlacement(moduleRotation(21),
                                         G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB21_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB22_phys = new G4PVPlacement(moduleRotation(22),
                                         G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB22_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB23_phys = new G4PVPlacement(moduleRotation(23),
                                         G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB23_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB24_phys = new G4PVPlacement(moduleRotation(24),
                                         G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB24_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB25_phys = new G4PVPlacement(moduleRotation(25),
                                         G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB25_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB26_phys = new G4PVPlacement(moduleRotation(26),
                                         G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB26_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB27_phys = new G4PVPlacement(moduleRotation(27),
                                         G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB27_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB28_phys = new G4PVPlacement(moduleRotation(28),
                                         G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB28_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB29_phys = new G4PVPlacement(moduleRotation(29),
                                         G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB29_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB30_phys = new G4PVPlacement(moduleRotation(30),
                                         G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB30_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB31_phys = new G4PVPlacement(moduleRotation(31),
                                         G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB31_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB32_phys = new G4PVPlacement(moduleRotation(32),
                                         G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB32_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB33_phys = new G4PVPlacement(moduleRotation(33),
                                         G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB33_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB34_phys = new G4PVPlacement(moduleRotation(34),
                                         G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB34_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB35_phys = new G4PVPlacement(moduleRotation(35),
                                         G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB35_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB36_phys = new G4PVPlacement(moduleRotation(36),
                                         G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB36_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB37_phys = new G4PVPlacement(moduleRotation(37),
                                         G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB37_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB38_phys = new G4PVPlacement(moduleRotation(38),
                                         G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB38_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbB39_phys = new G4PVPlacement(moduleRotation(39),
                                         G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),pcbB_loc_z),
                                         platePcbB_log,
                                         "platePcbB39_phys",
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
                                         G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC00_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    
    platePcbC01_phys = new G4PVPlacement(moduleRotation(1),
                                         G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC01_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC02_phys = new G4PVPlacement(moduleRotation(2),
                                         G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC02_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC03_phys = new G4PVPlacement(moduleRotation(3),
                                         G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC03_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC04_phys = new G4PVPlacement(moduleRotation(4),
                                         G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC04_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC05_phys = new G4PVPlacement(moduleRotation(5),
                                         G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC05_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC06_phys = new G4PVPlacement(moduleRotation(6),
                                         G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC06_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC07_phys = new G4PVPlacement(moduleRotation(7),
                                         G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC07_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC08_phys = new G4PVPlacement(moduleRotation(8),
                                         G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC08_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC09_phys = new G4PVPlacement(moduleRotation(9),
                                         G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC09_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC10_phys = new G4PVPlacement(moduleRotation(10),
                                         G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC10_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC11_phys = new G4PVPlacement(moduleRotation(11),
                                         G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC11_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC12_phys = new G4PVPlacement(moduleRotation(12),
                                         G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC12_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC13_phys = new G4PVPlacement(moduleRotation(13),
                                         G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC13_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC14_phys = new G4PVPlacement(moduleRotation(14),
                                         G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC14_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC15_phys = new G4PVPlacement(moduleRotation(15),
                                         G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC15_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC16_phys = new G4PVPlacement(moduleRotation(16),
                                         G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC16_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC17_phys = new G4PVPlacement(moduleRotation(17),
                                         G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC17_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC18_phys = new G4PVPlacement(moduleRotation(18),
                                         G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC18_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC19_phys = new G4PVPlacement(moduleRotation(19),
                                         G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC19_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC20_phys = new G4PVPlacement(moduleRotation(20),
                                         G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC20_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC21_phys = new G4PVPlacement(moduleRotation(21),
                                         G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC21_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC22_phys = new G4PVPlacement(moduleRotation(22),
                                         G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC22_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC23_phys = new G4PVPlacement(moduleRotation(23),
                                         G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC23_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC24_phys = new G4PVPlacement(moduleRotation(24),
                                         G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC24_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC25_phys = new G4PVPlacement(moduleRotation(25),
                                         G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC25_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC26_phys = new G4PVPlacement(moduleRotation(26),
                                         G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC26_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC27_phys = new G4PVPlacement(moduleRotation(27),
                                         G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC27_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC28_phys = new G4PVPlacement(moduleRotation(28),
                                         G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC28_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC29_phys = new G4PVPlacement(moduleRotation(29),
                                         G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC29_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC30_phys = new G4PVPlacement(moduleRotation(30),
                                         G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC30_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC31_phys = new G4PVPlacement(moduleRotation(31),
                                         G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC31_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC32_phys = new G4PVPlacement(moduleRotation(32),
                                         G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC32_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC33_phys = new G4PVPlacement(moduleRotation(33),
                                         G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC33_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC34_phys = new G4PVPlacement(moduleRotation(34),
                                         G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC34_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC35_phys = new G4PVPlacement(moduleRotation(35),
                                         G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC35_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC36_phys = new G4PVPlacement(moduleRotation(36),
                                         G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC36_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC37_phys = new G4PVPlacement(moduleRotation(37),
                                         G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC37_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC38_phys = new G4PVPlacement(moduleRotation(38),
                                         G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC38_phys",
                                         experimentalHall_log,
                                         false,
                                         0);
    platePcbC39_phys = new G4PVPlacement(moduleRotation(39),
                                         G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),pcbC_loc_z),
                                         platePcbC_log,
                                         "platePcbC39_phys",
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
                                           G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA00_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    
    backshieldA01_phys = new G4PVPlacement(moduleRotation(1),
                                           G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA01_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA02_phys = new G4PVPlacement(moduleRotation(2),
                                           G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA02_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA03_phys = new G4PVPlacement(moduleRotation(3),
                                           G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA03_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA04_phys = new G4PVPlacement(moduleRotation(4),
                                           G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA04_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA05_phys = new G4PVPlacement(moduleRotation(5),
                                           G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA05_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA06_phys = new G4PVPlacement(moduleRotation(6),
                                           G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA06_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA07_phys = new G4PVPlacement(moduleRotation(7),
                                           G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA07_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA08_phys = new G4PVPlacement(moduleRotation(8),
                                           G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA08_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA09_phys = new G4PVPlacement(moduleRotation(9),
                                           G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA09_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA10_phys = new G4PVPlacement(moduleRotation(10),
                                           G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA10_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA11_phys = new G4PVPlacement(moduleRotation(11),
                                           G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA11_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA12_phys = new G4PVPlacement(moduleRotation(12),
                                           G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA12_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA13_phys = new G4PVPlacement(moduleRotation(13),
                                           G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA13_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA14_phys = new G4PVPlacement(moduleRotation(14),
                                           G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA14_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA15_phys = new G4PVPlacement(moduleRotation(15),
                                           G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA15_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA16_phys = new G4PVPlacement(moduleRotation(16),
                                           G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA16_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA17_phys = new G4PVPlacement(moduleRotation(17),
                                           G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA17_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA18_phys = new G4PVPlacement(moduleRotation(18),
                                           G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA18_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA19_phys = new G4PVPlacement(moduleRotation(19),
                                           G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA19_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA20_phys = new G4PVPlacement(moduleRotation(20),
                                           G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA20_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA21_phys = new G4PVPlacement(moduleRotation(21),
                                           G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA21_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA22_phys = new G4PVPlacement(moduleRotation(22),
                                           G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA22_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA23_phys = new G4PVPlacement(moduleRotation(23),
                                           G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA23_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA24_phys = new G4PVPlacement(moduleRotation(24),
                                           G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA24_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA25_phys = new G4PVPlacement(moduleRotation(25),
                                           G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA25_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA26_phys = new G4PVPlacement(moduleRotation(26),
                                           G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA26_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA27_phys = new G4PVPlacement(moduleRotation(27),
                                           G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA27_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA28_phys = new G4PVPlacement(moduleRotation(28),
                                           G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA28_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA29_phys = new G4PVPlacement(moduleRotation(29),
                                           G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA29_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA30_phys = new G4PVPlacement(moduleRotation(30),
                                           G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA30_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA31_phys = new G4PVPlacement(moduleRotation(31),
                                           G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA31_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA32_phys = new G4PVPlacement(moduleRotation(32),
                                           G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA32_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA33_phys = new G4PVPlacement(moduleRotation(33),
                                           G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA33_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA34_phys = new G4PVPlacement(moduleRotation(34),
                                           G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA34_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA35_phys = new G4PVPlacement(moduleRotation(35),
                                           G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA35_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA36_phys = new G4PVPlacement(moduleRotation(36),
                                           G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA36_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA37_phys = new G4PVPlacement(moduleRotation(37),
                                           G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA37_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA38_phys = new G4PVPlacement(moduleRotation(38),
                                           G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA38_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldA39_phys = new G4PVPlacement(moduleRotation(39),
                                           G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),backshieldA_loc_z),
                                           backshieldA_log,
                                           "backshieldA39_phys",
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
                                           G4ThreeVector(moduleLocation(0,innerRingRadius, outerRingRadius).x(), moduleLocation(0,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB00_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    
    backshieldB01_phys = new G4PVPlacement(moduleRotation(1),
                                           G4ThreeVector(moduleLocation(1,innerRingRadius, outerRingRadius).x(), moduleLocation(1,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB01_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB02_phys = new G4PVPlacement(moduleRotation(2),
                                           G4ThreeVector(moduleLocation(2,innerRingRadius, outerRingRadius).x(), moduleLocation(2,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB02_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB03_phys = new G4PVPlacement(moduleRotation(3),
                                           G4ThreeVector(moduleLocation(3,innerRingRadius, outerRingRadius).x(), moduleLocation(3,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB03_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB04_phys = new G4PVPlacement(moduleRotation(4),
                                           G4ThreeVector(moduleLocation(4,innerRingRadius, outerRingRadius).x(), moduleLocation(4,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB04_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB05_phys = new G4PVPlacement(moduleRotation(5),
                                           G4ThreeVector(moduleLocation(5,innerRingRadius, outerRingRadius).x(), moduleLocation(5,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB05_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB06_phys = new G4PVPlacement(moduleRotation(6),
                                           G4ThreeVector(moduleLocation(6,innerRingRadius, outerRingRadius).x(), moduleLocation(6,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB06_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB07_phys = new G4PVPlacement(moduleRotation(7),
                                           G4ThreeVector(moduleLocation(7,innerRingRadius, outerRingRadius).x(), moduleLocation(7,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB07_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB08_phys = new G4PVPlacement(moduleRotation(8),
                                           G4ThreeVector(moduleLocation(8,innerRingRadius, outerRingRadius).x(), moduleLocation(8,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB08_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB09_phys = new G4PVPlacement(moduleRotation(9),
                                           G4ThreeVector(moduleLocation(9,innerRingRadius, outerRingRadius).x(), moduleLocation(9,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB09_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB10_phys = new G4PVPlacement(moduleRotation(10),
                                           G4ThreeVector(moduleLocation(10,innerRingRadius, outerRingRadius).x(), moduleLocation(10,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB10_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB11_phys = new G4PVPlacement(moduleRotation(11),
                                           G4ThreeVector(moduleLocation(11,innerRingRadius, outerRingRadius).x(), moduleLocation(11,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB11_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB12_phys = new G4PVPlacement(moduleRotation(12),
                                           G4ThreeVector(moduleLocation(12,innerRingRadius, outerRingRadius).x(), moduleLocation(12,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB12_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB13_phys = new G4PVPlacement(moduleRotation(13),
                                           G4ThreeVector(moduleLocation(13,innerRingRadius, outerRingRadius).x(), moduleLocation(13,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB13_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB14_phys = new G4PVPlacement(moduleRotation(14),
                                           G4ThreeVector(moduleLocation(14,innerRingRadius, outerRingRadius).x(), moduleLocation(14,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB14_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB15_phys = new G4PVPlacement(moduleRotation(15),
                                           G4ThreeVector(moduleLocation(15,innerRingRadius, outerRingRadius).x(), moduleLocation(15,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB15_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB16_phys = new G4PVPlacement(moduleRotation(16),
                                           G4ThreeVector(moduleLocation(16,innerRingRadius, outerRingRadius).x(), moduleLocation(16,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB16_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB17_phys = new G4PVPlacement(moduleRotation(17),
                                           G4ThreeVector(moduleLocation(17,innerRingRadius, outerRingRadius).x(), moduleLocation(17,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB17_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB18_phys = new G4PVPlacement(moduleRotation(18),
                                           G4ThreeVector(moduleLocation(18,innerRingRadius, outerRingRadius).x(), moduleLocation(18,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB18_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB19_phys = new G4PVPlacement(moduleRotation(19),
                                           G4ThreeVector(moduleLocation(19,innerRingRadius, outerRingRadius).x(), moduleLocation(19,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB19_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB20_phys = new G4PVPlacement(moduleRotation(20),
                                           G4ThreeVector(moduleLocation(20,innerRingRadius, outerRingRadius).x(), moduleLocation(20,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB20_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB21_phys = new G4PVPlacement(moduleRotation(21),
                                           G4ThreeVector(moduleLocation(21,innerRingRadius, outerRingRadius).x(), moduleLocation(21,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB21_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB22_phys = new G4PVPlacement(moduleRotation(22),
                                           G4ThreeVector(moduleLocation(22,innerRingRadius, outerRingRadius).x(), moduleLocation(22,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB22_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB23_phys = new G4PVPlacement(moduleRotation(23),
                                           G4ThreeVector(moduleLocation(23,innerRingRadius, outerRingRadius).x(), moduleLocation(23,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB23_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB24_phys = new G4PVPlacement(moduleRotation(24),
                                           G4ThreeVector(moduleLocation(24,innerRingRadius, outerRingRadius).x(), moduleLocation(24,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB24_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB25_phys = new G4PVPlacement(moduleRotation(25),
                                           G4ThreeVector(moduleLocation(25,innerRingRadius, outerRingRadius).x(), moduleLocation(25,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB25_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB26_phys = new G4PVPlacement(moduleRotation(26),
                                           G4ThreeVector(moduleLocation(26,innerRingRadius, outerRingRadius).x(), moduleLocation(26,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB26_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB27_phys = new G4PVPlacement(moduleRotation(27),
                                           G4ThreeVector(moduleLocation(27,innerRingRadius, outerRingRadius).x(), moduleLocation(27,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB27_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB28_phys = new G4PVPlacement(moduleRotation(28),
                                           G4ThreeVector(moduleLocation(28,innerRingRadius, outerRingRadius).x(), moduleLocation(28,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB28_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB29_phys = new G4PVPlacement(moduleRotation(29),
                                           G4ThreeVector(moduleLocation(29,innerRingRadius, outerRingRadius).x(), moduleLocation(29,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB29_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB30_phys = new G4PVPlacement(moduleRotation(30),
                                           G4ThreeVector(moduleLocation(30,innerRingRadius, outerRingRadius).x(), moduleLocation(30,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB30_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB31_phys = new G4PVPlacement(moduleRotation(31),
                                           G4ThreeVector(moduleLocation(31,innerRingRadius, outerRingRadius).x(), moduleLocation(31,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB31_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB32_phys = new G4PVPlacement(moduleRotation(32),
                                           G4ThreeVector(moduleLocation(32,innerRingRadius, outerRingRadius).x(), moduleLocation(32,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB32_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB33_phys = new G4PVPlacement(moduleRotation(33),
                                           G4ThreeVector(moduleLocation(33,innerRingRadius, outerRingRadius).x(), moduleLocation(33,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB33_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB34_phys = new G4PVPlacement(moduleRotation(34),
                                           G4ThreeVector(moduleLocation(34,innerRingRadius, outerRingRadius).x(), moduleLocation(34,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB34_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB35_phys = new G4PVPlacement(moduleRotation(35),
                                           G4ThreeVector(moduleLocation(35,innerRingRadius, outerRingRadius).x(), moduleLocation(35,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB35_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB36_phys = new G4PVPlacement(moduleRotation(36),
                                           G4ThreeVector(moduleLocation(36,innerRingRadius, outerRingRadius).x(), moduleLocation(36,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB36_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB37_phys = new G4PVPlacement(moduleRotation(37),
                                           G4ThreeVector(moduleLocation(37,innerRingRadius, outerRingRadius).x(), moduleLocation(37,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB37_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB38_phys = new G4PVPlacement(moduleRotation(38),
                                           G4ThreeVector(moduleLocation(38,innerRingRadius, outerRingRadius).x(), moduleLocation(38,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB38_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
    backshieldB39_phys = new G4PVPlacement(moduleRotation(39),
                                           G4ThreeVector(moduleLocation(39,innerRingRadius, outerRingRadius).x(), moduleLocation(39,innerRingRadius, outerRingRadius).y(),backshieldB_loc_z),
                                           backshieldB_log,
                                           "backshieldB39_phys",
                                           experimentalHall_log,
                                           false,
                                           0);


    
    
    
    
    // 14. SATELLITE BUS

	if (flag_satellitebus == true) {
		// a. Optical bench
		// Solid
	    const G4double Z[2]= {0*cm, -opticalbench_thick};
	    const G4double rInner[2]= {0*cm, 0*cm};
	    const G4double rOuter[2]= {opticalbench_side*sqrt(3)/2., opticalbench_side*sqrt(3)/2.};
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
		G4double opticalbenchPos_x = 0*cm;
		G4double opticalbenchPos_y = 0*cm;
		G4double opticalbenchPos_z = - bus_offset_z - mountingplate_thick;
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
		G4double towerPos_x = 0*cm;
		G4double towerPos_y = 0*cm;
		G4double towerPos_z = - bus_offset_z - mountingplate_thick - opticalbench_thick - tower_height/2. ;
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
		G4double servicemodulePos_x = 0*cm;
		G4double servicemodulePos_y = 0*cm;
		G4double servicemodulePos_z = - bus_offset_z - mountingplate_thick - opticalbench_thick - tower_height ;
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
        G4double solarpanelPos_x =  tower_diameter/2 + solarpanelGap + solarpanel_side_x/2.;
        G4double solarpanelPos_y = 0.*cm;
        G4double solarpanelPos_z = - bus_offset_z - mountingplate_thick - opticalbench_thick - tower_height/2.;
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
        solarpanelPos_x = -tower_diameter/2 - solarpanelGap - solarpanel_side_x/2.;
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
        G4double opticalbenchcoverPos_x = 0*cm;
        G4double opticalbenchcoverPos_y = mountingplate_diameter/2. + opticalbenchcover_thick;
        G4double opticalbenchcoverPos_z = (mountingplate_diameter-tower_diameter)/2 + opticalbenchcover_diameter/2. ;
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
        G4double sunshadePos_x = 0*cm;
        G4double sunshadePos_y = mountingplate_diameter/2. + opticalbenchcover_thick + sunshade_thick;
        G4double sunshadePos_z = sunshade_side_y/2. + mountingplate_thick;
        G4RotationMatrix* sunshadeRot = new G4RotationMatrix;
        sunshadeRot->rotateX(90*deg);
        sunshade_phys = new G4PVPlacement(sunshadeRot,
                                                   G4ThreeVector(sunshadePos_x, sunshadePos_y, sunshadePos_z),
                                                   sunshade_log,
                                                   "sunshade_phys",
                                                   experimentalHall_log,
                                                   false,
                                                   0);

        // g. Mounting plate
        // Solid
        G4VSolid* mountingplate_Tubs = new G4Tubs("mountingplate_Tubs",
                                                      tower_diameter/2.,            // inner radius
                                                      mountingplate_diameter/2.,    // outer radius
                                                      mountingplate_thick/2.,       // height
                                                      0.0 * deg, 360.0 * deg);      // segment angles
        // Logical
        mountingplate_log = new G4LogicalVolume(mountingplate_Tubs,
                                                    mountingplateMaterial, "mountingplate_log", 0, 0, 0);
        // Physical
        G4double mountingplatePos_x = 0*cm;
        G4double mountingplatePos_y = 0*cm;
        G4double mountingplatePos_z = -bus_offset_z - mountingplate_thick/2. ;
//        G4RotationMatrix* mountingplateRot = new G4RotationMatrix;
//        mountingplateRot->rotateX(90*deg);
        mountingplate_phys = new G4PVPlacement(0,
                                                   G4ThreeVector(mountingplatePos_x, mountingplatePos_y, mountingplatePos_z),
                                                   mountingplate_log,
                                                   "mountingplate_phys",
                                                   experimentalHall_log,
                                                   false,
                                                   0);
        
        // h. Optics
        // Solid
        G4VSolid* optics_Tubs = new G4Tubs("optics_Tubs",
                                                  0.,                       // inner radius
                                                  optics_diameter/2.,       // outer radius
                                                  optics_thick/2.,          // height
                                                  0.0 * deg, 360.0 * deg);  // segment angles
        // Logical
        optics_log = new G4LogicalVolume(optics_Tubs,
                                                opticsMaterial, "optics_log", 0, 0, 0);
        // Physical
        G4double optics_OuterRing_Pos_x = tower_diameter/2.-optics_diameter/2. - 5*cm; // TODO: Hardcoded distance btw. optics and tube walls?
        G4double optics_InnerRing_Pos_x = optics_diameter/2. + 20*cm; // TODO: Hardcoded distance btw. optics and tube center?
        G4double opticsPos_z = -bus_offset_z - optics_thick/2. ;
        optics00_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(0.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(0.*36.*3.1415926/180.), opticsPos_z),
                                           optics_log,
                                           "optics00_phys",
                                           experimentalHall_log,
                                           false,
                                           0);
        optics01_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(1.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(1.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics01_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics02_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(2.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(2.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics02_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics03_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(3.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(3.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics03_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics04_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(4.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(4.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics04_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics05_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(5.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(5.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics05_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics06_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(6.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(6.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics06_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics07_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(7.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(7.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics07_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics08_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(8.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(8.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics08_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics09_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_OuterRing_Pos_x*cos(9.*36.*3.1415926/180.), optics_OuterRing_Pos_x*sin(9.*36.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics09_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics10_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_InnerRing_Pos_x*cos(30.*3.1415926/180.), optics_InnerRing_Pos_x*sin(30.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics10_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics11_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_InnerRing_Pos_x*cos(150.*3.1415926/180.), optics_InnerRing_Pos_x*sin(150.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics11_phys",
                                          experimentalHall_log,
                                          false,
                                          0);
        optics12_phys = new G4PVPlacement(0,
                                          G4ThreeVector(optics_InnerRing_Pos_x*cos(270.*3.1415926/180.), optics_InnerRing_Pos_x*sin(270.*3.1415926/180.), opticsPos_z),
                                          optics_log,
                                          "optics12_phys",
                                          experimentalHall_log,
                                          false,
                                          0);


        // i. WFM dummies
        // Solid
        G4VSolid* wfmdummy_Trd = new G4Trd("wfmdummy_Trd",
                                                  wfmdummy_detside/2.,       // dx1 at -dz
                                                  wfmdummy_maskside/2.,      // dx2 at +dz
                                                  wfmdummy_detside/2.,       // dy1 at -dz
                                                  wfmdummy_maskside/2.,      // dy2 at + dz
                                                  wfmdummy_height/2.);          // dz
        
        // Logical
        wfmdummy_log = new G4LogicalVolume(wfmdummy_Trd,
                                                wfmdummyMaterial, "wfmdummy_log", 0, 0, 0);
        // Physical
        G4double wfmdummyA_Pos_x = wfmdummy_maskside/2.;
        G4double wfmdummyA_Pos_y = -(mountingplate_diameter/2.-wfmdummy_maskside/2.);
        G4double wfmdummyA_Pos_z = -bus_offset_z + wfmdummy_height/2. ;
        wfmdummy00_phys = new G4PVPlacement(0,
                                               G4ThreeVector(wfmdummyA_Pos_x, wfmdummyA_Pos_y, wfmdummyA_Pos_z),
                                               wfmdummy_log,
                                               "wfmdummy00_phys",
                                               experimentalHall_log,
                                               false,
                                               0);
        wfmdummy01_phys = new G4PVPlacement(0,
                                            G4ThreeVector(-wfmdummyA_Pos_x, wfmdummyA_Pos_y, wfmdummyA_Pos_z),
                                            wfmdummy_log,
                                            "wfmdummy01_phys",
                                            experimentalHall_log,
                                            false,
                                            0);
        G4double wfmdummyB_Pos_x = -opticalbench_side;
        G4double wfmdummyB_Pos_y = -wfmdummy_maskside/2.;
        G4RotationMatrix* wfmdummyRot1 = new G4RotationMatrix;
        wfmdummyRot1->rotateY(60*deg);
        wfmdummy02_phys = new G4PVPlacement(wfmdummyRot1,
                                            G4ThreeVector(wfmdummyB_Pos_x, wfmdummyB_Pos_y, wfmdummyA_Pos_z),
                                            wfmdummy_log,
                                            "wfmdummy02_phys",
                                            experimentalHall_log,
                                            false,
                                            0);
        wfmdummy03_phys = new G4PVPlacement(wfmdummyRot1,
                                            G4ThreeVector(wfmdummyB_Pos_x, -wfmdummyB_Pos_y, wfmdummyA_Pos_z),
                                            wfmdummy_log,
                                            "wfmdummy03_phys",
                                            experimentalHall_log,
                                            false,
                                            0);
        G4double wfmdummyC_Pos_x = +opticalbench_side;
        G4double wfmdummyC_Pos_y = -wfmdummy_maskside/2.;
        G4RotationMatrix* wfmdummyRot2 = new G4RotationMatrix;
        wfmdummyRot2->rotateY(-60*deg);
        wfmdummy04_phys = new G4PVPlacement(wfmdummyRot2,
                                            G4ThreeVector(wfmdummyC_Pos_x, wfmdummyC_Pos_y, wfmdummyA_Pos_z),
                                            wfmdummy_log,
                                            "wfmdummy04_phys",
                                            experimentalHall_log,
                                            false,
                                            0);
        wfmdummy05_phys = new G4PVPlacement(wfmdummyRot2,
                                            G4ThreeVector(wfmdummyC_Pos_x, -wfmdummyC_Pos_y, wfmdummyA_Pos_z),
                                            wfmdummy_log,
                                            "wfmdummy05_phys",
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

    G4VisAttributes* ThermalBlanketVisAtt = new G4VisAttributes(white);
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
        
        G4VisAttributes* MountingplateVisAtt= new G4VisAttributes(yellow);
        mountingplate_log -> SetVisAttributes(MountingplateVisAtt);

        G4VisAttributes* OpticsVisAtt = new G4VisAttributes(green);
        optics_log -> SetVisAttributes(OpticsVisAtt);

        G4VisAttributes* WFMDummyVisAtt = new G4VisAttributes(blue);
        wfmdummy_log -> SetVisAttributes(WFMDummyVisAtt);

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

void DetectorConstruction::SetMountingplateMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) mountingplateMaterial = pttoMaterial;
}

void DetectorConstruction::SetOpticsMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) opticsMaterial = pttoMaterial;
}

void DetectorConstruction::SetWFMDummyMaterial(G4String materialChoice)
{
    G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
    if (pttoMaterial) wfmdummyMaterial = pttoMaterial;
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


