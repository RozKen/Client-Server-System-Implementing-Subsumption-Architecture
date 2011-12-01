#ifndef _Robot_MAV_H_
#define _Robot_MAV_H_

#include "Constants.h"
#include "Sensors.h"
#include "Controllers.h"
#include "Actuators.h"
#include "Robot.h"

class RobotMAV : public Robot{
public:
	/**
		@brief Default Constructor
		Module‚ğ’Ç‰Á‚µ‚Ä‚¢‚­D
	 */
	RobotMAV();
	RobotMAV(std::string directoryPath, std::string fileName);

	/**
		@brief Às‚Ì“®ì
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
};

#endif	//_Robot_MAV_H_