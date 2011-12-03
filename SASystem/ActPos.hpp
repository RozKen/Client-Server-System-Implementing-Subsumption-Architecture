#ifndef _Act_Pos_HPP_
#define _Act_Pos_HPP_

#include "SAModule.h"
#include <iostream>
/**
	@class ActPos
	@brief Robot�̈ʒu���ړ�������D�o�͂͌��݂���̑��΋���
	@author Kenichi Yorozu
	@date 25th November 2011
 */
class ActPos : public SAModule{
public:
	/**
		@brief Default Constructor
		Input�Ȃǂ�ǉ����Ă���.
		Actuator�Ȃ̂ŁCOutput�͂Ȃ��D
	 */
	ActPos();
	/**
		@brief ���s���̓���
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline ActPos::ActPos(){
	this->addInput("controlX");
	this->addInput("controlY");
	this->addFBoard("fDeltaX");
	this->addFBoard("fDeltaY");
}

inline void ActPos::Run(){
	//�M�������
	float dX = this->getInput(0);
	float dY = this->getInput(1);
#ifdef _DEBUG
	//std::cout << "getInput0: " << this->getInput(0) << ": dX : " << dX << std::endl;
	//std::cout << "getInput1: " << this->getInput(1) << ": dY : " << dY << std::endl;
#endif //_DEBUG
	//Robot�̓����ɏo�͐M�����i�[
	this->setFBoard(0, dX);
	this->setFBoard(1, dY);
}

#endif	//_Act_Pos_HPP_