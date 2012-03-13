/*
 * SCVAgent.cpp
 */
#include "SCVAgent.h"
#include "GroundAgent.h"

#include "TacticalBuildingPlacer.h"

#include <BWAPI.h>

using namespace BWAPI;


SCVAgent::SCVAgent(Unit &u) 
	: GroundAgent(u)
{}

void SCVAgent::update()
{
	switch (state) {
		case GatherState:
			// Gather minerals
			if (unitTarget->getType().isMineralField()) 
			{
				if (!unit.isGatheringMinerals())
					unit.gather(unitTarget);
			}

			// Gather gas
			else if (unitTarget->getType().isRefinery()) 
			{
				if (!unit.isGatheringGas())
					unit.gather(unitTarget);
			}
			break;

		case BuildState:
			// Return cargo
			if (unit.isCarryingGas() ||	unit.isCarryingMinerals())
				unit.returnCargo();
			// Reserve a build location
			else if (!buildingReserved)
			{
				buildingLocation = TacticalBuildingPlacer::instance().reserveBuildLocation(
                    unitTypeTarget, Broodwar->self()->getStartLocation(), &unit );

				if (buildingLocation != TilePositions::None)
				{
					// TODO: Need to reset this to false eventually
					// TODO: Pass off/cancel reservations on build fails
					buildingReserved = true;
				}
			}
			// Start building
			else if (!unit.isConstructing())
			{
				unit.build(buildingLocation, unitTypeTarget);
			}

			break;
	}

    GroundAgent::update();
}