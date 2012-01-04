#ifndef _Cont_Alive_HPP_
#define _Cont_Alive_HPP_

#include "SAModule.h"
#include "Constants.h"
#include <math.h>

/**
	@class ContAlive
	@brief Mission : �o�b�e���[�c�ʂ����Ɉێ����悤�Ƃ��鐧���
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
		���݂�0.2
		@sa BATTERY_LOW
	 */
	float threshold;
};

inline ContAlive::ContAlive(): threshold((float)BATTERY_LOW){
	this->addInput("batLevelCAl");
	this->addInput("posXCAl");
	this->addInput("posYCAl");

	this->addOutput("dXCAl");
	this->addOutput("dXCAl");
}

#endif	//_Cont_Alive_HPP_