//
// Created by herbertqiao on 7/5/16.
//

#ifndef BAMBOOMC_DSLABORATORY_HH
#define BAMBOOMC_DSLABORATORY_HH

#include "detector/BambooDetectorPart.hh"

class DSLaboratory : public BambooDetectorPart
{
public:
    DSLaboratory(const G4String &name);

    virtual G4bool construct();

private:
    double _halfX;
    double _halfY;
    double _halfZ;
};


#endif //BAMBOOMC_DSLABORATORY_HH
