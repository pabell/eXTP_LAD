#include "SDDParameterisation.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"


SDDParameterisation::SDDParameterisation(G4double moduleSpacing_x, G4double moduleSpacing_y,
                                         G4int moduleArray_x, G4int moduleArray_y,
                                         G4double pixelSpacing_x, G4double pixelSpacing_y,
                                         G4int pixelArray_x, G4int pixelArray_y)
{
    fModuleSpacingX     = moduleSpacing_x;
    fModuleSpacingY     = moduleSpacing_y;
    fModuleArrayX       = moduleArray_x;
    fModuleArrayY       = moduleArray_y;
    fPixelSpacingX      = pixelSpacing_x;
    fPixelSpacingY      = pixelSpacing_y;
    fPixelArrayX        = pixelArray_x;
    fPixelArrayY        = pixelArray_y;
}


SDDParameterisation::~SDDParameterisation() 
{;}


void SDDParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{ 
//    G4int NbOfModules = fModuleArrayX*fModuleArrayY;
    G4int NbOfPixelsPerSDD = fPixelArrayX*fPixelArrayY;
//    G4int NbOfTotalPixels = NbOfPixelsPerSDD * NbOfModules;
    
    // SDD corresponding to this copyNo
    G4int module = copyNo / NbOfPixelsPerSDD;
    // Pixel number inside the module
    G4int pixel  = copyNo % NbOfPixelsPerSDD;
    
    // Row and column corresponding to this module copy (# module)
    G4int module_row    = module / fModuleArrayX;
    G4int module_column = module % fModuleArrayX;
    
    // Coordinates of the module center
    G4double xSDD = module_column*fModuleSpacingX - (fModuleArrayX-1)*fModuleSpacingX/2.;
    G4double ySDD = module_row*fModuleSpacingY    - (fModuleArrayY-1)*fModuleSpacingY/2.;
    
    // Row and column corresponding to this pixel (# pixel)
    G4int pixel_row    = pixel / fPixelArrayX;  // integer division!
    G4int pixel_column = pixel % fPixelArrayX;  // modulo!
    
    // Coordinates relative to the module center
    G4double xCell = pixel_column*fPixelSpacingX - (fPixelArrayX-1)*fPixelSpacingX/2.;
    G4double yCell = pixel_row*fPixelSpacingY    - (fPixelArrayY-1)*fPixelSpacingY/2.;
    
    // Absolute coordinates of the pixel
    G4double xPixel = xSDD + xCell;
    G4double yPixel = ySDD + yCell;
    
    physVol->SetTranslation(G4ThreeVector(xPixel, yPixel, 0.));
}



