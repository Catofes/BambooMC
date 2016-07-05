//
// Created by herbertqiao on 7/5/16.
//

#ifndef BAMBOOMC_DSSAMPLEBOX_HH
#define BAMBOOMC_DSSAMPLEBOX_HH

#include "detector/BambooDetectorPart.hh"

class DSSampleBox : public BambooDetectorPart
{
public:
    DSSampleBox(const G4String &name);

    virtual G4bool construct();

private:
    G4String _material;
    double _halfX;
    double _halfY;
    double _halfZ;
    G4String _detectorType;
    double _shiftX;
    double _shiftY;
    double _shiftZ;
    double _ChamberHeight;
    double _PEHatTopSurfaceToChamberTopSurface;
};

#endif //BAMBOOMC_DSSAMPLEBOX_HH
