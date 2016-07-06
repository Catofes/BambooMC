//
// Created by herbertqiao on 7/5/16.
//

#include "detector/BambooDetectorFactory.hh"
#include <G4Material.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Tubs.hh>
#include <G4SubtractionSolid.hh>
#include <G4SDManager.hh>
#include <G4Color.hh>
#include <G4VisAttributes.hh>
#include <analysis/PandaXSensitiveDetector.hh>
#include <G4UnionSolid.hh>
#include <G4Torus.hh>
#include <G4Polycone.hh>
#include "detector/CSBEDetector.hh"

namespace
{

    BambooDetectorPart *createCSBEDetector(const G4String &name)
    {
        return new CSBEDetector(name);
    }

    const std::string CSBEDetectorName("CSBEDetector");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(CSBEDetectorName,
                                                                                    createCSBEDetector);
}

CSBEDetector::CSBEDetector(const G4String &name)
        : BambooDetectorPart(name)
{
    _typeName = "CSBEDetector";
    HPGeRadius = 30.5 * mm;
    HPGeHeight = 31.0 * mm;
    HPGeEnteranceWindowThickness = 0.0004 * mm;
    HPGeOuterElectrodeThickness = 0.6 * mm;
    HPGePPlusRadius = 5.0 * mm;
    HPGePPlusDepth = 1.0 * mm;

//--- Chamber ---
    ChamberHalfX = 10.0 * cm;
    ChamberHalfY = 10.0 * cm;
    ChamberHalfZ = 20.0 * cm;

//--- distance from Cryostat to copper wall, minimum distance

    DistanceCryostatCuWall = 10.5 * mm;

//--- Cryostat inside chamber ---

    CryostatInnerRadius = 44.0 * mm;
    CryostatThickness = 1.5 * mm;
    CryostatRadius = 45.5 * mm;
    CryostatInnerHeight = 193.0 * mm;
    CryostatHeight = 196.0 * mm;
    CryostatWindowThickness = 0.5 * mm;
    CryostatZOffset = 0.0 - ChamberHalfZ + CryostatHeight / 2.0;//-102mm


//--- Cryostat Subtracted for Cooling Finger ---

    CryostatSubTubs1Radius = 16.0 * mm;
    CryostatSubTubs1Height = 115.5 * mm;
    CryostatSubTubs2Radius = 16.0 * mm;
    CryostatSubTubs2Height = 29.5 * mm + DistanceCryostatCuWall;
    CryostatSubTorusOuterRadius = 16.0 * mm;
    CryostatSubTorusInnerRadius = 0.0 * mm;
    CryostatSubTorusRadius = 16.0001 * mm;

//--- Cooling Finger inside the cyostat ---

    CryostatTubs1InnerRadius = 36.5 * mm;
    CryostatTubs1OuterRadius = 38.0 * mm;
//   CryostatTubs1Height=70.0*mm;
    CryostatTubs2InnerRadius = 38.0 * mm;
    CryostatTubs2OuterRadius = 39.5 * mm;
//   CryostatTubs2Height=7.0*mm;
    CryostatTubs3InnerRadius = 16.0 * mm;
    CryostatTubs3OuterRadius = 38.0 * mm;
//   CryostatTubs3Height=3.0*mm;
    CryostatTubs4InnerRadius = 16.0 * mm;
    CryostatTubs4OuterRadius = 33.5 * mm;
//   CryostatTubs4Height=7.0*mm;
    CryostatPolyconeZ1 = 0. * mm;
    CryostatPolyconeZ2 = 7. * mm;
    CryostatPolyconeZ3 = 7. * mm;
    CryostatPolyconeZ4 = 10. * mm;
    CryostatPolyconeZ5 = 10. * mm;
    CryostatPolyconeZ6 = 60. * mm;
    CryostatPolyconeZ7 = 60. * mm;
    CryostatPolyconeZ8 = 67. * mm;
    CryostatPolyconeZ9 = 67. * mm;
    CryostatPolyconeZ10 = 71.5 * mm;
    CryostatPolyconeZ11 = 71.5 * mm;
    CryostatPolyconeZ12 = 78.5 * mm;
    CryostatPolyconeZ13 = 78.5 * mm;
    CryostatPolyconeZ14 = 80. * mm;

//--- Chamber Subtracted for Cooling Finger ---
    ChamberTubsRadius = 16.0 * mm;
    ChamberTubsHeight = 72.0 * mm;

//--- Copper Shield ---
    CopperShieldThickness = 10.0 * cm;
    CopperShieldHalfX = 20.0 * cm;
    CopperShieldHalfY = 20.0 * cm;
    CopperShieldHalfZ = 30.0 * cm;

//--- Copper Shield Subtracted for Cooling Finger ---
    CopperShieldSubTubsRadius = 16.0 * mm;
    CopperShieldSubTubsHeight = 10.0 * cm;

//--- Pb Shield ---
    LeadShieldThickness = 20.0 * cm;
    LeadShieldHalfX = 40.0 * cm;
    LeadShieldHalfY = 40.0 * cm;
    LeadShieldHalfZ = 50.0 * cm;

//--- Pb Shield Subtracted for Cooling Finger ---
    LeadShieldSubTubsRadius = 16.0 * mm;
    LeadShieldSubTubsHeight = 20.0 * cm;

//--- Polyethylene ---
    PEShiledThickness = 10.0 * cm;
    PEShiledLowerThickness = 20.0 * cm;
    PEShieldHalfX = 50.0 * cm;
    PEShieldHalfY = 50.0 * cm;
    PEShieldHalfZ = 65.0 * cm;
    PEInnerCenOffOuterCen = 5.0 * cm;

//--- PE Shield Subtracted for Cooling Finger ---
    PEShieldSubTubsRadius = 16.0 * mm;
    PEShieldSubTubsHeight = 10.0 * cm;


//--- Pb Sample ---
    SampleRadius = 65.0 * mm;
    SampleHeight = 70.0 * mm;
    SampleZOffset = 100.0 * mm;
    SampleZOffset = 100.0 * mm;

//--- PE hat inside chamber---
    PEHatHeight = 25.5 * mm;
    PEHatInnerHeight = 22.0 * mm;
    PEHatOuterRadius = 48.5 * mm;
    PEHatInnerRadius = CryostatRadius; // 45.5mm
    PEHatZOffset = CryostatZOffset + CryostatHeight / 2.0 - PEHatHeight / 2.0 + 4.9 * mm;//-11.35mm

    //--- cryostat shell ---

    CryostatSubTubsRadius = 16.0 * mm;
    CryostatSubTubsHeight = 60.0 * mm;

    PEinCoolingFingerHeight = 1.0 * mm;
    PEinCoolingFingerRadius = 16.0 * mm;
}

