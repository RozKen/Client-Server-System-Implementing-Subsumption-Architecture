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
		Module��ǉ����Ă����D
	 */
	RobotMAV();

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
};

inline RobotMAV::RobotMAV(){
	//�ʒu�Z���T�Ƃ���Ɋւ�鍀�ڂ�ǉ�
	this->addModule(new SensePos());

	//�ʒuActuator�Ƃ���Ɋւ�鍀�ڂ�ǉ�
	this->addModule(new ActPos());
}

inline void RobotMAV::Run(){
	//Robot�ւ�Input����������
	ProcessInputs();
	//Robot�̊eModule�𓮂���
	RunModules();
	//Robot�����Output����������
	ProcessOutputs();
	//Log�����
	Log();
}

#endif	//_Robot_MAV_HPP_