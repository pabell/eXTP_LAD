#include "ModuleParameterisation.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"


ModuleParameterisation::ModuleParameterisation()
{;}


ModuleParameterisation::~ModuleParameterisation() 
{;}





void ModuleParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{ 
    G4ThreeVector moduleLoc;
    G4RotationMatrix* moduleRot = new G4RotationMatrix;

    G4double xMod = 0*cm;
    G4double yMod = (copyNo - 2)*100*cm;
    G4double zMod = 0*cm;
    
    
    if(copyNo == 1)
    {
        moduleRot->rotateX(90*deg);
    }

    
    moduleLoc = G4ThreeVector(xMod, yMod, zMod);

    physVol->SetTranslation( moduleLoc );
    physVol->SetRotation( moduleRot );
}



