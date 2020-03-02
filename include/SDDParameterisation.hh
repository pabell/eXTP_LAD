#ifndef SDDParameterisation_H
#define SDDParameterisation_H 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Box;

// Dummy declarations to get rid of warnings...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Box;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;
class G4BREPSolidPolyhedra;

class SDDParameterisation : public G4VPVParameterisation
{ 
    public:
        SDDParameterisation(G4double sdd_x,
                            G4double sdd_y,
                            G4double sdd_spacing_x,
                            G4double sdd_spacing_y);

        virtual	~SDDParameterisation();

        void ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const;


    private:  // Dummy declarations to get rid of warnings...
        void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
        //    void ComputeDimensions (G4BREPSolidPolyhedra&,const G4int,const G4VPhysicalVolume*) const {}

    private:
        G4double fSDDX;
        G4double fSDDY;
        G4double fSDDSpacingX;
        G4double fSDDSpacingY;

};


#endif


