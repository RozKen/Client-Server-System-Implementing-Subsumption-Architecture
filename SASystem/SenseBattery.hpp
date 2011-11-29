#ifndef _Sense_Battery_HPP_
#define _Sense_Battery_HPP_

#include "SAModule.h"

/**
	@class SenseBattery
	@brief �o�b�e���[�c�ʂ����m���C�o�͂���
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class SenseBattery : public SAModule{
public:
	/**
		@brief Default Constructor
		Output�Ȃǂ�ǉ����Ă���.
		Sensor�Ȃ̂ŁCInput�͂Ȃ��D
	 */
	SenseBattery();
	/**
		@brief ���s���̓���
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline SenseBattery::SenseBattery(){
	this->addFBoard("fBattery");
	this->addOutput("battery");
}
inline SenseBattery::Run(){
	float batteryLevel = this->getFBoard(0);
#ifdef _DEBUG
	std::cout << "batteryLevel: " << batteryLevel << std::endl;
#endif //_DEBUG
	this->setOutput(0, batteryLevel);
}

#endif	//_Sense_Battery_HPP_