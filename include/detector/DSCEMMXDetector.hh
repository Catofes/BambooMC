//
// Created by herbertqiao on 7/5/16.
//

#ifndef BAMBOOMC_DSCEMMXDETECTOR_HH
#define BAMBOOMC_DSCEMMXDETECTOR_HH

#include "detector/BambooDetectorPart.hh"

class DSCEMMXDetector : public BambooDetectorPart
{
public:
    DSCEMMXDetector(const G4String &name);

    virtual G4bool construct();

private:
    bool TopShieldOpen;
};


#endif //BAMBOOMC_DSCEMMXDETECTOR_HH
