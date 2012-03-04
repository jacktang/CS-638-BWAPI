#include <BWAPI.h>
#include <BWTA.h>
#include <Strategizer.h>
#include "BasicAIModule.h"

void BasicAIModule::onStart()
{
  BWAPI::Broodwar->sendText("Hello, CS638!");
}
void BasicAIModule::onEnd(bool isWinner)
{
}
void BasicAIModule::onFrame()
{
	std::set<BWAPI::Unit*> units = BWAPI::Broodwar->self()->getUnits();
	std::set<BWAPI::Unit*> minerals = BWAPI::Broodwar->getMinerals();

	for (std::set<BWAPI::Unit*>::iterator i = units.begin(); i != units.end(); i++)
	{
		BWAPI::Unit *u = *i;

		// Find a worker
		if (u->getType().isWorker() && u->isIdle()) 
		{
			BWAPI::Unit *closest = NULL;
			int closestDist = 9999999;
			for (std::set<BWAPI::Unit*>::iterator j = minerals.begin(); j != minerals.end(); j++)
			{
				BWAPI::Unit *m = *j;
				int dist = u->getDistance(m);
				if (dist < closestDist)
				{
					closest = m;
					closestDist = dist;
				}
			}
			if (closest != NULL)
				u->gather(closest);
		}
	}	
}

void BasicAIModule::onUnitDiscover(BWAPI::Unit* unit)
{
  BWAPI::Broodwar->sendText("Unit discovered: %s", unit->getType().getName());
}

void BasicAIModule::onUnitEvade(BWAPI::Unit* unit)
{
}

void BasicAIModule::onUnitMorph(BWAPI::Unit* unit)
{
}

void BasicAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
}

void BasicAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
}

void BasicAIModule::onSendText(std::string text)
{
}

void BasicAIModule::showPlayers()
{
}

void BasicAIModule::showForces()
{
}

    