G4bool CSBEDetector::construct()
{
    G4cout << " Counting Station BE Detector Found." << G4endl;

    G4RotationMatrix *xRot90deg = new G4RotationMatrix();
    xRot90deg->rotateX(90. * deg);

    G4RotationMatrix *yRot90deg = new G4RotationMatrix();
    yRot90deg->rotateY(90. * deg);

    G4Material *Lead = G4Material::GetMaterial("Lead");
    G4Material *Copper = G4Material::GetMaterial("Copper");
    G4Material *Aluminium = G4Material::GetMaterial("G4_Al");
    G4Material *Polyethylene = G4Material::GetMaterial("Polyethylene");
    G4Material *Vacuum = G4Material::GetMaterial("Vacuum");
    G4Material *ChamberVacuum = G4Material::GetMaterial("ChamberVacuum");
    G4Material *Epoxy = G4Material::GetMaterial("Epoxy");

//--- polyethylene shield shell ---

    G4Box *pPEShieldBox = new G4Box("PEShieldBox", PEShieldHalfX, PEShieldHalfY, PEShieldHalfZ);
    G4LogicalVolume *m_pPEShieldLogicalVolume = new G4LogicalVolume(pPEShieldBox, Polyethylene, "PEShieldLogicalVolume",
                                                                    0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), m_pPEShieldLogicalVolume, "PEShield",
                      _parentPart->getContainerLogicalVolume(), false, 0);

