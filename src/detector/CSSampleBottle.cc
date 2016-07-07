//
// Created by herbertqiao on 7/7/16.
//
#include <G4Material.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4LogicalVolume.hh>
#include <G4Tubs.hh>
#include <G4SubtractionSolid.hh>
#include <G4Polycone.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"
#include "detector/CSSampleBottle.hh"

namespace
{

    BambooDetectorPart *createCSSampleBottle(const G4String &name)
    {
        return new CSSampleBottle(name);
    }

    const std::string CSSampleBottleName("CSSampleBottle");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(CSSampleBottleName,
                                                                                    createCSSampleBottle);
}

CSSampleBottle::CSSampleBottle(const G4String &name)
        : BambooDetectorPart(name)
{
    DetectorParameters dp = BambooGlobalVariables::Instance()
            ->findDetectorPartParameters(_partName);
    _shiftX = BambooUtils::evaluate(dp.getParameterAsString("shift_x"));
    _shiftY = BambooUtils::evaluate(dp.getParameterAsString("shift_y"));
    _shiftZ = BambooUtils::evaluate(dp.getParameterAsString("shift_z"));
    _detectorType = dp.getParameterAsString("type");
}

G4bool CSSampleBottle::construct()
{
    G4cout << "Counting Station Sample Bottle Found." << G4endl;

    G4Material *SourcePowder = G4Material::GetMaterial("Soil");
    G4Material *Glass = G4Material::GetMaterial("Quartz");
    G4Material *PE = G4Material::GetMaterial("Polyethylene");
    //G4Material *TestVac = G4Material::GetMaterial("ChamberVacuum");

    G4double PEhatThickness = 1.0 * mm;
    G4double PEhatHeight = 8.0 * mm;
    G4double PEhatOuterDiameter = 12.0 * mm;
    G4double PEhatInnerDiameter = PEhatOuterDiameter - 2.0 * PEhatThickness;

    G4double GlassThickness = 1.0 * mm;
    G4double GlassZFirst = 0.0;
    G4double GlassZSecond = 25.0 * mm;
    G4double GlassZThird = 25.5 * mm;
    G4double GlassZFourth = 32.0 * mm;
    G4double RGlassOuter = 12.0 * mm;
    G4double RGlassInner = 10.0 * mm;

    G4double PhiStart = 0.0 * deg;
    G4double PhiEnd = 360.0 * deg;

    G4ThreeVector loc(0, 0, 0);
    if (_parentPart->getType() == "CSCEMMXDetector")
        //G4ThreeVector(-40.0*mm, 0.0, ChamberHeight*0.5- PEHatTopSurfaceToChamberTopSurface+1.0*mm+0.5*pmmaH)
        loc.set(-40 * mm + _shiftX, _shiftY, 57 * mm + _shiftZ);
    else if (_parentPart->getType() == "CSBEDetector")
        //G4ThreeVector(DistanceCryostatCuWall-54.5*mm,0.0,PEHatZOffset+PEHatHeight/2.0+0.5*pmmaH)
        loc.set(-44 * mm + _shiftX, _shiftY, 0.9 * mm + _shiftZ);
    else
        loc.set(0, 0, 0);

//-----> PEhat
    G4Tubs *pPEhatTubsOuter = new G4Tubs("PEhatTubsOuter", 0.0, PEhatOuterDiameter / 2.0, PEhatHeight / 2.0, PhiStart,
                                         PhiEnd);
    G4Tubs *pPEhatTubsInner = new G4Tubs("PEhatTubsInner", 0.0, PEhatInnerDiameter / 2.0, PEhatHeight / 2.0, PhiStart,
                                         PhiEnd);
    G4SubtractionSolid *pPEhatTubs = new G4SubtractionSolid("PEhatTubs",
                                                            pPEhatTubsOuter, pPEhatTubsInner,
                                                            0, G4ThreeVector(0, 0, 0.0 - PEhatThickness));
    G4LogicalVolume *m_pPEhatLogicalVolume = new G4LogicalVolume(pPEhatTubs, PE, "PEhatLogicalVolume", 0, 0, 0);

    new G4PVPlacement(0, loc + G4ThreeVector(0, 0, 0.5 * PEhatHeight + GlassZThird),
                      m_pPEhatLogicalVolume, "SourcePEhat", _parentPart->getContainerLogicalVolume(), false, 0);

    G4VisAttributes *pCryostatTubsVisAtt = new G4VisAttributes(G4Colour(0.6, 0.4, 0.0, 1));
    pCryostatTubsVisAtt->SetVisibility(true);
    pCryostatTubsVisAtt->SetForceSolid(true);
    m_pPEhatLogicalVolume->SetVisAttributes(pCryostatTubsVisAtt);
//-----> GlassBottle
    const G4int numZPlane = 4;
    G4double zPlane[numZPlane];
    G4double rInner[numZPlane];
    G4double rOuter[numZPlane];
    zPlane[0] = GlassZFirst;
    zPlane[1] = GlassZSecond;
    zPlane[2] = GlassZThird;
    zPlane[3] = GlassZFourth;
    rOuter[0] = RGlassOuter * 0.5;
    rOuter[1] = RGlassOuter * 0.5;
    rOuter[2] = RGlassInner * 0.5;
    rOuter[3] = RGlassInner * 0.5;
    rInner[0] = RGlassInner * 0.5;
    rInner[1] = RGlassInner * 0.5;
    rInner[2] = RGlassInner * 0.5 - GlassThickness;
    rInner[3] = RGlassInner * 0.5 - GlassThickness;

    G4Polycone *pBottlePolycone = new G4Polycone("BottlePolycone", PhiStart, PhiEnd, numZPlane, zPlane, rInner, rOuter);
    G4LogicalVolume *m_pBottleLogicalVolume = new G4LogicalVolume(pBottlePolycone, Glass, "BottleLogicalVolume", 0, 0,
                                                                  0);
    _partPhysicalVolume = new G4PVPlacement(0, loc, m_pBottleLogicalVolume, "SourceBottle",
                                            _parentPart->getContainerLogicalVolume(), false, 0);

    pCryostatTubsVisAtt = new G4VisAttributes(G4Colour(0.6, 0.4, 0.3, 1));
    pCryostatTubsVisAtt->SetVisibility(true);
    pCryostatTubsVisAtt->SetForceSolid(true);
    m_pBottleLogicalVolume->SetVisAttributes(pCryostatTubsVisAtt);
//-----> SourcePowder
    G4double zSPlane[numZPlane];
    G4double rSInner[numZPlane];
    G4double rSOuter[numZPlane];
    zSPlane[0] = GlassZFirst;
    zSPlane[1] = GlassZSecond - GlassThickness;
    zSPlane[2] = GlassZThird - GlassThickness;
    zSPlane[3] = GlassZFourth - 1.5 * GlassThickness;
    rSOuter[0] = RGlassInner * 0.5;
    rSOuter[1] = RGlassInner * 0.5;
    rSOuter[2] = RGlassInner * 0.5 - GlassThickness;
    rSOuter[3] = RGlassInner * 0.5 - GlassThickness;
    rSInner[0] = 0.0;
    rSInner[1] = 0.0;
    rSInner[2] = 0.0;
    rSInner[3] = 0.0;

    G4Polycone *pSourcePolycone = new G4Polycone("SourcePolycone", PhiStart, PhiEnd, numZPlane, zSPlane, rSInner,
                                                 rSOuter);
    G4LogicalVolume *m_pSourceLogicalVolume = new G4LogicalVolume(pSourcePolycone, SourcePowder, "SourceLogicalVolume",
                                                                  0, 0, 0);
    new G4PVPlacement(0, loc + G4ThreeVector(0, 0, GlassThickness), m_pSourceLogicalVolume, "sample",
                      _parentPart->getContainerLogicalVolume(), false, 0);

    G4cout << "Counting Station Sample Bottle Constructed." << G4endl;
    pCryostatTubsVisAtt = new G4VisAttributes(G4Colour(0.6, 0.4, 0.6, 1));
    pCryostatTubsVisAtt->SetVisibility(true);
    pCryostatTubsVisAtt->SetForceSolid(true);
    m_pSourceLogicalVolume->SetVisAttributes(pCryostatTubsVisAtt);
    return true;
}