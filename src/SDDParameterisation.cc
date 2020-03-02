#include "SDDParameterisation.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"


SDDParameterisation::SDDParameterisation(G4double sdd_x,
                                         G4double sdd_y,
                                         G4double sdd_spacing_x,
                                         G4double sdd_spacing_y)
{
    
    fSDDX  =  sdd_x;
    fSDDY  =  sdd_y;
    fSDDSpacingX =  sdd_spacing_x;
    fSDDSpacingY =  sdd_spacing_y;

}


SDDParameterisation::~SDDParameterisation() 
{;}


void SDDParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    G4int sddPerRow = 4;

    // Row and column corresponding to this SDD (# pixel)
    G4int sdd_row    = copyNo / sddPerRow;  // integer division!
    G4int sdd_column = copyNo % sddPerRow;  // modulo!
    
    // Coordinates relative to the module center
    G4double xPixel = sdd_column*fSDDSpacingX - (sddPerRow-1)*fSDDSpacingX/2.;
    G4double yPixel = sdd_row*fSDDSpacingY    - (sddPerRow-1)*fSDDSpacingY/2.;
    
//    G4cout << copyNo <<" *** DEBUG: xPixel " << xPixel/cm << " yPixel " << yPixel/cm  << G4endl;

    physVol->SetTranslation(G4ThreeVector(xPixel, yPixel, 0.));
}



