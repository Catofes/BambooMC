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
#include "detector/CSCEMMXDetector.hh"

namespace
{

    BambooDetectorPart *createCSCEMMXDetector(const G4String &name)
    {
        return new CSCEMMXDetector(name);
    }

    const std::string CSCEMMXDetectorName("CSCEMMXDetector");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(CSCEMMXDetectorName,
                                                                                    createCSCEMMXDetector);
}

CSCEMMXDetector::CSCEMMXDetector(const G4String &name)
        : BambooDetectorPart(name)
{
    TopShieldOpen = false;
}

G4bool CSCEMMXDetector::construct()
{
    G4cout << "Counting Station CEMMX Detector Found." << G4endl;

    G4Material *Lead = G4Material::GetMaterial("Lead");
    G4Material *Copper = G4Material::GetMaterial("Copper");
    G4Material *Air = G4Material::GetMaterial("G4_AIR");
    G4Material *natGe = G4Material::GetMaterial("NaturalGe");
    G4Material *Vacuum = G4Material::GetMaterial("Vacuum");
    G4Material *CarbonFibre = G4Material::GetMaterial("CarbonFibre");

    G4double pRMin;
    G4double pRMax;
    G4double pDz;
    G4double pSPhi;
    G4double pDPhi;

    G4double dHalfX;
    G4double dHalfY;
    G4double dHalfZ;
    G4double dZShift;

//--- lead shield shell is 80cm x 80cm x 110cm when close, 130cm when open ---
    dHalfX = 40.0 * cm;
    dHalfY = 40.0 * cm;
    if (TopShieldOpen) {
        dHalfZ = 65.0 * cm;
        G4cout << "===============================" << G4endl;
        G4cout << "===== GEMMX Top Shield Open ===" << G4endl;
        G4cout << "===============================" << G4endl;
    }
    else {
        dHalfZ = 55.0 * cm;
        G4cout << "===============================" << G4endl;
        G4cout << "===== GEMMX Top Shield Closed =" << G4endl;
        G4cout << "===============================" << G4endl;
    }

    G4Box *pLeadShieldBox = new G4Box("LeadShieldBox",
                                      dHalfX,
                                      dHalfY,
                                      dHalfZ);
    G4LogicalVolume *m_pLeadShieldLogicalVolume = new G4LogicalVolume(pLeadShieldBox, Lead,
                                                                      "LeadShieldLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), m_pLeadShieldLogicalVolume, "LeadShield",
                      _parentPart->getContainerLogicalVolume(), false, 0);

//--- copper shield shell s 40 * 40 * 70cm, top and surrounding shield 10cm thick, bottom 25cm thick---
// if open, increase height from 70 to 90cm
    dHalfX = 20.0 * cm;
    dHalfY = 20.0 * cm;
    if (TopShieldOpen) dHalfZ = 45.0 * cm;
    else dHalfZ = 35.0 * cm;

    G4Box *pCopperShieldBox = new G4Box("CopperShieldBox",
                                        dHalfX,
                                        dHalfY,
                                        dHalfZ);
    G4LogicalVolume *m_pCopperShieldLogicalVolume = new G4LogicalVolume(pCopperShieldBox, Copper,
                                                                        "CopperShieldLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), m_pCopperShieldLogicalVolume, "CopperShield",
                      m_pLeadShieldLogicalVolume, false, 0);

//--- counting chamber 20cm * 20cm * 35cm---
// if open, increase height to 55cm
    dHalfX = 10.0 * cm;
    dHalfY = 10.0 * cm;
    if (TopShieldOpen) {
        dHalfZ = 27.5 * cm;
        dZShift = 7.5 * cm;
    }
    else {
        dHalfZ = 17.5 * cm;
        dZShift = 7.5 * cm;
    }

    G4Box *pChamberBox = new G4Box("ChamberBox",
                                   dHalfX,
                                   dHalfY,
                                   dHalfZ);
    G4LogicalVolume *m_pChamberLogicalVolume = new G4LogicalVolume(pChamberBox, Air,
                                                                   "ChamberLogicalVolume", 0, 0, 0);
    _partPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., dZShift), m_pChamberLogicalVolume, "Chamber",
                                            m_pCopperShieldLogicalVolume, false, 0);
    _partContainerLogicalVolume = m_pChamberLogicalVolume;
