#include "World/EnergyItem.h"

#include "RoboroboMain/roborobo.h"
#include "Utilities/Misc.h"
#include "World/World.h"
#include "SelfAssembly/WorldModels/GroupRobotWorldModel.h"
#include <iomanip>

EnergyItem::EnergyItem( int __id ) :CircleObject( __id ) // should only be called by PhysicalObjectFactory
{
    setType(1);
    std::string s = "";
	std::stringstream out;
	out << getId();

    s = "physicalObject[";
	s += out.str();
	s += "].energy";
	if ( gProperties.hasProperty( s ) )
		convertFromString<double>(maxEnergyLevel, gProperties.getProperty( s ), std::dec);
	else
    {
        if ( gVerbose )
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem) missing default energy initial level (integer, >=0). Assume default (" << gEnergyItemDefaultInit << ").\n";
        maxEnergyLevel = gEnergyItemDefaultInit;
    }
    
    s = "physicalObject[";
	s += out.str();
	s += "].energyMode";
	if ( gProperties.hasProperty( s ) )
		convertFromString<int>(energyMode, gProperties.getProperty( s ), std::dec);
	else
    {
        if ( gVerbose )
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem) missing default energy mode (integer, >=0). Assume default (" << gEnergyItemDefaultMode << ").\n";
        energyMode = gEnergyItemDefaultMode;
    }

}

void EnergyItem::step()
{
    stepPhysicalObject();
}

void EnergyItem::isTouched( int __idAgent )
{
//    if ( gVerbose && gDisplayMode <= 1)
//        std::cout << "[DEBUG] Physical object #" << this->getId() << " (energy item) touched by robot #" << __idAgent << std::endl;
}
void EnergyItem::isWalked( int __idAgent )
{
//    if ( gVerbose && gDisplayMode <= 1)
//        std::cout << "[DEBUG] Physical object #" << this->getId() << " (energy item) walked upon by robot #" << __idAgent << std::endl;

    Robot* robot = gWorld->getRobot(__idAgent);
    if(robot->getIsPredator())
        return;

    if(_visible == false)
        return;

    double energyRequestedValueByRobot;
    double energyProvided;
    switch ( energyMode )
    {
        case 0: // give all
            giveEnergy(__idAgent, maxEnergyLevel);
            regrowTime = regrowTimeMax; // time to regrow is proportionate to energy taken
            break;
            
        case 1: // give what is asked, fixed respawn delay
            energyRequestedValueByRobot = gWorld->getRobot(__idAgent)->getWorldModel()->getEnergyRequestValue(); // in [0,1[ (guaranteed)
            energyProvided = energyRequestedValueByRobot * maxEnergyLevel;
            giveEnergy(__idAgent, energyProvided);
            assert ( energyProvided >= 0 );
            regrowTime = regrowTimeMax;
            break;
            
        case 2: // give what is asked, remaining sets respawn delay
            energyRequestedValueByRobot = gWorld->getRobot(__idAgent)->getWorldModel()->getEnergyRequestValue(); // in [0,1[ (guaranteed)
            energyProvided = energyRequestedValueByRobot * maxEnergyLevel;
            giveEnergy(__idAgent, energyProvided);
            assert ( energyProvided >= 0 );
            regrowTime = (int)( (double)regrowTimeMax * ( energyProvided/maxEnergyLevel ) ); // time to regrow is proportionate to energy taken
            break;

        case 3: // give nothing
            break;
    }

    regrow = true;

    unregisterObject();
    hide();
    _visible = false;
}

#include "SelfAssemblyMechanisms/include/Logger/StatisticsLogger.h"

void EnergyItem::giveEnergy(int agentId, double amount)
{
    auto robot = gWorld->getRobot(agentId);
    auto wm = (GroupRobotWorldModel*)robot->getWorldModel();
    StatisticsLogger* logger = StatisticsLogger::getInstance();
    if(wm->getGroup()->size() > 1){
        logger->logGroupConsumedEnergy();
    }
    else
        logger->logRobotConsumedEnergy();

    for(auto it = wm->getGroup()->begin(); it != wm->getGroup()->end(); it++)
    {
        auto member = it->second;
        member->addEnergy(amount/wm->getGroup()->size());
    }
}

