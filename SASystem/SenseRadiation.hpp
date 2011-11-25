#ifndef _Sense_Radiation_HPP_
#define _Sense_Radiation_HPP_

#include "SAModule.h"
#include "World.h"
#include "MAV_Robot.hpp"

class SenseRadiation : public SAModule{
public:
	SenseRadiation();

	virtual void Run();
};

inline SenseRadiation::SenseRadiation(){
	for(int i = 0; i < MAX_AREA; i++){
		addOutput("radiation[" + intToString(i) + "]");
	}
}

inline void SenseRadiation::Run(){
	//World* world = ;
	std::vector<float>* radMap = ((World *) (this->getParent()->getParent()))->getRadiationMap(
		(MAV_Robot *)(this->getParent())->getPosX(), (MAV_Robot *)(this->getParent())->getPosY());
	for(int i = 0; i < MAX_AREA; i++){
		setOutput(i, radMap->at(i));
	}
}

#endif	//_Sense_Radiation_HPP_