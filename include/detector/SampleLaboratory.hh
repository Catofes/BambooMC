//
// Created by herbertqiao on 7/5/16.
//

#ifndef BAMBOOMC_SAMPLELABORATORY_HH
#define BAMBOOMC_SAMPLELABORATORY_HH

#include "detector/BambooDetectorPart.hh"

class SampleLaboratory : public BambooDetectorPart
{
public:
    SampleLaboratory(const G4String &name);

    virtual G4bool construct();

private:
    double _halfX;
    double _halfY;
    double _halfZ;
};


#endif //BAMBOOMC_SampleLABORATORY_HH
