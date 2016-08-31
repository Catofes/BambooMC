//
// Created by herbertqiao on 8/18/16.
//

#ifndef BAMBOOMC_CSSAMPLEAMBESOURCE_H
#define BAMBOOMC_CSSAMPLEAMBESOURCE_H

#include "detector/BambooDetectorPart.hh"

class CSSampleAmBeSource : public BambooDetectorPart
{
public:
    CSSampleAmBeSource(const G4String &name);

    virtual G4bool construct();

private:
    double _shiftX;
    double _shiftY;
    double _shiftZ;
};


#endif //BAMBOOMC_CSSAMPLEAMBESOURCE_H
