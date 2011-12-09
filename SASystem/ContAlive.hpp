#ifndef _Cont_Alive_HPP_
#define _Cont_Alive_HPP_

#include "SAModule.h"
#include "Constants.h"
#include <math.h>

/**
	@class ContAlive
	@brief �o�b�e���[�c�ʂ����Ɉێ����悤�Ƃ��鐧���
	<h1>Inputs</h1>
	<ul>
		<li>Input0: batLevelCAl: current Battery Level</li>
		<li>Input1: posXCAl: current Robot Position - X</li>
		<li>Input2: posYCAl: current Robot Position - Y</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCAl: delta X - differential of Motion X</li>
		<li>Output1: dXCAl: delta Y - differential of Motion Y</li>
	</ul>
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class ContAlive : public SAModule{
public:
	/**
		@brief Default Constructor
		Input��Output�Ȃǂ�ǉ����Ă���.
	 */
	ContAlive();
	/**
		@brief ���s���̓���.
		batteryLevel���Ⴉ������C�o���n�_�֖߂�悤�M�����o��.
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
	/**
		@brief Battery������Ȃ��Ɣ��f���邽�߂�臒l
		���݂�0.3
	 */
	float threshold;
};

inline ContAlive::ContAlive(): threshold(0.3f){
	this->addInput("batLevelCAl");
	this->addInput("posXCAl");
	this->addInput("posYCAl");

	this->addOutput("dXCAl");
	this->addOutput("dXCAl");
}

inline void ContAlive::Run(){
	float batLevel = this->getInput(0);
	float signalX, signalY;
	if(batLevel / ((float)MAX_BAT) < threshold){
		float posX = this->getInput(1);
		float posY = this->getInput(2);
		float deltaX = START_X - posX;
		float deltaY = START_Y - posY;
		float norm = this->norm(deltaX, deltaY);
		signalX = MAX_DRIVE * deltaX / norm;
		signalY = MAX_DRIVE * deltaY / norm;
	}else{
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

#endif	//_Cont_Alive_HPP_