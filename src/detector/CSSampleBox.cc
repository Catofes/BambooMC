//
// Created by herbertqiao on 7/5/16.
//

#include <G4Material.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4LogicalVolume.hh>
#include "detector/CSSampleBox.hh"
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"

namespace
{

    BambooDetectorPart *createCSSampleBox(const G4String &name)
    {
        return new CSSampleBox(name);
    }

    const std::string CSSampleBoxName("CSSampleBox");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(CSSampleBoxName, createCSSampleBox);
}

CSSampleBox::CSSampleBox(const G4String &name)
        : BambooDetectorPart(name)
{
    DetectorParameters dp = BambooGlobalVariables::Instance()
            ->findDetectorPartParameters(_partName);
    _halfX = BambooUtils::evaluate(dp.getParameterAsString("half_x"));
    _halfY = BambooUtils::evaluate(dp.getParameterAsString("half_y"));
    _halfZ = BambooUtils::evaluate(dp.getParameterAsString("half_z"));
    _shiftX = BambooUtils::evaluate(dp.getParameterAsString("shift_x"));
    _shiftY = BambooUtils::evaluate(dp.getParameterAsString("shift_y"));
    _shiftZ = BambooUtils::evaluate(dp.getParameterAsString("shift_z"));
    _material = dp.getParameterAsString("material");
    _detectorType = dp.getParameterAsString("type");
    if (_halfX <= 0)
        _halfX = 10 * cm;
    if (_halfY <= 0)
        _halfY = 10 * cm;
    if (_halfZ <= 0)
        _halfZ = 10 * cm;
    if (_material == "")
        throw std::runtime_error("No Material Found For Smaple.");
}

G4bool CSSampleBox::construct()
{
    G4cout << "Counting Station Sample Box Found." << G4endl;
    G4Material *sampleMaterial = G4Material::GetMaterial(_material);
    if (!sampleMaterial)
        throw std::runtime_error("Can not find material for sample.");

    G4Box *sampleBox = new G4Box("pmmabox", _halfX, _halfY, _halfZ);
    _partLogicalVolume = new G4LogicalVolume(sampleBox, sampleMaterial, "sampleBoxLV", 0, 0, 0);
    G4ThreeVector loc(0, 0, 0);
    if (_parentPart->getType() == "CSCEMMXDetector")
        //G4ThreeVector(-40.0*mm, 0.0, ChamberHeight*0.5- PEHatTopSurfaceToChamberTopSurface+1.0*mm+0.5*pmmaH)
        loc.set(-40 * mm + _shiftX, _shiftY, 57 * mm + _halfZ + _shiftZ);
    else if (_parentPart->getType() == "CSBEDetector")
        //G4ThreeVector(DistanceCryostatCuWall-54.5*mm,0.0,PEHatZOffset+PEHatHeight/2.0+0.5*pmmaH)
        loc.set(-44 * mm + _shiftX, _shiftY, 0.9 * mm + _halfZ + _shiftZ);
    else
        loc.set(0, 0, 0);
    _partPhysicalVolume = new G4PVPlacement(0, loc, _partLogicalVolume, "sample",
                                            _parentPart->getContainerLogicalVolume(), false, 0);
    G4cout << "Counting Station Sample Box Constructed" << G4endl;
    return true;
}