//--- tubs in polyethylene shield shell subtracted for cooling finger---
    G4Tubs *pPEShieldSubTubs = new G4Tubs("PEShieldSubTubs", 0.0 * cm,
                                          PEShieldSubTubsRadius,
                                          PEShieldSubTubsHeight / 2,
                                          0.0 * deg, 360.0 * deg);
    G4LogicalVolume *m_pPEShieldSubTubsLogicalVolume = new G4LogicalVolume(pPEShieldSubTubs, Copper,
                                                                           "PEShieldSubTubsVolume", 0, 0, 0);
    new G4PVPlacement(yRot90deg, G4ThreeVector(-450.0, 0.0, -122.0), m_pPEShieldSubTubsLogicalVolume, "PEShieldSubTubs",
                      m_pPEShieldLogicalVolume, false, 0);

//--- lead shield shell ---

    G4Box *pLeadShieldBox = new G4Box("LeadShieldBox", LeadShieldHalfX, LeadShieldHalfY, LeadShieldHalfZ);
    G4LogicalVolume *m_pLeadShieldLogicalVolume = new G4LogicalVolume(pLeadShieldBox, Lead, "LeadShieldLogicalVolume",
                                                                      0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., PEInnerCenOffOuterCen), m_pLeadShieldLogicalVolume, "LeadShield",
                      m_pPEShieldLogicalVolume, false, 0);

