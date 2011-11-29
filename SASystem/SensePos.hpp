#ifndef _Sense_Pos_HPP_
#define _Sense_Pos_HPP_

#include "SAModule.h"

/**
	@class SensePos
	@brief ���݈ʒu�����m���C�o�͂���(GPS)
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class SensePos : public SAModule{
public:
	/**
		@brief Default Constructor
		Output�Ȃǂ�ǉ����Ă���.
		Sensor�Ȃ̂ŁCInput�͂Ȃ��D
	 */
	SensePos();
	/**
		@brief ���s���̓���
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline SensePos::SensePos(){
	this->addFBoard("fPosX");
	this->addFBoard("fPosY");
	this->addOutput("posX");
	this->addOutput("posY");
}

inline void SensePos::Run(){
	//Sensor�������
	float posX = this->getFBoard(0);
	float posY = this->getFBoard(1);
	//Sensor�����o��
	this->setOutput(0, posX);
	this->setOutput(1, posY);
}

#endif	//_Sense_Pos_HPP_