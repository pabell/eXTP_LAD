#include "ModuleParameterisation.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"


ModuleParameterisation::ModuleParameterisation(G4double moduleSpacing_x, G4double moduleSpacing_y,
                                               G4int moduleArray_x, G4int moduleArray_y)
{
    fModuleSpacingX    =  moduleSpacing_x;
    fModuleSpacingY    =  moduleSpacing_y;
    fModuleArrayX  =  moduleArray_x;
    fModuleArrayY  =  moduleArray_y;
}


ModuleParameterisation::~ModuleParameterisation() 
{;}


void ModuleParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{ 
    G4double xCell;
    G4double yCell;

    // Row and column corresponding to this copy (number copyNo)
    G4int row    = copyNo / fModuleArrayX;  // integer division!
    G4int column = copyNo % fModuleArrayX;  // modulo!

    //G4cout << "copyNo " << copyNo << " row " << row << " column " << column << G4endl;


    xCell = column*fModuleSpacingX - (fModuleArrayX-1)*fModuleSpacingX/2.;
    yCell = row*fModuleSpacingY    - (fModuleArrayY-1)*fModuleSpacingY/2.;

    physVol->SetTranslation( G4ThreeVector(xCell, yCell, 0.) );
}



