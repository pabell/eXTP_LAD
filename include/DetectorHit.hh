#ifndef DETECTORHIT_HH
#define DETECTORHIT_HH

#include <vector>
#include <utility>
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "tls.hh"

// General purpose:
//  Represents a hit and contains relevant information about the hit.
//  (The user implementation should provide functionalities which allow to 
//  assign and retrieve hit information).
//  Hit objects can be created in the sensitive detector, and may be used
//  at the end of events to accumulate hit information.
//
// Purpose of the class in this implementation:
//  Represents a hit in the detector, where the relevant hit information is 
//  the energy deposited by the particle and its location


// G4VHit is the abstract base class for creating hit objects.

class DetectorHit : public G4VHit {
	public:
		DetectorHit();							                  // Default constructor
		DetectorHit(G4int xp, G4int yp); // Alternate constructor
		virtual ~DetectorHit();					// Destructor

		
		// Assignment and comparison operators:  
		const DetectorHit& operator= (const DetectorHit& right);
		int operator==(const DetectorHit& right) const;

		
		// The hit class has user-defined new and delete operators to speed up
		// the generation and deletion of hits objects:
		inline void* operator new(size_t);
		inline void  operator delete(void* hit);

		
		// The G4VHit provides two methods, which can be overloaded by the user to
		// visualize hits or to print information about hits. 
		// Here, these methods are not used (dummy implementation):
		virtual void Draw() { }
		virtual void Print() { }

		
		// The current hit object can be used to keep track of:
		// a. The  energy deposit
		// b. The ID of the azimutal sector of deposit 
		
		// The following methods allow to set, accumulate and get the energy deposit:
		inline void SetEnergyDeposit(G4double energy) {energyDeposit = energy;}
		inline void AddEnergyDeposit(G4double energy) {energyDeposit += energy;}
		inline G4double GetEnergyDeposit() 			  {return energyDeposit;}
		
		// The following methods allow to set and get the ID of the X sector:
		inline void SetSDDXID(G4int id) 			  {XpixelID = id;}
		inline G4int GetSDDXID() 					  {return XpixelID;}
		// The following methods allow to set and get the ID of the Y sector:
		inline void SetSDDYID(G4int id) 			  {YpixelID = id;}
		inline G4int GetSDDYID() 					  {return YpixelID;}
	
		// The following methods allow to set and get the time:
		inline void SetTime(G4double t) 		      {globaltime = t;}
		inline G4int GetTime() 					      {return globaltime;}

	private:
//		const G4LogicalVolume* pLogV;
		// The total energy deposit
		G4double energyDeposit;
		// The pixel ID in the X direction
		G4int XpixelID;
		// The pixel ID in the Y direction
		G4int YpixelID;
		// The time of the last track step
		G4double globaltime;
	
};

typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;
extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;


inline void* DetectorHit::operator new(size_t) {
    // Implementation of the new operator
    if(!DetectorHitAllocator) DetectorHitAllocator = new G4Allocator<DetectorHit>;
    return (void*) DetectorHitAllocator->MallocSingle();
}


inline void DetectorHit::operator delete(void* hit) {
    // Implementation of the delete operator
    DetectorHitAllocator->FreeSingle((DetectorHit*) hit);
}

#endif // DETECTORHIT_HH
