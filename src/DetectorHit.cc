#include "DetectorHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4ThreeVector.hh"

G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator = 0;

// Default constructor
DetectorHit::DetectorHit() 
:	energyDeposit(0),
	XpixelID(0),
	YpixelID(0),
	globaltime(0)
{}		



// Alternate constructor
DetectorHit::DetectorHit(G4int xp, G4int yp)
:  	energyDeposit(0),
	XpixelID(xp),
	YpixelID(yp),
	globaltime(0)
{;}    



// Destructor
DetectorHit::~DetectorHit() {}		



const DetectorHit& DetectorHit::operator=(const DetectorHit& right) {
	// Assignment operator	
	energyDeposit = right.energyDeposit;
	XpixelID = right.XpixelID;
	YpixelID = right.YpixelID;
	globaltime = right.globaltime; 
	return *this;
}



int DetectorHit::operator==(const DetectorHit& right) const {
	// Comparison operator
	return (this == &right) ? 1 : 0;
}

