//
// Created by herbertqiao on 7/5/16.
//

#ifndef BAMBOOMC_CSBEDETECTOR_HH
#define BAMBOOMC_CSBEDETECTOR_HH


#include "detector/BambooDetectorPart.hh"

class CSBEDetector : public BambooDetectorPart
{
public:
    CSBEDetector(const G4String &name);

    virtual G4bool construct();

private:
    double HPGeRadius;
    double HPGeHeight;
    double HPGeEnteranceWindowThickness;
    double HPGeOuterElectrodeThickness;
    double HPGePPlusRadius;
    double HPGePPlusDepth;

//--- Chamber ---
    double ChamberHalfX;
    double ChamberHalfY;
    double ChamberHalfZ;

//--- distance from Cryostat to copper wall, minimum distance

    double DistanceCryostatCuWall;

//--- Cryostat inside chamber ---

    double CryostatInnerRadius;
    double CryostatThickness;
    double CryostatRadius;
    double CryostatInnerHeight;
    double CryostatHeight;
    double CryostatWindowThickness;
    double CryostatZOffset;


//--- Cryostat Subtracted for Cooling Finger ---

    double CryostatSubTubs1Radius;
    double CryostatSubTubs1Height;
    double CryostatSubTubs2Radius;
    double CryostatSubTubs2Height;
    double CryostatSubTorusOuterRadius;
    double CryostatSubTorusInnerRadius;
    double CryostatSubTorusRadius;

//--- Cooling Finger inside the cyostat ---

    double CryostatTubs1InnerRadius;
    double CryostatTubs1OuterRadius;
//   double CryostatTubs1Height;
    double CryostatTubs2InnerRadius;
    double CryostatTubs2OuterRadius;
//   double CryostatTubs2Height;
    double CryostatTubs3InnerRadius;
    double CryostatTubs3OuterRadius;
//   double CryostatTubs3Height;
    double CryostatTubs4InnerRadius;
    double CryostatTubs4OuterRadius;
//   double CryostatTubs4Height;
    double CryostatPolyconeZ1;
    double CryostatPolyconeZ2;
    double CryostatPolyconeZ3;
    double CryostatPolyconeZ4;
    double CryostatPolyconeZ5;
    double CryostatPolyconeZ6;
    double CryostatPolyconeZ7;
    double CryostatPolyconeZ8;
    double CryostatPolyconeZ9;
    double CryostatPolyconeZ10;
    double CryostatPolyconeZ11;
    double CryostatPolyconeZ12;
    double CryostatPolyconeZ13;
    double CryostatPolyconeZ14;

//--- Chamber Subtracted for Cooling Finger ---
    double ChamberTubsRadius;
    double ChamberTubsHeight;

//--- Copper Shield ---
    double CopperShieldThickness;
    double CopperShieldHalfX;
    double CopperShieldHalfY;
    double CopperShieldHalfZ;

//--- Copper Shield Subtracted for Cooling Finger ---
    double CopperShieldSubTubsRadius;
    double CopperShieldSubTubsHeight;

//--- Pb Shield ---
    double LeadShieldThickness;
    double LeadShieldHalfX;
    double LeadShieldHalfY;
    double LeadShieldHalfZ;

//--- Pb Shield Subtracted for Cooling Finger ---
    double LeadShieldSubTubsRadius;
    double LeadShieldSubTubsHeight;

//--- Polyethylene ---
    double PEShiledThickness;
    double PEShiledLowerThickness;
    double PEShieldHalfX;
    double PEShieldHalfY;
    double PEShieldHalfZ;
    double PEInnerCenOffOuterCen;

//--- PE Shield Subtracted for Cooling Finger ---
    double PEShieldSubTubsRadius;
    double PEShieldSubTubsHeight;


//--- Pb Sample ---
    double SampleRadius;
    double SampleHeight;
    double SampleZOffset;

//--- PE hat inside chamber---
    double PEHatHeight;
    double PEHatInnerHeight;
    double PEHatOuterRadius;
    double PEHatInnerRadius;
    double PEHatZOffset;

    //--- cryostat shell ---

    double CryostatSubTubsRadius;
    double CryostatSubTubsHeight;

    double PEinCoolingFingerHeight;
    double PEinCoolingFingerRadius;
};


#endif //BAMBOOMC_CSBEDETECTOR_HH
