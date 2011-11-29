#ifndef _Sense_Battery_HPP_
#define _Sense_Battery_HPP_

#include "SAModule.h"

/**
	@class SenseBattery
	@brief バッテリー残量を検知し，出力する
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class SenseBattery : public SAModule{
public:
	/**
		@brief Default Constructor
		Outputなどを追加していく.
		Sensorなので，Inputはない．
	 */
	SenseBattery();
	/**
		@brief 実行時の動作
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