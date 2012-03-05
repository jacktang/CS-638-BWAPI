/*
 *  Strategizer.cpp
 */
#include "Strategizer.h"
#include "BWAPI.h"

using namespace BWAPI;
using namespace std;

void Strategizer::update()
{
	Broodwar->sendText("Hello!");
 
	set<Unit*> units = Broodwar->self()->getUnits();
	set<Unit*>::iterator i;

	::Broodwar->sendText("Units include: ");
	for (i = units.begin(); i != units.end(); i++)
	{
		Broodwar->sendText("%s", (*i)->getType().getName().c_str());
		SCVAgent a(*(*i));
	}
}

void Strategizer::onEvent(JohnConnorBot::Event &e)
{
}


