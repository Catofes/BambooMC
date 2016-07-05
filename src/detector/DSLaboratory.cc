//
// Created by herbertqiao on 7/5/16.
//

#include "detector/DSLaboratory.hh"
#include "detector/BambooDetectorFactory.hh"
#include "BambooGlobalVariables.hh"
#include "BambooUtils.hh"

namespace
{

    BambooDetectorPart *createLatexWorld(const G4String &name)
    {
        return new LatexWorld(name);
    }

    const std::string LatexWorldName("LatexWorld");

    const bool registered = BambooDetectorFactory::Instance()->registerDetectorPart(LatexWorldName, createLatexWorld);
}