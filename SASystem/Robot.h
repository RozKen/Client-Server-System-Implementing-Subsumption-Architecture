#ifndef _Robot_H_
#define _Robot_H_

#include "SAModule.h"
#include "Blackboard.h"

/**
	@class Robot
	@brief ���{�b�g��̂̓����𐧌䂷�郂�W���[��.
	�ȑO��SAServer�ɋ߂����������邪�CBlackboard System���������Ă���

	inputs: sensor�ւ̓���
	outputs: actuator�ɂ��o��
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