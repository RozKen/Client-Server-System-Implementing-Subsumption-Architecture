#ifndef _Robot_MAV_HPP_
#define _Robot_MAV_HPP_

#include "Robot.h"
#include "Sensors.h"
#include "Controllers.h"
#include "Actuators.h"

class RobotMAV : public Robot{

public:
	/**
		@brief Default Constructor
		Moduleを追加していく．
	 */
	RobotMAV();

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
};

inline RobotMAV::RobotMAV(){
	//位置センサとそれに関わる項目を追加
	this->addModule(new SensePos());

	//位置Actuatorとそれに関わる項目を追加
	this->addModule(new ActPos());
}

inline void RobotMAV::Run(){
	//RobotへのInputを処理する
	ProcessInputs();
	//Robotの各Moduleを動かす
	RunModules();
	//RobotからのOutputを処理する
	ProcessOutputs();
	//Logを取る
	Log();
}

#endif	//_Robot_MAV_HPP_