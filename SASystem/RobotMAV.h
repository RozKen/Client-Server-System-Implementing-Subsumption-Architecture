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
		Moduleを追加していく．
	 */
	RobotMAV();
	RobotMAV(std::string directoryPath, std::string fileName);

	/**
		@brief 実行時の動作
		@sa SAModule::Run()
	 */
	virtual void Run();
	/**
		@brief ロボットの位置を設定する.
		Worldが利用する？？？
		@sa World
	 */
	//void setPos(int x, int y);
	/**
		@brief RobotのX座標をBlackboardから得る
	 */
	//int getPosX();
	/**
		@brief RobotのY座標をBlackboardから得る
	 */
	//int getPosY();
	
protected:
	//internalRadiationMap
	//float internalRadiationMap[FIELD_SIZE][FIELD_SIZE];
	//connectingRobotDirections[Robot数][2]
};

#endif	//_Robot_MAV_H_