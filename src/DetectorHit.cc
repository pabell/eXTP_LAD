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
	x_ID(0),
    y_ID(0),
    SDD_ID(0),
    module_ID(0),
	globaltime(0)
{}		



// Alternate constructor
DetectorHit::DetectorHit(G4int xp, G4int yp)
:  	energyDeposit(0),
    x_ID(xp),
    y_ID(yp),
    SDD_ID(0),
    module_ID(0),
    globaltime(0)
{;}



// Destructor
DetectorHit::~DetectorHit() {}		



const DetectorHit& DetectorHit::operator=(const DetectorHit& right) {
	// Assignment operator	
	energyDeposit = right.energyDeposit;
	x_ID = right.x_ID;
	y_ID = right.y_ID;
    SDD_ID = right.SDD_ID;
    module_ID = right.module_ID;
	globaltime = right.globaltime; 
	return *this;
}



int DetectorHit::operator==(const DetectorHit& right) const {
	// Comparison operator
	return (this == &right) ? 1 : 0;
}