//--- tubs in lead shield shell subtracted for cooling finger ---

    G4Tubs *pLeadShieldSubTubs = new G4Tubs("LeadShieldSubTubs", 0.0 * cm, LeadShieldSubTubsRadius,
                                            LeadShieldSubTubsHeight / 2, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *m_pLeadShieldSubTubsLogicalVolume = new G4LogicalVolume(pLeadShieldSubTubs, Copper,
                                                                             "LeadShieldSubTubsVolume", 0, 0, 0);
    new G4PVPlacement(yRot90deg, G4ThreeVector(-300.0, 0.0, -172.0), m_pLeadShieldSubTubsLogicalVolume,
                      "LeadShieldSubTubs", m_pLeadShieldLogicalVolume, false, 0);

//--- copper shield shell ---

    G4Box *pCopperShieldBox = new G4Box("CopperShieldBox", CopperShieldHalfX, CopperShieldHalfY, CopperShieldHalfZ);
    G4LogicalVolume *m_pCopperShieldLogicalVolume = new G4LogicalVolume(pCopperShieldBox, Copper,
                                                                        "CopperShieldLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), m_pCopperShieldLogicalVolume, "CopperShield",
                      m_pLeadShieldLogicalVolume, false, 0);

//--- tubs in copper shield subtracted for cooling finger ---

    G4Tubs *pCopperShieldSubTubs = new G4Tubs("CopperShieldSubTubs", 0.0 * cm, CopperShieldSubTubsRadius,
                                              CopperShieldSubTubsHeight / 2, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *m_pCopperShieldSubTubsLogicalVolume = new G4LogicalVolume(pCopperShieldSubTubs, Copper,
                                                                               "CopperShieldSubTubsVolume", 0, 0, 0);
    new G4PVPlacement(yRot90deg, G4ThreeVector(-150.0, 0.0, -172.0), m_pCopperShieldSubTubsLogicalVolume,
                      "CopperShieldSubTubs", m_pCopperShieldLogicalVolume, false, 0);

//--- chamber ---

    G4Box *pChamberBox = new G4Box("ChamberBox", ChamberHalfX, ChamberHalfY, ChamberHalfZ);
    G4LogicalVolume *m_pChamberLogicalVolume = new G4LogicalVolume(pChamberBox, ChamberVacuum,
                                                                   "ChamberLogicalVolume", 0, 0, 0);
    _partPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.),
                                            m_pChamberLogicalVolume, "Chamber", m_pCopperShieldLogicalVolume,
                                            false, 0);
    _partContainerLogicalVolume = m_pChamberLogicalVolume;

    G4Tubs *pCryostatOuterTubs = new G4Tubs("CryostatOuterTubs", 0.0 * cm, CryostatRadius, CryostatHeight / 2.0,
                                            0.0 * deg, 360.0 * deg);
    G4Tubs *pCryostatInnerTubs1 = new G4Tubs("CryostatInnerTubs1", 0.0 * cm, CryostatRadius - CryostatThickness,
                                             CryostatHeight / 2.0 - CryostatThickness, 0.0 * deg, 360.0 * deg);
    G4Tubs *pCryostatInnerTubs2 = new G4Tubs("CryostatInnerTubs2", 0.0 * cm, HPGeRadius,
                                             CryostatThickness / 2.0 - CryostatWindowThickness / 2.0, 0.0 * deg,
                                             360.0 * deg);
    G4UnionSolid *pCryostatInnerTubs = new G4UnionSolid("CryostatInnerTubs", pCryostatInnerTubs1, pCryostatInnerTubs2,
                                                        0, G4ThreeVector(0., 0., 97.0));
    G4SubtractionSolid *pCryostatInitialShell = new G4SubtractionSolid("CryostatInitialShell", pCryostatOuterTubs,
                                                                       pCryostatInnerTubs, 0,
                                                                       G4ThreeVector(0., 0., 0.));
    G4Tubs *pCryostatSubTubs = new G4Tubs("CryostatSubTubs", 0.0 * cm, CryostatSubTubsRadius,
                                          CryostatSubTubsHeight / 2.0, 0.0 * deg, 360.0 * deg);
    G4SubtractionSolid *pCryostatShell = new G4SubtractionSolid("CryostatShell", pCryostatInitialShell,
                                                                pCryostatSubTubs, yRot90deg,
                                                                G4ThreeVector(-44.5, 0.0, -70.0));
    G4LogicalVolume *m_pCryostatLogicalVolume = new G4LogicalVolume(pCryostatShell, Aluminium, "CryostatLogicalVolume",
                                                                    0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(-54.5 + DistanceCryostatCuWall, 0., -102.), m_pCryostatLogicalVolume, "Cryostat",
                      m_pChamberLogicalVolume, false, 0);

//--- chamber cooling finger

    G4Tubs *pCryostatSubTubs1 = new G4Tubs("CryostatSubTubs1", 0.0 * cm, CryostatSubTubs1Radius,
                                           CryostatSubTubs1Height / 2.0, 0.0 * deg, 360.0 * deg);
    G4Tubs *pCryostatSubTubs2 = new G4Tubs("CryostatSubTubs2", 0.0 * cm, CryostatSubTubs2Radius,
                                           CryostatSubTubs2Height / 2.0, 0.0 * deg, 360.0 * deg);
    G4UnionSolid *pCryostatSubTubs1AndTub2 = new G4UnionSolid("CryostatSubTubs1AndTub2", pCryostatSubTubs1,
                                                              pCryostatSubTubs2, yRot90deg, G4ThreeVector(
                    (0.0 - CryostatSubTubs1Radius - CryostatSubTubs2Height * 0.5), 0., -73.75));
    //G4ThreeVector(-30.75,0.,-73.75));
    G4Torus *pCryostatSubTorus = new G4Torus("CryostatSubTorus", CryostatSubTorusInnerRadius,
                                             CryostatSubTorusOuterRadius, CryostatSubTorusRadius, 0 * deg, 90.0 * deg);
    G4UnionSolid *pChamberCoolingFingerSolid = new G4UnionSolid("ChamberCoolingFingerSolid", pCryostatSubTubs1AndTub2,
                                                                pCryostatSubTorus, xRot90deg,
                                                                G4ThreeVector(-16.0, 0., -57.75));
    G4LogicalVolume *m_pChamberCoolingFingerLogicalVolume = new G4LogicalVolume(pChamberCoolingFingerSolid, Copper,
                                                                                "ChamberCoolingFingerLogicalVolume", 0,
                                                                                0, 0);
    new G4PVPlacement(0, G4ThreeVector(-54.5 + DistanceCryostatCuWall, 0., -98.25),
                      m_pChamberCoolingFingerLogicalVolume, "ChamberCoolingFinger", m_pChamberLogicalVolume, false, 0);

