#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class SensitiveDetector;
class G4VPVParameterisation;

#include "G4VUserDetectorConstruction.hh"

// Mandatory user class that defines the detector used in the
// simulation, its geometry and its materials.
// Derived from the G4VUserDetectorConstruction initialisation 
// abstract base class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();		// Constructor
		~DetectorConstruction();	// Destructor

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
	    const G4VPhysicalVolume* GetWorld()     {return experimentalHall_phys;};

	    // Method to get the world dimensions
		G4double GetWorldSide()               	{return worldSide;};

		// Method to get the SDD physical volume
	    const G4VPhysicalVolume* GetSDD()  		{return sdd_phys;};

	    // Methods to get the SDD dimensions
		G4double GetSDDSideX()          		{return sdd_x;};
		G4double GetSDDSideY()          		{return sdd_y;};
		G4double GetSDDThick()          		{return sdd_thick;};

		// Methods to get the module array dimensions
		G4double GetModuleArrayX()          	{return moduleArray_x;};
		G4double GetModuleArrayY()          	{return moduleArray_y;};
		
		// Methods to get the collimator dimensions
		G4double GetCollThick()          		{return coll_thick;};

	    // Methods to get the thermal blanket dimensions
		G4double GetThermalblanket1Thick()      {return thermalblanket1_thick;};
		G4double GetThermalblanket2Thick()      {return thermalblanket2_thick;};

	    // Methods to get the coating dimensions
		G4double GetCoatingThick()       		{return coating_thick;};
		
		// Methods to get the dead layers dimensions
		G4double GetDeadlayer1Thick()       	{return deadlayer1_thick;};
		G4double GetDeadlayer2Thick()       	{return deadlayer2_thick;};
		G4double GetDeadlayer3Thick()       	{return deadlayer3_thick;};

		// Methods to get the PCB layers dimensions
		G4double GetPcbsThick()       		    {return pcbs_thick;};
		G4double GetPcb1Thick()       		    {return pcb1_thick;};
		G4double GetPcb2Thick()       		    {return pcb2_thick;};
		G4double GetPcb3Thick()       		    {return pcb3_thick;};

	    // Methods to get the backshield dimensions
		G4double GetBack1Thick()       		    {return back1_thick;};
		G4double GetBack2Thick()       		    {return back2_thick;};
		
	    // Methods to get the frame dimensions
		G4double GetFrameThick()       		    {return frame_thick;};
		
		// Methods to get the sideframe dimensions
		G4double GetSideframe1Width()       	{return sideframe1_width;};
		G4double GetSideframe2Width()       	{return sideframe2_width;};

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


		// Methods to get the flags
		G4double GetFlagSatellitebus() 				{return flag_satellitebus;};

		// Methods to get the materials
		G4Material* GetSDDMaterial()        	        {return sddMaterial;};
		G4Material* GetCollMaterial() 	                {return collMaterial;};
		G4Material* GetThermalblanket1Material()   	    {return thermalblanket1Material;};
		G4Material* GetThermalblanket2Material()   	    {return thermalblanket2Material;};
		G4Material* GetCoatingMaterial()   	    	    {return coatingMaterial;};
		G4Material* GetDeadlayer1Material()   	        {return deadlayer1Material;};
		G4Material* GetDeadlayer2Material()   	        {return deadlayer2Material;};
		G4Material* GetDeadlayer3Material()   	        {return deadlayer3Material;};
		G4Material* GetPcbsMaterial()                   {return pcbsMaterial;};
		G4Material* GetPcb1Material()                   {return pcb1Material;};
		G4Material* GetPcb2Material()                   {return pcb2Material;};
		G4Material* GetPcb3Material()                   {return pcb3Material;};
		G4Material* GetBack1Material()                  {return back1Material;};
		G4Material* GetBack2Material()                  {return back2Material;};
		G4Material* GetFrameMaterial()   	            {return frameMaterial;};
		G4Material* GetSideframe1Material()   	        {return sideframe1Material;};
		G4Material* GetSideframe2Material()   	        {return sideframe2Material;};
		G4Material* GetOpticalbenchMaterial()           {return opticalbenchMaterial;};
		G4Material* GetTowerMaterial()   			    {return towerMaterial;};
		G4Material* GetServicemoduleMaterial ()   	    {return servicemoduleMaterial;};
        G4Material* GetSolarPanelMaterial ()            {return solarpanelMaterial;};
        G4Material* GetOpticalBenchCoverMaterial ()    {return opticalbenchcoverMaterial;};
        G4Material* GetSunshadeMaterial ()              {return sunshadeMaterial;};

		// Set methods
		// Method to set the world dimensions
		void SetWorldSide(G4double wside)		{worldSide = wside;};

		// Methods to set the SDD dimensions
		void SetSDDSideX(G4double sddsidex)		{sdd_x = sddsidex;};
		void SetSDDSideY(G4double sddsidey)		{sdd_y = sddsidey;};
		void SetSDDThick(G4double sddthick)		{sdd_thick = sddthick;};

		// Methods to set the module array dimensions
		void SetModuleArrayX(G4int modulex)		{moduleArray_x = modulex;};
		void SetModuleArrayY(G4int moduley)		{moduleArray_y = moduley;};
		
	    // Methods to set the collimator dimensions
		void SetCollThick(G4double collthick) 	{coll_thick = collthick;};

	    // Methods to set the thermal blanket dimensions
		void SetThermalblanket1Thick(G4double thermalblanketthick1) {thermalblanket1_thick = thermalblanketthick1;};
		void SetThermalblanket2Thick(G4double thermalblanketthick2) {thermalblanket2_thick = thermalblanketthick2;};

	    // Methods to set the coating dimensions
		void SetCoatingThick(G4double coatingthick) {coating_thick = coatingthick;};

	    // Methods to set the dead layers dimensions
		void SetDeadlayer1Thick(G4double deadlayerthick1) {deadlayer1_thick = deadlayerthick1;};
		void SetDeadlayer2Thick(G4double deadlayerthick2) {deadlayer2_thick = deadlayerthick2;};
		void SetDeadlayer3Thick(G4double deadlayerthick3) {deadlayer3_thick = deadlayerthick3;};

	    // Methods to set the PCB layers dimensions
		void SetPcbsThick(G4double pcbthicks) {pcbs_thick = pcbthicks;};
		void SetPcb1Thick(G4double pcbthick1) {pcb1_thick = pcbthick1;};
		void SetPcb2Thick(G4double pcbthick2) {pcb2_thick = pcbthick2;};
		void SetPcb3Thick(G4double pcbthick3) {pcb3_thick = pcbthick3;};

	    // Methods to set the backshield dimensions
		void SetBack1Thick(G4double backthick1) {back1_thick = backthick1;};
		void SetBack2Thick(G4double backthick2) {back2_thick = backthick2;};

	    // Methods to set the frame dimensions
		void SetFrameThick(G4double framethick) {frame_thick = framethick;};

	    // Methods to set the sideframe dimensions
		void SetSideframe1Width(G4double sideframewidth) {sideframe1_width = sideframewidth;};
		void SetSideframe2Width(G4double sideframewidth) {sideframe2_width = sideframewidth;};

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

    
		void SetBusDistance(G4double busdistance)              {bus_distance = busdistance;};

		// Method to activate the bus
		void SetFlagSatellitebus(G4bool flag)					{flag_satellitebus = flag;};
		
		
        // Methods to set the number of pixels
        void SetPixelX(G4int p)                 {pixel_x = p;}
        void SetPixelY(G4int p)                 {pixel_y = p;}
    
        // Methods to set the materials
		void SetSDDMaterial                 (G4String);     
		void SetCollMaterial                (G4String);     
		void SetThermalblanket1Material     (G4String);     
		void SetThermalblanket2Material     (G4String);    
		void SetCoatingMaterial             (G4String);     
		void SetDeadlayer1Material          (G4String);     
		void SetDeadlayer2Material          (G4String);     
		void SetDeadlayer3Material          (G4String);  
		void SetPcbsMaterial				(G4String);   
		void SetPcb1Material				(G4String); 
		void SetPcb2Material				(G4String); 
		void SetPcb3Material				(G4String); 
		void SetBack1Material               (G4String);     
		void SetBack2Material               (G4String);     
		void SetFrameMaterial               (G4String);     
		void SetSideframe1Material          (G4String);   
		void SetSideframe2Material          (G4String);     
		void SetOpticalbenchMaterial 		(G4String);     
		void SetTowerMaterial               (G4String);     
		void SetServicemoduleMaterial       (G4String);     
        void SetSolarPanelMaterial          (G4String);
        void SetOpticalBenchCoverMaterial   (G4String);
        void SetSunshadeMaterial            (G4String);

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
		G4LogicalVolume* thermalblanket1_log;
		G4LogicalVolume* thermalblanket2_log;
		G4LogicalVolume* plateCoating_log;
		G4LogicalVolume* coating_log;
		G4LogicalVolume* plateDeadlayer1_log;
		G4LogicalVolume* deadlayer1_log;
		G4LogicalVolume* plateDeadlayer2_log;
		G4LogicalVolume* deadlayer2_log;
		G4LogicalVolume* plateDeadlayer3_log;
		G4LogicalVolume* deadlayer3_log;
		G4LogicalVolume* platePcbs_log;
		G4LogicalVolume* pcbs_log;
		G4LogicalVolume* platePcb1_log;
		G4LogicalVolume* pcb1_log;
		G4LogicalVolume* platePcb2_log;
		G4LogicalVolume* pcb2_log;
		G4LogicalVolume* platePcb3_log;
		G4LogicalVolume* pcb3_log;
		G4LogicalVolume* plateBack1_log;
		G4LogicalVolume* back1_log;
		G4LogicalVolume* plateBack2_log;
		G4LogicalVolume* back2_log;
		G4LogicalVolume* plateFrame_log;
		G4LogicalVolume* frame_log;
		G4LogicalVolume* sideframe1_log;
		G4LogicalVolume* sideframe2_log;
		G4LogicalVolume* opticalbench_log;
		G4LogicalVolume* tower_log;
		G4LogicalVolume* servicemodule_log;
        G4LogicalVolume* solarpanel_log;
        G4LogicalVolume* opticalbenchcover_log;
        G4LogicalVolume* sunshade_log;


		// Parameterisations
		G4VPVParameterisation* sddParam;
		G4VPVParameterisation* collParam;
		G4VPVParameterisation* deadlayer1Param;
		G4VPVParameterisation* deadlayer2Param;
		G4VPVParameterisation* deadlayer3Param;
		G4VPVParameterisation* coatingParam;
		G4VPVParameterisation* pcbsParam;
		G4VPVParameterisation* pcb1Param;
		G4VPVParameterisation* pcb2Param;
		G4VPVParameterisation* pcb3Param;
		G4VPVParameterisation* back1Param;
		G4VPVParameterisation* back2Param;
		G4VPVParameterisation* frameParam;


		// Physical volumes
		G4VPhysicalVolume* experimentalHall_phys;
		G4VPhysicalVolume* plateSdd_phys;
		G4VPhysicalVolume* sdd_phys;
		G4VPhysicalVolume* plateColl_phys;
		G4VPhysicalVolume* coll_phys;
		G4VPhysicalVolume* thermalblanket1_phys;
		G4VPhysicalVolume* thermalblanket2_phys;
		G4VPhysicalVolume* plateCoating_phys;
		G4VPhysicalVolume* coating_phys;
		G4VPhysicalVolume* plateDeadlayer1_phys;
		G4VPhysicalVolume* deadlayer1_phys;
		G4VPhysicalVolume* plateDeadlayer2_phys;
		G4VPhysicalVolume* deadlayer2_phys;
		G4VPhysicalVolume* plateDeadlayer3_phys;
		G4VPhysicalVolume* deadlayer3_phys;
		G4VPhysicalVolume* platePcbs_phys;
		G4VPhysicalVolume* pcbs_phys;	
		G4VPhysicalVolume* platePcb1_phys;
		G4VPhysicalVolume* pcb1_phys;	
		G4VPhysicalVolume* platePcb2_phys;
		G4VPhysicalVolume* pcb2_phys;	
		G4VPhysicalVolume* platePcb3_phys;
		G4VPhysicalVolume* pcb3_phys;	
		G4VPhysicalVolume* plateBack1_phys;
		G4VPhysicalVolume* back1_phys;
		G4VPhysicalVolume* plateBack2_phys;
		G4VPhysicalVolume* back2_phys;
		G4VPhysicalVolume* plateFrame_phys;
		G4VPhysicalVolume* frame_phys;
		G4VPhysicalVolume* sideframe1_phys;
		G4VPhysicalVolume* sideframe2_phys;
		G4VPhysicalVolume* opticalbench_phys;
		G4VPhysicalVolume* tower_phys;
		G4VPhysicalVolume* servicemodule_phys;
        G4VPhysicalVolume* solarpanel1_phys;
        G4VPhysicalVolume* solarpanel2_phys;
        G4VPhysicalVolume* opticalbenchcover_phys;
        G4VPhysicalVolume* sunshade_phys;

		// World dimensions
		G4double worldSide;

		// SDD dimensions 
		G4double sdd_x;
		G4double sdd_y;
		G4double sdd_thick;

		// Module array dimensions;
		G4int moduleArray_x;
		G4int moduleArray_y;
		
		// Collimator dimensions
		G4double coll_thick;

		// Thermal blanket dimensions
		G4double thermalblanket1_thick;
		G4double thermalblanket2_thick;

		// Coating dimensions
		G4double coating_thick;

		// Dead layers dimensions
		G4double deadlayer1_thick;
		G4double deadlayer2_thick;
		G4double deadlayer3_thick;

		// PCB dimensions
		G4double pcbs_thick;
		G4double pcb1_thick;
		G4double pcb2_thick;
		G4double pcb3_thick;
		
		// Backshield dimensions
		G4double back1_thick;
		G4double back2_thick;

		// Frame dimensions
		G4double frame_thick;

		// Sideframe dimensions
		G4double sideframe1_width;
		G4double sideframe2_width;

    
    
    
		// Bus dimensions
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

		// Materials
		G4Material* defaultMaterial;
		G4Material*	sddMaterial;
		G4Material* collMaterial;
		G4Material* thermalblanket1Material;
		G4Material* thermalblanket2Material;
		G4Material* coatingMaterial;
		G4Material* deadlayer1Material;
		G4Material* deadlayer2Material;
		G4Material* deadlayer3Material;
		G4Material* pcbsMaterial;
		G4Material* pcb1Material;
		G4Material* pcb2Material;
		G4Material* pcb3Material;
		G4Material* back1Material;
		G4Material* back2Material;
		G4Material* frameMaterial;
		G4Material* sideframe1Material;
		G4Material* sideframe2Material;
		G4Material* opticalbenchMaterial;
		G4Material* towerMaterial;
		G4Material* servicemoduleMaterial;
        G4Material* solarpanelMaterial;
        G4Material* opticalbenchcoverMaterial;
        G4Material* sunshadeMaterial;

		// Flags
		G4bool flag_satellitebus;
    
        // Pixelisation
        G4int pixel_x;
        G4int pixel_y;
		
};

#endif

