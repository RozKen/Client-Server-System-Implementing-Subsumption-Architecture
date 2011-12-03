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
		Module��ǉ����Ă����D
	 */
	RobotMAV();
	RobotMAV(std::string directoryPath, std::string fileName);

	/**
		@brief ���s���̓���
		@sa SAModule::Run()
	 */
	virtual void Run();
	float getBattery() const;
	void setBattery(float value);
	float getPosX() const;
	void setPosX(float value);
	float getPosY() const;
	void setPosY(float value);
protected:
};

#endif	//_Robot_MAV_H_