#ifndef SAMPLECYLINDERDETECTOR_H
#define SAMPLECYLINDERDETECTOR_H

#include "detector/BambooDetectorPart.hh"

class SampleCylinderDetector : public BambooDetectorPart
{
public:
  SampleCylinderDetector(const G4String &name);
  virtual G4bool construct();

private:
  double _radius;
  double _height;
  double _shiftX;
  double _shiftY;
  double _shiftZ;
    G4String _material;
    bool _sensitive;
};


#endif // SAMPLECYLINDERDETECTOR_H