//--- cryostat shell made of carbon fiber is a cylinder 108mm in diameter and 230mm high---
//   the distance from the top surface to the top of counting chamber is 350-230mm = 120mm
//   and it is 4cm away from the center to the -x side
//   thus its center inside counting chamber is (-40.0*mm, 0.0, -175mm+115mm = -60mm)
//   if open, distance from top surface to top of counting chamber is 320mm
//   z shift is -275mm+115mm = -160mm
    pRMin = 0.0;
    pRMax = 108.0 / 2.0 * mm;
    pDz = 230.0 / 2.0 * mm;
    pSPhi = 0.0 * deg;
    pDPhi = 360.0 * deg;
    if (TopShieldOpen) { dZShift = -160.0 * mm; }
    else { dZShift = -60.0 * mm; }
    G4Tubs *pCryostatOuterTubs = new G4Tubs("CryostatOuterTubs", pRMin, pRMax, pDz, pSPhi, pDPhi);
    G4LogicalVolume *m_pCryostatLogicalVolume = new G4LogicalVolume(pCryostatOuterTubs, CarbonFibre,
                                                                    "CryostatLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(-40.0 * mm, 0., dZShift), m_pCryostatLogicalVolume, "Cryostat",
                      m_pChamberLogicalVolume, false, 0);

//--- PE hat right on top of the cryostat ---
// the thickness is 1mm, the diameter is the same as cryostat
// the distance from the top surface to the top of counting chamber is 119mm
// thus its center inside the counting chamber is at 175mm - 119mm - 0.5mm = 55.5mm
// if open, distance from PE hat top surface to the top of counting chamber is 319mm
//          z shift 275 - 319-0.5 = -44.5mm
/*
    pRMin=0.0;
    pRMax=108.0/2.0*mm;
    pDz  =1.0/2.0*mm;
    pSPhi=0.0*deg;
    pDPhi=360.0*deg;
    if (TopShieldOpen) { dZShift = -44.5*mm; }
    else               { dZShift =  55.5*mm; }

    G4Tubs *pPEHatTubs = new G4Tubs("PEHatTubs",pRMin, pRMax, pDz, pSPhi, pDPhi);
    m_pPEHatLogicalVolume = new G4LogicalVolume(pPEHatTubs,Polyethylene,"PEHatLogicalVolume", 0, 0, 0);
    m_pPEHatPhysicalVolume = new G4PVPlacement(0, G4ThreeVector(-40.0*mm, 0., dZShift),
        m_pPEHatLogicalVolume, "PEHat", m_pChamberLogicalVolume, false, 0);
*/

//--- cryostat inner vacuum part, the top and bottom of carbon fiber are 0.9mm thick, the side is 1.6mm thick
//  thus the vacuum is 230.0-0.9*2.0= 228.2mm high, 108.0/2.0-1.6=52.4mm in radius
    pRMin = 0.0;
    pRMax = 52.4 * mm;
    pDz = 228.2 / 2.0 * mm;
    pSPhi = 0.0 * deg;
    pDPhi = 360.0 * deg;
    G4Tubs *pCryostatInnerTubs = new G4Tubs("CryostatInnerTubs", pRMin, pRMax, pDz, pSPhi, pDPhi);
    G4LogicalVolume *m_pCryostatVacuumLogicalVolume = new G4LogicalVolume(pCryostatInnerTubs, Vacuum,
                                                                          "CryostatInnerLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), m_pCryostatVacuumLogicalVolume, "CryostatVacuum",
                      m_pCryostatLogicalVolume, false, 0);

//--- a copper cup holding the HPGe
// the total height is 130mm, the oute diameter is 100mm
// the cup side is 1.5mm thick, bottom is 3mm thick, no top cover
// the cup top surface is 5mm below the bottom surface of the top carbon fibre entrance window
// thus the cup z shift is (228.2-130.0)*0.5-5=49.1-5.0=44.1

    pRMin = 0.0;
    pRMax = 100.0 / 2.0 * mm;
    pDz = 130.0 / 2.0 * mm;
    pSPhi = 0.0 * deg;
    pDPhi = 360.0 * deg;
    G4Tubs *pCopperCupTubsOuter = new G4Tubs("CopperCupTubsOuter", pRMin, pRMax, pDz, pSPhi, pDPhi);
    pRMax = 100.0 / 2.0 * mm - 1.5 * mm;
    pDz = (130.0 - 3.0) / 2.0 * mm;
    G4Tubs *pCopperCupTubsInner = new G4Tubs("CopperCupTubsInner", pRMin, pRMax, pDz, pSPhi, pDPhi);

    G4SubtractionSolid *pCopperCupTubs = new G4SubtractionSolid("CopperCupTubs",
                                                                pCopperCupTubsOuter, pCopperCupTubsInner,
                                                                0, G4ThreeVector(0, 0, 1.5 * mm));

    G4LogicalVolume *m_pCopperCupLogicalVolume = new G4LogicalVolume(pCopperCupTubs, Copper, "CopperCupLogicalVolume",
                                                                     0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 44.1 * mm), m_pCopperCupLogicalVolume, "CopperCup",
                      m_pCryostatVacuumLogicalVolume, false, 0);

