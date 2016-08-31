//
// Created by herbertqiao on 7/5/16.
//

#include "detector/CSMaterial.hh"
#include "detector/BambooMaterialFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"

#include <G4Material.hh>
#include <G4NistManager.hh>
#include <vector>

namespace
{

    BambooMaterial *createCSMaterial()
    {
        return new CSMaterial("CSMaterial");
    }

    const std::string CSMaterialName("CSMaterial");

    const bool registered = BambooMaterialFactory::Instance()->registerMaterial(CSMaterialName, createCSMaterial);
}

CSMaterial::CSMaterial(const G4String &name) :
        BambooMaterial(name)
{
    G4cout << "DetectorStation Material Found." << G4endl;
}

void CSMaterial::defineMaterials()
{
    G4NistManager *pNistManager = G4NistManager::Instance();
    vector<G4Element *> elementVec;
    vector<G4Material *> materialVec;

    G4Element *H = pNistManager->FindOrBuildElement(1);
    elementVec.push_back(H);
    G4Element *C = pNistManager->FindOrBuildElement(6);
    elementVec.push_back(C);
    G4Element *N = pNistManager->FindOrBuildElement(7);
    elementVec.push_back(N);
    G4Element *O = pNistManager->FindOrBuildElement(8);
    elementVec.push_back(O);
    G4Element *F = pNistManager->FindOrBuildElement(9);
    elementVec.push_back(F);
    G4Element *Mg = pNistManager->FindOrBuildElement(12);
    elementVec.push_back(Mg);
    G4Element *Al = pNistManager->FindOrBuildElement(13);
    elementVec.push_back(Al);
    G4Element *Si = pNistManager->FindOrBuildElement(14);
    elementVec.push_back(Si);
    G4Element *P = pNistManager->FindOrBuildElement(15);
    elementVec.push_back(P);
    G4Element *S = pNistManager->FindOrBuildElement(16);
    elementVec.push_back(S);
    G4Element *Cl = pNistManager->FindOrBuildElement(17);
    elementVec.push_back(Cl);
    G4Element *K = pNistManager->FindOrBuildElement(19);
    elementVec.push_back(K);
    G4Element *Ca = pNistManager->FindOrBuildElement(20);
    elementVec.push_back(Ca);
    G4Element *Cr = pNistManager->FindOrBuildElement(24);
    elementVec.push_back(Cr);
    G4Element *Mn = pNistManager->FindOrBuildElement(25);
    elementVec.push_back(Mn);
    G4Element *Fe = pNistManager->FindOrBuildElement(26);
    elementVec.push_back(Fe);
    G4Element *Ni = pNistManager->FindOrBuildElement(28);
    elementVec.push_back(Ni);
    G4Element *Cu = pNistManager->FindOrBuildElement(29);
    elementVec.push_back(Cu);
    G4Element *Mo = pNistManager->FindOrBuildElement(42);
    elementVec.push_back(Mo);
    G4Element *La = pNistManager->FindOrBuildElement(57);
    elementVec.push_back(La);
    G4Element *Pb = pNistManager->FindOrBuildElement(82);
    elementVec.push_back(Pb);
    G4Element *Th = pNistManager->FindOrBuildElement(90);
    elementVec.push_back(Th);
    G4Element *Sn = pNistManager->FindOrBuildElement(50);
    elementVec.push_back(Sn);
    //G4Element *Am = new G4Element("Americium", "Am", 95., 241.0*g/mole); // Am241, AmBe powder
    G4Element *Am = pNistManager->FindOrBuildElement(95);
    elementVec.push_back(Am);
    G4Element *Be = new G4Element("Beryllium", "Be", 4.,  9.0121822*g/mole); // Be9, AmBe powder
    elementVec.push_back(Be);


    G4Isotope *Ge70 = new G4Isotope("Ge70", 32, 70, 69.92 * g / mole);
    G4Isotope *Ge72 = new G4Isotope("Ge72", 32, 72, 71.92 * g / mole);
    G4Isotope *Ge73 = new G4Isotope("Ge73", 32, 73, 73.0 * g / mole);
    G4Isotope *Ge74 = new G4Isotope("Ge74", 32, 74, 74.0 * g / mole);
    G4Isotope *Ge76 = new G4Isotope("Ge76", 32, 76, 76.0 * g / mole);

    G4int nIsotopes = 5;
    G4Element *elGeNat = new G4Element("naturalGermanium", "GeNat", nIsotopes);
    elGeNat->AddIsotope(Ge70, 20.9 * perCent);
    elGeNat->AddIsotope(Ge72, 27.5 * perCent);
    elGeNat->AddIsotope(Ge73, 7.7 * perCent);
    elGeNat->AddIsotope(Ge74, 36.3 * perCent);
    elGeNat->AddIsotope(Ge76, 7.6 * perCent);

    G4Element *elGeEnr = new G4Element("enrichedGermanium", "GeEnr", nIsotopes);
    elGeEnr->AddIsotope(Ge70, 0.0 * perCent);
    elGeEnr->AddIsotope(Ge72, 0.1 * perCent);
    elGeEnr->AddIsotope(Ge73, 0.2 * perCent);
    elGeEnr->AddIsotope(Ge74, 13.1 * perCent);
    elGeEnr->AddIsotope(Ge76, 86.6 * perCent);

//---> soldering tin simulation
    G4Isotope *Sn116 = new G4Isotope("Sn116", 50, 116, 116.0 * g / mole);
    G4Isotope *Sn117 = new G4Isotope("Sn117", 50, 117, 117.0 * g / mole);
    G4Isotope *Sn118 = new G4Isotope("Sn118", 50, 118, 118.0 * g / mole);
    G4Isotope *Sn119 = new G4Isotope("Sn119", 50, 119, 119.0 * g / mole);
    G4Isotope *Sn120 = new G4Isotope("Sn120", 50, 120, 120.0 * g / mole);
    G4Isotope *Sn122 = new G4Isotope("Sn122", 50, 122, 122.0 * g / mole);
    G4Isotope *Sn124 = new G4Isotope("Sn124", 50, 124, 124.0 * g / mole);

    nIsotopes = 7;
    G4Element *elSnNat = new G4Element("naturalTin", "SnNat", nIsotopes);
    elSnNat->AddIsotope(Sn116, 15.0 * perCent);
    elSnNat->AddIsotope(Sn117, 8.0 * perCent);
    elSnNat->AddIsotope(Sn118, 24.0 * perCent);
    elSnNat->AddIsotope(Sn119, 9.0 * perCent);
    elSnNat->AddIsotope(Sn120, 33.0 * perCent);
    elSnNat->AddIsotope(Sn122, 5.0 * perCent);
    elSnNat->AddIsotope(Sn124, 6.0 * perCent);


    //------------------------------------- air -------------------------------------
    G4Material *G4_AIR = pNistManager->FindOrBuildMaterial("G4_AIR");
    materialVec.push_back(G4_AIR);

    //----------------------------------- vacuum ------------------------------------
    G4Material *Vacuum = new G4Material("Vacuum", 1.e-20 * g / cm3, 2, kStateGas);
    Vacuum->AddElement(N, 0.755);
    Vacuum->AddElement(O, 0.245);
    materialVec.push_back(Vacuum);

    //------------------------------------ water ------------------------
    G4Material *Water = new G4Material("Water", 1. * g / cm3, 2, kStateLiquid);
    Water->AddElement(H, 2);
    Water->AddElement(O, 1);
    materialVec.push_back(Water);

    //------------------------------------ Lubricator ------------------------
    G4Material *MoS2 = new G4Material("MoS2", 1. * g / cm3, 2, kStateLiquid);
    MoS2->AddElement(S, 2);
    MoS2->AddElement(Mo, 1);
    materialVec.push_back(MoS2);

    //------------------------------- Epoxy -------------------------------
    G4Material *Epoxy = new G4Material("Epoxy", 1.782 * mg / cm3, 3, kStateSolid);
    Epoxy->AddElement(C, 80.26 * perCent);
    Epoxy->AddElement(H, 7.86 * perCent);
    Epoxy->AddElement(O, 11.88 * perCent);
    materialVec.push_back(Epoxy);

    //---------------------------------- aluminium ----------------------------------
    G4Material *G4_AL = pNistManager->FindOrBuildMaterial("G4_Al");
    materialVec.push_back(G4_AL);

    //------------------------------------- lead ------------------------------------
    G4Material *Lead = new G4Material("Lead", 11.34 * g / cm3, 1);
    Lead->AddElement(Pb, 1);
    materialVec.push_back(Lead);

    //--------------------------------- polyethylene --------------------------------
    G4Material *Polyethylene = new G4Material("Polyethylene", 0.94 * g / cm3, 2, kStateSolid);
    Polyethylene->AddElement(C, 2);
    Polyethylene->AddElement(H, 4);
    materialVec.push_back(Polyethylene);

    //------------------------------------ copper -----------------------------------
    G4int iNbEntries = 3;
    G4Material *Copper = new G4Material("Copper", 8.92 * g / cm3, 1);
    Copper->AddElement(Cu, 1);
    G4double pdCopperPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double pdCopperReflectivity[] = {0.15, 0.2, 0.15};
    G4MaterialPropertiesTable *pCopperPropertiesTable = new G4MaterialPropertiesTable();
    pCopperPropertiesTable->AddProperty("REFLECTIVITY", pdCopperPhotonMomentum, pdCopperReflectivity, iNbEntries);
    Copper->SetMaterialPropertiesTable(pCopperPropertiesTable);
    materialVec.push_back(Copper);

    double density;
    // natural germanium
    density = 5.32 * g / cm3;
    G4Material *natGe = new G4Material("NaturalGe", density, 1);
    natGe->AddElement(elGeNat, 1);
    materialVec.push_back(natGe);

    // enriched germanium
    density = 5.54 * g / cm3;
    G4Material *enrGe = new G4Material("EnrichedGe", density, 1);
    enrGe->AddElement(elGeEnr, 1);
    materialVec.push_back(enrGe);

    // soldering tin
    density = 6.99 * g / cm3;
    G4Material *natSn = new G4Material("SolderingTin", density, 1);
    natSn->AddElement(elSnNat, 1);
    materialVec.push_back(natSn);

    //------- soil 25% air 25% water 45% SiO2 5% TISSUE ------
    // the soil sample from Hongwei, 70mm diameter, 65mm high, total weight 341.1g
    // density (include the plastic box) 1.3636 g/cm3
    pNistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    pNistManager->FindOrBuildMaterial("G4_WATER");
    pNistManager->FindOrBuildMaterial("G4_A-150_TISSUE");
    G4Material *G4Air = G4Material::GetMaterial("G4_AIR");
    G4Material *G4Water = G4Material::GetMaterial("G4_WATER");
    G4Material *G4SILICONDIOXIDE = G4Material::GetMaterial("G4_SILICON_DIOXIDE");
    G4Material *G4TISSUE = G4Material::GetMaterial("G4_A-150_TISSUE");

    G4Material *Soil = new G4Material("Soil", 1.3636 * g / cm3, 4, kStateSolid);
    Soil->AddMaterial(G4Air, 0.25);
    Soil->AddMaterial(G4Water, 0.25);
    Soil->AddMaterial(G4SILICONDIOXIDE, 0.45);
    Soil->AddMaterial(G4TISSUE, 0.05);
    materialVec.push_back(Soil);

    // ----------------------- soldering tin roll ---------------------
    G4Material *SolderingTinRoll = new G4Material("SolderingTinRoll", 3.63 * g / cm3, 2, kStateSolid);
    SolderingTinRoll->AddMaterial(natSn, 0.52);
    SolderingTinRoll->AddMaterial(G4Air, 0.48);
    materialVec.push_back(SolderingTinRoll);

    // ----------------------- soldering tin roll disk /screened on 2012.3.20-21 ---------------------
    G4Material *SolderingTinRollDisk = new G4Material("SolderingTinRollDisk", 5.70 * g / cm3, 2, kStateSolid);
    SolderingTinRollDisk->AddMaterial(natSn, 0.75);
    SolderingTinRollDisk->AddMaterial(G4Air, 0.25);
    materialVec.push_back(SolderingTinRollDisk);

    //----------------------------------- quartz ------------------------------------
    // ref: http://www.sciner.com/Opticsland/FS.htm
    G4Material *Quartz = new G4Material("Quartz", 2.201 * g / cm3, 2, kStateSolid, 168.15 * kelvin, 1.5 * atmosphere);
    Quartz->AddElement(Si, 1);
    Quartz->AddElement(O, 2);
    materialVec.push_back(Quartz);

    //------------------------------- stainless steel -------------------------------
    G4Material *SS304LSteel = new G4Material("SS304LSteel", 8.00 * g / cm3, 5, kStateSolid);
    SS304LSteel->AddElement(Fe, 0.65);
    SS304LSteel->AddElement(Cr, 0.20);
    SS304LSteel->AddElement(Ni, 0.12);
    SS304LSteel->AddElement(Mn, 0.02);
    SS304LSteel->AddElement(Si, 0.01);
    materialVec.push_back(SS304LSteel);

    //------------------------------- Ceramic Al2O3 _--------------------------------
    G4Material *ceramic = new G4Material("ceramic", 2.88 * g / cm3, 2);
    ceramic->AddElement(Al, 2);
    ceramic->AddElement(O, 3);
    materialVec.push_back(ceramic);

    //------------------------------- teflon ----------------------------------------
    G4Material *Teflon = new G4Material("Teflon", 2.2 * g / cm3, 2, kStateSolid);
    Teflon->AddElement(C, 0.240183);
    Teflon->AddElement(F, 0.759817);
    materialVec.push_back(Teflon);

    //------------------------------- La2O3 powder ----------------------------------------
    G4Material *la2o3powder = new G4Material("la2o3powder", 1.00 * g / cm3, 2);
    la2o3powder->AddElement(La, 2);
    la2o3powder->AddElement(O, 3);
    materialVec.push_back(la2o3powder);

    //------------------------------- Carbon Fibre ----------------------------------------
    G4Material *carbonf = new G4Material("CarbonFibre", 1.75 * g / cm3, 1);
    carbonf->AddElement(C, 1);

    //------------------------------- Th(NO3)4.4H2O crystal ----------------------------------------
    G4Material *th228crystal = new G4Material("th228crystal", 2.80 * g / cm3, 4);
    th228crystal->AddElement(Th, 1);
    th228crystal->AddElement(N, 4);
    th228crystal->AddElement(O, 16);
    th228crystal->AddElement(H, 8);
    materialVec.push_back(th228crystal);

    //---------------------------- Polytetrafluoroethylene --------------------------
    G4Material *Polytetrafluoroethylene = new G4Material("Polytetrafluoroethylene", 2.2 * g / cm3, 2, kStateSolid);
    Polytetrafluoroethylene->AddElement(C, 2);
    Polytetrafluoroethylene->AddElement(F, 4);
    materialVec.push_back(Polyethylene);

    //---------------------------- White Copper --------------------------
    G4Material *whitecopper = new G4Material("whitecopper", 7.89 * g / cm3, 2, kStateSolid);
    whitecopper->AddElement(Cu, 0.73481);
    whitecopper->AddElement(Ni, 0.26519);
    materialVec.push_back(whitecopper);

    G4Material *AmBepowder = new G4Material("AmBepowder", 1.821*g/cm3, 3, kStateSolid);
    AmBepowder->AddElement(Am, 1);
    AmBepowder->AddElement(Be, 370);
    AmBepowder->AddElement(O, 2);
    materialVec.push_back(AmBepowder);

    G4cout << "Available materials: " << G4endl;
    for (size_t i = 0; i < materialVec.size(); ++i) {
        G4cout << materialVec[i]->GetName();
        if (i != materialVec.size() - 1)
            G4cout << ", ";
    }
    G4cout << G4endl;
}