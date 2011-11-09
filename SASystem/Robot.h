#ifndef _Robot_H_
#define _Robot_H_

#include "SAModule.h"
#include "Blackboard.h"

/**
	@class Robot
	@brief ロボット一体の動きを制御するモジュール.
	以前のSAServerに近い役割をするが，Blackboard Systemを実装してある

	inputs: sensorへの入力
	outputs: actuatorによる出力
	@sa SAModule
 */
class Robot : public SAModule{
public:
	/**
		@brief Constructor
	 */
	Robot();

	/**
		@brief Mission: Operate a Robot
	 */
	void Run();
protected:
	Blackboard* memory;
};

inline Robot::Robot(){
	memory = new Blackboard();
}

#endif _Robot_H_