//--- cryostat inner volume

    G4SubtractionSolid *pCryostatInnerSolid = new G4SubtractionSolid("CryostatInnerSolid",
                                                                     pCryostatInnerTubs, pChamberCoolingFingerSolid, 0,
                                                                     G4ThreeVector(0., 0., 3.75));
    G4LogicalVolume *m_pCryostatInnerLogicalVolume = new G4LogicalVolume(pCryostatInnerSolid, Vacuum,
                                                                         "CryostatInnerLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(-54.5 * mm + DistanceCryostatCuWall, 0., -102.), m_pCryostatInnerLogicalVolume,
                      "CryostatInnerVolume", m_pChamberLogicalVolume, false, 0);

//--- cryostat window

    G4Tubs *pCryostatWindowTubs = new G4Tubs("CryostatWindowTubs", 0.0 * cm, HPGeRadius, CryostatWindowThickness / 2.0,
                                             0.0 * deg, 360.0 * deg);
    G4LogicalVolume *m_pCryostatWindowLogicalVolume = new G4LogicalVolume(pCryostatWindowTubs, Epoxy,
                                                                          "CryostatWindowLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 97.75 * mm), m_pCryostatWindowLogicalVolume, "CryostatWindow",
                      m_pCryostatLogicalVolume, false, 0);

//--- cooling finger inside the cyostat

    const G4double dCryostatPolyconeZPlane[] = {CryostatPolyconeZ1, CryostatPolyconeZ2, CryostatPolyconeZ3,
                                                CryostatPolyconeZ4, CryostatPolyconeZ5, CryostatPolyconeZ6,
                                                CryostatPolyconeZ7, CryostatPolyconeZ8, CryostatPolyconeZ9,
                                                CryostatPolyconeZ10, CryostatPolyconeZ11, CryostatPolyconeZ12,
                                                CryostatPolyconeZ13, CryostatPolyconeZ14};
    const G4double dCryostatPolyconeInnerRadius[] = {CryostatTubs4InnerRadius, CryostatTubs4InnerRadius,
                                                     CryostatTubs3InnerRadius, CryostatTubs3InnerRadius,
                                                     CryostatTubs1InnerRadius, CryostatTubs1InnerRadius,
                                                     CryostatTubs1InnerRadius, CryostatTubs1InnerRadius,
                                                     CryostatTubs1InnerRadius, CryostatTubs1InnerRadius,
                                                     CryostatTubs1InnerRadius, CryostatTubs1InnerRadius,
                                                     CryostatTubs1InnerRadius, CryostatTubs1InnerRadius};
    const G4double dCryostatPolyconeOuterRadius[] = {CryostatTubs4OuterRadius, CryostatTubs4OuterRadius,
                                                     CryostatTubs3OuterRadius, CryostatTubs3OuterRadius,
                                                     CryostatTubs3OuterRadius, CryostatTubs3OuterRadius,
                                                     CryostatTubs2OuterRadius, CryostatTubs2OuterRadius,
                                                     CryostatTubs1OuterRadius, CryostatTubs1OuterRadius,
                                                     CryostatTubs2OuterRadius, CryostatTubs2OuterRadius,
                                                     CryostatTubs1OuterRadius, CryostatTubs1OuterRadius};
    G4Polycone *pCryostatTubs = new G4Polycone("CryostatTubs", 0.0 * deg, 360.0 * deg, 14,
                                               dCryostatPolyconeZPlane, dCryostatPolyconeInnerRadius,
                                               dCryostatPolyconeOuterRadius);
    G4LogicalVolume *m_pCryostatTubsLogicalVolume = new G4LogicalVolume(pCryostatTubs, Copper,
                                                                        "CryostatTubsLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 11.), m_pCryostatTubsLogicalVolume, "CryostatTubs",
                      m_pCryostatInnerLogicalVolume, false, 0);

