#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class SensitiveDetector;
class G4VPVParameterisation;

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"


// Mandatory user class that defines the detector used in the
// simulation, its geometry and its materials.
// Derived from the G4VUserDetectorConstruction initialisation 
// abstract base class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();		// Constructor
		~DetectorConstruction();	// Destructor
    
        G4ThreeVector moduleLocation(G4int moduleID);
        G4RotationMatrix* moduleRotation(G4int moduleID);


	private:
		// Method to construct the detector
		G4VPhysicalVolume* Construct();
        // Method to construct the sensitive detector
        void ConstructSDandField();
		// Method to define the materials
		void DefineMaterials();
		// Method to read the values of parameters from file
		void DefineParameters();
    

	public:
		// Get methods
		// Method to get the world physical volume
	    const G4VPhysicalVolume* GetWorld()         {return experimentalHall_phys;};

	    // Method to get the world dimensions
		G4double GetWorldSide()               	    {return worldSide;};

		// Method to get the SDD physical volume
	    const G4VPhysicalVolume* GetSDD()  		    {return sdd_phys;};

	    // Methods to get the SDD dimensions
		G4double GetSDDSideX()          		    {return sdd_x;};
		G4double GetSDDSideY()          		    {return sdd_y;};
		G4double GetSDDThick()          		    {return sdd_thick;};
    
		// Methods to get the collimator dimensions
		G4double GetCollThick()          		    {return coll_thick;};

	    // Methods to get the thermal blanket dimensions
		G4double GetThermalblanketAThick()          {return thermalblanketA_thick;};
		G4double GetThermalblanketBThick()          {return thermalblanketB_thick;};

		// Methods to get the dead layers dimensions
		G4double GetDeadlayerAThick()       	    {return deadlayerA_thick;};
		G4double GetDeadlayerBThick()       	    {return deadlayerB_thick;};
		G4double GetDeadlayerCThick()       	    {return deadlayerC_thick;};

		// Methods to get the PCB layers dimensions
		G4double GetPcbsThick()       		        {return pcbs_thick;};
		G4double GetPcbAThick()       		        {return pcbA_thick;};
		G4double GetPcbBThick()       		        {return pcbB_thick;};
		G4double GetPcbCThick()       		        {return pcbC_thick;};

	    // Methods to get the backshield dimensions
		G4double GetBackshieldAThick()       	    {return backshieldA_thick;};
		G4double GetBackshieldBThick()       	    {return backshieldB_thick;};
		
		// Methods to get the sideframe dimensions
		G4double GetModuleframeX()       	        {return moduleframe_side_x;};
		G4double GetModuleframeY()       	        {return moduleframe_side_y;};
        G4double GetInternalframeX()                {return internalframe_side_x;};
        G4double GetInternalframeY()                {return internalframe_side_y;};

		// Methods to get the bus dimensions
		G4double GetOpticalbenchSide()              {return opticalbench_side;};
		G4double GetOpticalbenchDiameter()          {return opticalbench_thick;};
		G4double GetTowerHeight()                   {return tower_height;};
		G4double GetTowerDiameter()                 {return tower_diameter;};
		G4double GetServicemoduleSide()             {return servicemodule_side;};
		G4double GetServicemoduleDiameter()         {return servicemodule_thick;};
		G4double GetBusDistance()                   {return bus_distance;};
        G4double GetSolarPanelSideX()               {return solarpanel_side_x;};
        G4double GetSolarPanelSideY()               {return solarpanel_side_y;};
        G4double GetSolarPanelThick()               {return solarpanel_thick;};
        G4double GetOpticalBenchCoverDiameter()     {return opticalbenchcover_diameter;};
        G4double GetOpticalBenchCoverThick()        {return opticalbenchcover_thick;};
        G4double GetSunshadeSideX()                 {return sunshade_side_x;};
        G4double GetSunshadeSideY()                 {return sunshade_side_y;};
        G4double GetSunshadeThick()                 {return sunshade_thick;};
        G4double GeMountingplateDiameter()          {return mountingplate_diameter;};
        G4double GeMountingplateThick()             {return mountingplate_thick;};
        G4double GetOpticsDiameter()                {return optics_diameter;};
        G4double GetOpticsThick()                   {return optics_thick;};

        G4double GeWFMDummyDetside()                {return wfmdummy_detside;};
        G4double GeWFMDummyMaskside()               {return wfmdummy_maskside;};
        G4double GeWFMDummyHeight()                 {return wfmdummy_height;};

		// Methods to get the flags
		G4double GetFlagSatellitebus() 				{return flag_satellitebus;};

		// Methods to get the materials
		G4Material* GetSDDMaterial()        	    {return sddMaterial;};
		G4Material* GetCollMaterial() 	            {return collMaterial;};
		G4Material* GetThermalblanketAMaterial()   	{return thermalblanketAMaterial;};
		G4Material* GetThermalblanketBMaterial()   	{return thermalblanketBMaterial;};
		G4Material* GetDeadlayerAMaterial()   	    {return deadlayerAMaterial;};
		G4Material* GetDeadlayerBMaterial()   	    {return deadlayerBMaterial;};
		G4Material* GetDeadlayerCMaterial()   	    {return deadlayerCMaterial;};
		G4Material* GetPcbsMaterial()               {return pcbsMaterial;};
		G4Material* GetPcbAMaterial()               {return pcbAMaterial;};
		G4Material* GetPcbBMaterial()               {return pcbBMaterial;};
		G4Material* GetPcbCMaterial()               {return pcbCMaterial;};
		G4Material* GetBackshieldAMaterial()        {return backshieldAMaterial;};
		G4Material* GetBackshieldBMaterial()        {return backshieldBMaterial;};
        G4Material* GetModuleframeMaterial()        {return moduleframeMaterial;};
        G4Material* GetOpticalbenchMaterial()       {return opticalbenchMaterial;};
		G4Material* GetTowerMaterial()   			{return towerMaterial;};
		G4Material* GetServicemoduleMaterial()   	{return servicemoduleMaterial;};
        G4Material* GetSolarPanelMaterial()         {return solarpanelMaterial;};
        G4Material* GetOpticalBenchCoverMaterial()  {return opticalbenchcoverMaterial;};
        G4Material* GetSunshadeMaterial()           {return sunshadeMaterial;};

        G4Material* GetMountingplateMaterial()      {return mountingplateMaterial;};
        G4Material* GetOpticsMaterial()             {return opticsMaterial;};
        G4Material* GetWFMDummyMaterial()           {return wfmdummyMaterial;};

		// Set methods
		// Method to set the world dimensions
		void SetWorldSide(G4double wside)		    {worldSide = wside;};
    
		// Methods to set the SDD dimensions
		void SetSDDSideX(G4double sddsidex)		    {sdd_x = sddsidex;};
		void SetSDDSideY(G4double sddsidey)		    {sdd_y = sddsidey;};
		void SetSDDThick(G4double sddthick)		    {sdd_thick = sddthick;};

		
	    // Methods to set the collimator dimensions
		void SetCollThick(G4double collthick) 	    {coll_thick = collthick;};

	    // Methods to set the thermal blanket dimensions
		void SetThermalblanketAThick(G4double ttA)  {thermalblanketA_thick = ttA;};
		void SetThermalblanketBThick(G4double ttB)  {thermalblanketB_thick = ttB;};

	    // Methods to set the dead layers dimensions
		void SetDeadlayerAThick(G4double dltA)      {deadlayerA_thick = dltA;};
		void SetDeadlayerBThick(G4double dltB)      {deadlayerB_thick = dltB;};
		void SetDeadlayerCThick(G4double dltC)      {deadlayerC_thick = dltC;};

	    // Methods to set the PCB layers dimensions
		void SetPcbsThick(G4double pcbthicks)       {pcbs_thick = pcbthicks;};
		void SetPcbAThick(G4double pcbthickA)       {pcbA_thick = pcbthickA;};
		void SetPcbBThick(G4double pcbthickB)       {pcbB_thick = pcbthickB;};
		void SetPcbCThick(G4double pcbthickC)       {pcbC_thick = pcbthickC;};

	    // Methods to set the backshield dimensions
		void SetBackshieldAThick(G4double b1)       {backshieldA_thick = b1;};
		void SetBackshieldBThick(G4double b2)       {backshieldB_thick = b2;};

	    // Methods to set the external module dimensions
		void SetModuleframeX(G4double sfx)          {moduleframe_side_x = sfx;};
		void SetModuleframeY(G4double sfy)          {moduleframe_side_y = sfy;};
        void SetInternalframeX(G4double sfx)        {internalframe_side_x = sfx;};
        void SetInternalframeY(G4double sfy)        {internalframe_side_y = sfy;};

	    // Methods to set the bus dimensions
        void SetOpticalbenchSide(G4double  opticalbenchside)        {opticalbench_side = opticalbenchside;};
        void SetOpticalbenchThick(G4double opticalbenchthick)       {opticalbench_thick = opticalbenchthick;};
        void SetTowerHeight(G4double towerheight)                   {tower_height = towerheight;};
        void SetTowerDiameter(G4double towerdiameter)               {tower_diameter = towerdiameter;};
        void SetServicemoduleSide(G4double  servicemoduleside)      {servicemodule_side = servicemoduleside;};
        void SetServicemoduleThick(G4double servicemodulethick)     {servicemodule_thick = servicemodulethick;};
        void SetSolarPanelSideX(G4double  spsidex)                  {solarpanel_side_x = spsidex;};
        void SetSolarPanelSideY(G4double  spsidey)                  {solarpanel_side_y = spsidey;};
        void SetSolarPanelThick(G4double  spthick)                  {solarpanel_thick = spthick;};
        void SetOpticalBenchCoverDiameter(G4double obcdiameter)     {opticalbenchcover_diameter = obcdiameter;};
        void SetOpticalBenchCoverThick(G4double obcthick)           {opticalbenchcover_thick = obcthick;};
        void SetSunshadeSideX(G4double  sunsidex)                   {sunshade_side_x = sunsidex;};
        void SetSunshadeSideY(G4double  sunsidey)                   {sunshade_side_y = sunsidey;};
        void SetSunshadeThick(G4double  sunthick)                   {sunshade_thick = sunthick;};
        void SetMountingplateDiameter(G4double  mpd)                {mountingplate_diameter = mpd;};
        void SetMountingplateThick(G4double  mpt)                   {mountingplate_thick = mpt;};
        void SetOpticsDiameter(G4double  od)                        {optics_diameter = od;};
        void SetOpticsThick(G4double  ot)                           {optics_thick = ot;};

        void SetWFMDummyDetside(G4double  wfmd)                     {wfmdummy_detside = wfmd;};
        void SetWFMDummyMaskside(G4double  wfmm)                    {wfmdummy_maskside = wfmm;};
        void SetWFMDummyHeight(G4double  wfmh)                      {wfmdummy_height = wfmh;};

		void SetBusDistance(G4double busdistance)                   {bus_distance = busdistance;};

		// Method to activate the bus
		void SetFlagSatellitebus(G4bool flag)					    {flag_satellitebus = flag;};
		
		
        // Methods to set the number of pixels
        void SetPixelX(G4int p)                 {pixel_x = p;}
        void SetPixelY(G4int p)                 {pixel_y = p;}
    
        // Methods to set the materials
		void SetSDDMaterial                 (G4String);     
		void SetCollMaterial                (G4String);     
		void SetThermalblanketAMaterial     (G4String);
		void SetThermalblanketBMaterial     (G4String);
		void SetDeadlayerAMaterial          (G4String);
		void SetDeadlayerBMaterial          (G4String);
		void SetDeadlayerCMaterial          (G4String);  
		void SetPcbsMaterial				(G4String);   
		void SetPcbAMaterial				(G4String);
		void SetPcbBMaterial				(G4String);
		void SetPcbCMaterial				(G4String);
		void SetBackshieldAMaterial         (G4String);
		void SetBackshieldBMaterial         (G4String);
        void SetModuleframeMaterial         (G4String);
		void SetOpticalbenchMaterial 		(G4String);     
		void SetTowerMaterial               (G4String);     
		void SetServicemoduleMaterial       (G4String);     
        void SetSolarPanelMaterial          (G4String);
        void SetOpticalBenchCoverMaterial   (G4String);
        void SetSunshadeMaterial            (G4String);

        void SetMountingplateMaterial       (G4String);
        void SetOpticsMaterial              (G4String);
        void SetWFMDummyMaterial            (G4String);

	    // Print a list of parameters
		void PrintParameters();
	
		// Geometry update
		void UpdateGeometry();


	private:
		// Logical volumes
		G4LogicalVolume* experimentalHall_log;
    
		G4LogicalVolume* plateSdd_log;
		G4LogicalVolume* sdd_log;
		G4LogicalVolume* plateColl_log;
		G4LogicalVolume* coll_log;
		G4LogicalVolume* thermalblanketA_log;
		G4LogicalVolume* thermalblanketB_log;
		G4LogicalVolume* plateDeadlayerA_log;
		G4LogicalVolume* deadlayerA_log;
        G4LogicalVolume* plateDeadlayerB_log;
		G4LogicalVolume* deadlayerB_log;
		G4LogicalVolume* plateDeadlayerC_log;
		G4LogicalVolume* deadlayerC_log;
		G4LogicalVolume* platePcbs_log;
		G4LogicalVolume* pcbs_log;
		G4LogicalVolume* platePcbA_log;
		G4LogicalVolume* pcbA_log;
		G4LogicalVolume* platePcbB_log;
		G4LogicalVolume* pcbB_log;
		G4LogicalVolume* platePcbC_log;
		G4LogicalVolume* pcbC_log;
		G4LogicalVolume* backshieldA_log;
		G4LogicalVolume* backshieldB_log;

		G4LogicalVolume* opticalbench_log;
		G4LogicalVolume* tower_log;
		G4LogicalVolume* servicemodule_log;
        G4LogicalVolume* solarpanel_log;
        G4LogicalVolume* opticalbenchcover_log;
        G4LogicalVolume* sunshade_log;

        G4LogicalVolume* mountingplate_log;
        G4LogicalVolume* optics_log;

        G4LogicalVolume* wfmdummy_log;


		// Parameterisations
		G4VPVParameterisation* sddParam;
		G4VPVParameterisation* collParam;
		G4VPVParameterisation* deadlayerAParam;
		G4VPVParameterisation* deadlayerBParam;
		G4VPVParameterisation* deadlayerCParam;
		G4VPVParameterisation* pcbsParam;
		G4VPVParameterisation* pcbAParam;
		G4VPVParameterisation* pcbBParam;
		G4VPVParameterisation* pcbCParam;

		// Physical volumes
		G4VPhysicalVolume* experimentalHall_phys;
    
        G4VPhysicalVolume* plateSdd00_phys;
        G4VPhysicalVolume* plateSdd01_phys;
        G4VPhysicalVolume* plateSdd02_phys;
        G4VPhysicalVolume* plateSdd03_phys;
        G4VPhysicalVolume* sdd_phys;

        G4VPhysicalVolume* plateColl00_phys;
        G4VPhysicalVolume* plateColl01_phys;
        G4VPhysicalVolume* plateColl02_phys;
        G4VPhysicalVolume* plateColl03_phys;
		G4VPhysicalVolume* coll_phys;
    
		G4VPhysicalVolume* thermalblanketA00_phys;
        G4VPhysicalVolume* thermalblanketA01_phys;
        G4VPhysicalVolume* thermalblanketA02_phys;
        G4VPhysicalVolume* thermalblanketA03_phys;

		G4VPhysicalVolume* thermalblanketB00_phys;
        G4VPhysicalVolume* thermalblanketB01_phys;
        G4VPhysicalVolume* thermalblanketB02_phys;
        G4VPhysicalVolume* thermalblanketB03_phys;

		G4VPhysicalVolume* plateDeadlayerA00_phys;
        G4VPhysicalVolume* plateDeadlayerA01_phys;
        G4VPhysicalVolume* plateDeadlayerA02_phys;
        G4VPhysicalVolume* plateDeadlayerA03_phys;
		G4VPhysicalVolume* deadlayerA_phys;
    
		G4VPhysicalVolume* plateDeadlayerB00_phys;
        G4VPhysicalVolume* plateDeadlayerB01_phys;
        G4VPhysicalVolume* plateDeadlayerB02_phys;
        G4VPhysicalVolume* plateDeadlayerB03_phys;
		G4VPhysicalVolume* deadlayerB_phys;
    
		G4VPhysicalVolume* plateDeadlayerC00_phys;
        G4VPhysicalVolume* plateDeadlayerC01_phys;
        G4VPhysicalVolume* plateDeadlayerC02_phys;
        G4VPhysicalVolume* plateDeadlayerC03_phys;
		G4VPhysicalVolume* deadlayerC_phys;
    
		G4VPhysicalVolume* platePcbs00_phys;
        G4VPhysicalVolume* platePcbs01_phys;
        G4VPhysicalVolume* platePcbs02_phys;
        G4VPhysicalVolume* platePcbs03_phys;
		G4VPhysicalVolume* pcbs_phys;
    
		G4VPhysicalVolume* platePcbA00_phys;
        G4VPhysicalVolume* platePcbA01_phys;
        G4VPhysicalVolume* platePcbA02_phys;
        G4VPhysicalVolume* platePcbA03_phys;
		G4VPhysicalVolume* pcbA_phys;
    
        G4VPhysicalVolume* platePcbB00_phys;
        G4VPhysicalVolume* platePcbB01_phys;
        G4VPhysicalVolume* platePcbB02_phys;
        G4VPhysicalVolume* platePcbB03_phys;
		G4VPhysicalVolume* pcbB_phys;
    
        G4VPhysicalVolume* platePcbC00_phys;
        G4VPhysicalVolume* platePcbC01_phys;
        G4VPhysicalVolume* platePcbC02_phys;
        G4VPhysicalVolume* platePcbC03_phys;
		G4VPhysicalVolume* pcbC_phys;
    
		G4VPhysicalVolume* backshieldA00_phys;
        G4VPhysicalVolume* backshieldA01_phys;
        G4VPhysicalVolume* backshieldA02_phys;
        G4VPhysicalVolume* backshieldA03_phys;

		G4VPhysicalVolume* backshieldB00_phys;
        G4VPhysicalVolume* backshieldB01_phys;
        G4VPhysicalVolume* backshieldB02_phys;
        G4VPhysicalVolume* backshieldB03_phys;

    
		G4VPhysicalVolume* opticalbench_phys;
		G4VPhysicalVolume* tower_phys;
		G4VPhysicalVolume* servicemodule_phys;
        G4VPhysicalVolume* solarpanelA_phys;
        G4VPhysicalVolume* solarpanelB_phys;
        G4VPhysicalVolume* opticalbenchcover_phys;
        G4VPhysicalVolume* sunshade_phys;

        G4VPhysicalVolume* mountingplate_phys;
        G4VPhysicalVolume* optics00_phys;
        G4VPhysicalVolume* optics01_phys;
        G4VPhysicalVolume* optics02_phys;
        G4VPhysicalVolume* optics03_phys;
        G4VPhysicalVolume* optics04_phys;
        G4VPhysicalVolume* optics05_phys;
        G4VPhysicalVolume* optics06_phys;
        G4VPhysicalVolume* optics07_phys;
        G4VPhysicalVolume* optics08_phys;
        G4VPhysicalVolume* optics09_phys;
        G4VPhysicalVolume* optics10_phys;
        G4VPhysicalVolume* optics11_phys;
        G4VPhysicalVolume* optics12_phys;

        G4VPhysicalVolume* wfmdummy00_phys;
        G4VPhysicalVolume* wfmdummy01_phys;
        G4VPhysicalVolume* wfmdummy02_phys;
        G4VPhysicalVolume* wfmdummy03_phys;
        G4VPhysicalVolume* wfmdummy04_phys;
        G4VPhysicalVolume* wfmdummy05_phys;

		// World dimensions
		G4double worldSide;

		// SDD dimensions 
		G4double sdd_x;
		G4double sdd_y;
		G4double sdd_thick;

        // Module external dimensions
        G4double moduleframe_side_x;
        G4double moduleframe_side_y;
        G4double internalframe_side_x;
        G4double internalframe_side_y;

		// Module array numbers (hardcoded in initialisation)
        G4int n_sdd_x;
        G4int n_sdd_y;
        G4int n_sdd_per_module;
        G4int n_modules;
    
		// Collimator dimensions
		G4double coll_thick;

		// Thermal blanket dimensions
		G4double thermalblanketA_thick;
		G4double thermalblanketB_thick;

		// Dead layers dimensions
		G4double deadlayerA_thick;
		G4double deadlayerB_thick;
		G4double deadlayerC_thick;

		// PCB dimensions
		G4double pcbs_thick;
		G4double pcbA_thick;
		G4double pcbB_thick;
		G4double pcbC_thick;
		
		// Backshield dimensions
		G4double backshieldA_thick;
		G4double backshieldB_thick;

    


		// Bus parameters
		G4double opticalbench_side;
		G4double opticalbench_thick;
		G4double tower_height;
		G4double tower_diameter;
		G4double servicemodule_side;
		G4double servicemodule_thick;
		G4double bus_distance;
        G4double solarpanel_side_x;
        G4double solarpanel_side_y;
        G4double solarpanel_thick;
        G4double opticalbenchcover_diameter;
        G4double opticalbenchcover_thick;
        G4double sunshade_side_x;
        G4double sunshade_side_y;
        G4double sunshade_thick;
        G4double mountingplate_diameter;
        G4double mountingplate_thick;
        G4double optics_diameter;
        G4double optics_thick;

        G4double wfmdummy_detside;
        G4double wfmdummy_maskside;
        G4double wfmdummy_height;
    
    
		// Materials
		G4Material* defaultMaterial;
		G4Material*	sddMaterial;
		G4Material* collMaterial;
		G4Material* thermalblanketAMaterial;
		G4Material* thermalblanketBMaterial;
		G4Material* deadlayerAMaterial;
		G4Material* deadlayerBMaterial;
		G4Material* deadlayerCMaterial;
		G4Material* pcbsMaterial;
		G4Material* pcbAMaterial;
		G4Material* pcbBMaterial;
		G4Material* pcbCMaterial;
		G4Material* backshieldAMaterial;
		G4Material* backshieldBMaterial;
		G4Material* moduleframeMaterial;
		G4Material* opticalbenchMaterial;
		G4Material* towerMaterial;
		G4Material* servicemoduleMaterial;
        G4Material* solarpanelMaterial;
        G4Material* opticalbenchcoverMaterial;
        G4Material* sunshadeMaterial;
        G4Material* mountingplateMaterial;
        G4Material* opticsMaterial;
        G4Material* wfmdummyMaterial;
    
		// Flags
		G4bool flag_satellitebus;
    
        // Pixelisation
        G4int pixel_x;
        G4int pixel_y;
		
};

#endif