//--- HPGe ---
// the total crystal is 93.8mm in diameter, 103.7mm in height, the side deadlayer is 0.7mm
// the active volume is 46.9-0.7=46.2mm in radius, 103.7mm in height
// the inner core hole is 11.2mm in diameter, and 89.9mm in depth, ignore the spherical shape of the top end
// the HPGe top surface is 5mm below the crystal vacuum top surface
// thus the z shift is (228.2-103.7)*0.5-5.0=62.25-5.0=57.25mm

    pRMin = 0.0;
    pRMax = 46.2 * mm;
    pDz = 103.7 / 2.0 * mm;
    pSPhi = 0.0 * deg;
    pDPhi = 360.0 * deg;
    G4Tubs *pCrystalTubsOuter = new G4Tubs("CrystalTubsOuter", pRMin, pRMax, pDz, pSPhi, pDPhi);
    pRMax = 11.2 / 2.0 * mm;
    pDz = 89.9 / 2.0 * mm;
    G4Tubs *pCrystalTubsBoreHole = new G4Tubs("CrystalTubsBoreHole", pRMin, pRMax, pDz, pSPhi, pDPhi);
    G4SubtractionSolid *pCrystalTubs = new G4SubtractionSolid("CrystalTubs",
                                                              pCrystalTubsOuter, pCrystalTubsBoreHole,
                                                              0, G4ThreeVector(0, 0, -(103.7 - 89.9) * 0.5 * mm));

    G4LogicalVolume *m_pCrystalLogicalVolume = new G4LogicalVolume(pCrystalTubs, natGe, "CrystalLogicalVolume", 0, 0,
                                                                   0);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 57.25 * mm), m_pCrystalLogicalVolume, "Crystal",
                      m_pCryostatVacuumLogicalVolume, false, 0);


    G4String SDName = _partName;
    SDName.append(G4String("SDName"));
    PandaXSensitiveDetector *xeSD = new PandaXSensitiveDetector(SDName);
    G4SDManager *sdManager = G4SDManager::GetSDMpointer();
    sdManager->AddNewDetector(xeSD);
    m_pCrystalLogicalVolume->SetSensitiveDetector(xeSD);

    G4VisAttributes *pHPGeVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 1.0));
    pHPGeVisAtt->SetVisibility(true);
    pHPGeVisAtt->SetForceSolid(true);
    m_pCrystalLogicalVolume->SetVisAttributes(pHPGeVisAtt);

//--- crystal deadlayer ---
    pRMin = 46.2 * mm;
    pRMax = 46.9 * mm;
    pDz = 103.7 / 2.0 * mm;
    pSPhi = 0.0 * deg;
    pDPhi = 360.0 * deg;
    G4Tubs *pCrystalDeadlayerTubs = new G4Tubs("CrystalDeadlayerTubs", pRMin, pRMax, pDz, pSPhi, pDPhi);
    G4LogicalVolume *m_pCrystalDeadlayerLogicalVolume = new G4LogicalVolume(pCrystalDeadlayerTubs, natGe,
                                                                            "CrystalDeadlayerLogicalVolume", 0, 0, 0);
    new G4PVPlacement(0, G4ThreeVector(0, 0, 57.25 * mm), m_pCrystalDeadlayerLogicalVolume, "CrystalDeadlayer",
                      m_pCryostatVacuumLogicalVolume, false, 0);

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

    G4VisAttributes *pCrystalDeadlayerVisAtt = new G4VisAttributes(hCoolingFingerColor);
    pCrystalDeadlayerVisAtt->SetVisibility(true);
    pCrystalDeadlayerVisAtt->SetForceSolid(true);
    m_pCrystalDeadlayerLogicalVolume->SetVisAttributes(pCrystalDeadlayerVisAtt);

    G4cout << "Counting Station CEMMX Detector Constructed." << G4endl;
    return true;
}