//--- PE inside the cooling finger

    G4Tubs *pPEinCoolingFinger = new G4Tubs("PEinCoolingFinger", 0.0 * cm, PEinCoolingFingerRadius,
                                            PEinCoolingFingerHeight / 2.0, 0.0 * deg, 360.0 * deg);
    G4LogicalVolume *m_pPEinCoolingFingerLogicalVolume = new G4LogicalVolume(pPEinCoolingFinger, Polyethylene,
                                                                             "PEinCoolingFinger", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 57.25 * mm), m_pPEinCoolingFingerLogicalVolume, "PEinCoolingFinger",
                      m_pChamberCoolingFingerLogicalVolume, false, 0);

//--- PE Hat inside chamber

    G4Tubs *pPEHatTubsAll = new G4Tubs("PEHatTubsAll", 0.0 * mm, PEHatOuterRadius, PEHatHeight / 2.0, 0.0 * deg,
                                       360.0 * deg);
    G4Tubs *pPEHatTubsSubtracted = new G4Tubs("PEHatTubsSubtracted", 0.0 * mm, PEHatInnerRadius, PEHatInnerHeight / 2.0,
                                              0.0 * deg, 360.0 * deg);
    G4SubtractionSolid *pPEHatTubs = new G4SubtractionSolid("PEHatTubs", pPEHatTubsAll, pPEHatTubsSubtracted, 0,
                                                            G4ThreeVector(0.0, 0.0,
                                                                          PEHatInnerHeight / 2.0 - PEHatHeight / 2.0));

    G4LogicalVolume *m_pPEHatLogicalVolume = new G4LogicalVolume(pPEHatTubs, Polyethylene, "PEHatLogicalVolume", 0, 0,
                                                                 0);
    new G4PVPlacement(0, G4ThreeVector(-54.5 * mm + DistanceCryostatCuWall, 0., PEHatZOffset), m_pPEHatLogicalVolume,
                      "PEHat", m_pChamberLogicalVolume, false, 0);


