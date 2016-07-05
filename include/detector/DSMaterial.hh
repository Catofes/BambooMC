//
// Created by herbertqiao on 7/5/16.
//

#ifndef BAMBOOMC_DSMATERIAL_HH
#define BAMBOOMC_DSMATERIAL_HH


#include "detector/BambooMaterial.hh"

class DSMaterial : public BambooMaterial
{
public:
    DSMaterial(const G4String &name);

    virtual void defineMaterials();
};


#endif //BAMBOOMC_DSMATERIAL_HH
