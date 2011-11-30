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
	/**
		@brief ���{�b�g�̈ʒu��ݒ肷��.
		World�����p����H�H�H
		@sa World
	 */
	//void setPos(int x, int y);
	/**
		@brief Robot��X���W��Blackboard���瓾��
	 */
	//int getPosX();
	/**
		@brief Robot��Y���W��Blackboard���瓾��
	 */
	//int getPosY();
	
protected:
	//internalRadiationMap
	//float internalRadiationMap[FIELD_SIZE][FIELD_SIZE];
	//connectingRobotDirections[Robot��][2]
};

#endif	//_Robot_MAV_H_