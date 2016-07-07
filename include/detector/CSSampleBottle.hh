//
// Created by herbertqiao on 7/7/16.
//

#ifndef BAMBOOMC_CSSAMPLEBOTTLE_HH
#define BAMBOOMC_CSSAMPLEBOTTLE_HH


class CSSampleBottle : public BambooDetectorPart
{
public:
    CSSampleBottle(const G4String &name);

    virtual G4bool construct();

private:
    G4String _detectorType;
    double _shiftX;
    double _shiftY;
    double _shiftZ;
};

#endif //BAMBOOMC_CSSAMPLEBOTTLE_HH
