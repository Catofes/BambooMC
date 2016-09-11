//
// Created by herbertqiao on 7/5/16.
//

#include <G4Material.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4LogicalVolume.hh>
#include "detector/SampleLaboratory.hh"
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"

namespace
{

    BambooDetectorPart *createSampleLaboratory(const G4String &name)
    {
        return new SampleLaboratory(name);
    }

    const std::string SampleLaboratoryName("SampleLaboratory");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(SampleLaboratoryName,
                                                                                    createSampleLaboratory);
}


SampleLaboratory::SampleLaboratory(const G4String &name)
        : BambooDetectorPart(name)
{
    DetectorParameters dp = BambooGlobalVariables::Instance()
            ->findDetectorPartParameters(_partName);
    _halfX = BambooUtils::evaluate(dp.getParameterAsString("half_x"));
    _halfY = BambooUtils::evaluate(dp.getParameterAsString("half_y"));
    _halfZ = BambooUtils::evaluate(dp.getParameterAsString("half_z"));
    if (_halfX <= 0)
        _halfX = 1 * m;
    if (_halfY <= 0)
        _halfY = 1 * m;
    if (_halfZ <= 0)
        _halfZ = 1 * m;
}

G4bool SampleLaboratory::construct()
{
    G4cout << "Sample Laboratory Found." << G4endl;
    G4Material *Air = G4Material::GetMaterial("G4_AIR");
    G4Box *worldBox = new G4Box("LabBox", _halfX, _halfY, _halfZ);
    _partLogicalVolume = new G4LogicalVolume(worldBox, Air, "LabLogicalVolume", 0, 0, 0);
    _partPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(), _partLogicalVolume, "Lab", 0, false, 0);
    _partContainerLogicalVolume = _partLogicalVolume;

    G4cout << "Sample Laboratory Constructed." << G4endl;
    return true;
}