//--- attributes ---
    G4Colour hPEShieldColor(1., 1., 1., 1.);
    G4Colour hLeadShieldColor(0.500, 0.500, 0.500, 1.0);
    G4Colour hCopperShieldColor(0.835, 0.424, 0.059, 1.);
    G4Colour hChamberColor(1., 0., 1., 1.);
    G4Colour hCryostatColor(1., 1., 1., 1.);
    G4Colour hCryostatInnerVolumeColor(1., 1., 1., 1.);
    G4Colour hCryostatWindowColor(0., 1., 0., 1.);
    G4Colour hPEinCoolingFingerColor(0., 0., 1., 1.);
    G4Colour hCoolingFingerColor(1., 0., 0., 1.);

    G4VisAttributes *pPEShieldVisAtt = new G4VisAttributes(hPEShieldColor);
    pPEShieldVisAtt->SetVisibility(true);
    pPEShieldVisAtt->SetForceSolid(true);
    m_pPEShieldLogicalVolume->SetVisAttributes(pPEShieldVisAtt);

    G4VisAttributes *pLeadShieldVisAtt = new G4VisAttributes(hLeadShieldColor);
    pLeadShieldVisAtt->SetVisibility(true);
    pLeadShieldVisAtt->SetForceSolid(true);
    m_pLeadShieldLogicalVolume->SetVisAttributes(pLeadShieldVisAtt);

    G4VisAttributes *pCopperShieldVisAtt = new G4VisAttributes(hCopperShieldColor);
    pCopperShieldVisAtt->SetVisibility(true);
    pCopperShieldVisAtt->SetForceSolid(true);
    m_pCopperShieldLogicalVolume->SetVisAttributes(pCopperShieldVisAtt);

    G4VisAttributes *pChamberVisAtt = new G4VisAttributes(hChamberColor);
    pChamberVisAtt->SetVisibility(true);
    pChamberVisAtt->SetForceSolid(true);
    m_pChamberLogicalVolume->SetVisAttributes(pChamberVisAtt);

    G4VisAttributes *pCryostatVisAtt = new G4VisAttributes(hCryostatColor);
    pCryostatVisAtt->SetVisibility(true);
    pCryostatVisAtt->SetForceSolid(true);
    m_pCryostatLogicalVolume->SetVisAttributes(pCryostatVisAtt);

    G4VisAttributes *pCryostatWindowVisAtt = new G4VisAttributes(hCryostatWindowColor);
    pCryostatVisAtt->SetVisibility(true);
    pCryostatVisAtt->SetForceSolid(true);
    m_pCryostatWindowLogicalVolume->SetVisAttributes(pCryostatWindowVisAtt);

    G4VisAttributes *pPEinCoolingFingerVisAtt = new G4VisAttributes(hPEinCoolingFingerColor);
    pPEinCoolingFingerVisAtt->SetVisibility(true);
    pPEinCoolingFingerVisAtt->SetForceSolid(true);
    m_pPEinCoolingFingerLogicalVolume->SetVisAttributes(pPEinCoolingFingerVisAtt);

    G4VisAttributes *pPEShieldSubTubsVisAtt = new G4VisAttributes(hCoolingFingerColor);
    pPEShieldSubTubsVisAtt->SetVisibility(true);
    pPEShieldSubTubsVisAtt->SetForceSolid(true);
    m_pPEShieldSubTubsLogicalVolume->SetVisAttributes(pPEShieldSubTubsVisAtt);
    m_pPEHatLogicalVolume->SetVisAttributes(pPEShieldSubTubsVisAtt);

    G4VisAttributes *pLeadShieldSubTubsVisAtt = new G4VisAttributes(hCoolingFingerColor);
    pLeadShieldSubTubsVisAtt->SetVisibility(true);
    pLeadShieldSubTubsVisAtt->SetForceSolid(true);
    m_pLeadShieldSubTubsLogicalVolume->SetVisAttributes(pLeadShieldSubTubsVisAtt);

    G4VisAttributes *pCopperShieldSubTubsVisAtt = new G4VisAttributes(hCoolingFingerColor);
    pCopperShieldSubTubsVisAtt->SetVisibility(true);
    pCopperShieldSubTubsVisAtt->SetForceSolid(true);
    m_pCopperShieldSubTubsLogicalVolume->SetVisAttributes(pCopperShieldSubTubsVisAtt);

    G4VisAttributes *pChamberCoolingFingerVisAtt = new G4VisAttributes(hCoolingFingerColor);
    pChamberCoolingFingerVisAtt->SetVisibility(true);
    pChamberCoolingFingerVisAtt->SetForceSolid(true);
    m_pChamberCoolingFingerLogicalVolume->SetVisAttributes(pChamberCoolingFingerVisAtt);

    G4VisAttributes *pCryostatTubsVisAtt = new G4VisAttributes(hCoolingFingerColor);
    pCryostatTubsVisAtt->SetVisibility(true);
    pCryostatTubsVisAtt->SetForceSolid(true);
    m_pCryostatTubsLogicalVolume->SetVisAttributes(pCryostatTubsVisAtt);

    G4cout << " Counting Station BE Detector Constructed." << G4endl;
    return true;
}