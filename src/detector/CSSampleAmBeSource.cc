//
// Created by herbertqiao on 8/18/16.
//

#include "detector/CSSampleAmBeSource.hh"


#include <G4Material.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4LogicalVolume.hh>
#include <G4Tubs.hh>
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"

namespace
{

    BambooDetectorPart *createCSSampleAmBeSource(const G4String &name)
    {
        return new CSSampleAmBeSource(name);
    }

    const std::string CSSampleAmBeSourceName("CSSampleAmBeSource");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(CSSampleAmBeSourceName,
                                                                                    createCSSampleAmBeSource);
}

CSSampleAmBeSource::CSSampleAmBeSource(const G4String &name)
        : BambooDetectorPart(name)
{
    DetectorParameters dp = BambooGlobalVariables::Instance()
            ->findDetectorPartParameters(_partName);
    _shiftX = BambooUtils::evaluate(dp.getParameterAsString("shift_x"));
    _shiftY = BambooUtils::evaluate(dp.getParameterAsString("shift_y"));
    _shiftZ = BambooUtils::evaluate(dp.getParameterAsString("shift_z"));
}

G4bool CSSampleAmBeSource::construct()
{
    G4Material *ss = G4Material::GetMaterial("SS304LSteel");
    G4Material *abpowder = G4Material::GetMaterial("AmBepowder");
    G4double samplehalfz = 8.0 / 2.0 * mm;
    G4double sampleouterradius = 8.0 / 2.0 * mm;
    G4double sampleinnerradius = 4.0 / 2.0 * mm;
    G4double shellT = 2.0 * mm;
    G4double activeZ = 4.0 * mm;

    G4Tubs *pShellTubs = new G4Tubs("ShellTubs", 0.0, sampleouterradius, samplehalfz, 0.0 * deg, 360.0 * deg);
    G4Tubs *pActiveTubs = new G4Tubs("ActiveTubs", 0.0, sampleinnerradius, activeZ / 2.0, 0.0 * deg, 360.0 * deg);

    G4LogicalVolume *m_pAmBeShellLogicalVolume = new G4LogicalVolume(pShellTubs, ss, "AmBeShellLV", 0, 0, 0);
    //m_pAmBeActiveLogicalVolume = new G4LogicalVolume(pActiveTubs, abpowder, "AmBeActiveLV", 0,0,0);
    G4LogicalVolume *m_pAmBeActiveLogicalVolume = new G4LogicalVolume(pActiveTubs, ss, "AmBeActiveLV", 0, 0, 0);

    G4RotationMatrix *xRot90deg = new G4RotationMatrix();
    xRot90deg->rotateX(90. * deg);

    double ChamberHeight = 350.0 * mm;
    double PEHatTopSurfaceToChamberTopSurface = 119.0 * mm;

    G4PVPlacement *m_pAmBeShellPhysicalVolume = new G4PVPlacement(xRot90deg,
                                                                  G4ThreeVector(-40. * mm, 0.0,
                                                                                ChamberHeight * 0.5 -
                                                                                PEHatTopSurfaceToChamberTopSurface +
                                                                                1.0 * mm + sampleouterradius),
                                                                  m_pAmBeShellLogicalVolume, "AmBeShell",
                                                                  _parentPart->getContainerLogicalVolume(), false, 0);

    G4PVPlacement *m_pAmBeActivePhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.0),
                                                                   m_pAmBeActiveLogicalVolume, "AmBeSource",
                                                                   m_pAmBeShellLogicalVolume, false, 0);

}

