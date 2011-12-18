#ifndef _Sense_Battery_Charger_HPP_
#define	_Sense_Battery_Charger_HPP_

#include "SAModule.h"

/**
	@class SenseBatteryCharger
		@brief 自分の位置がBattery Chargerのある場所かどうかを与える
	<h1>Inputs</h1>
	No Inputs
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : onBattery : 1.0 = true, 0.0 = false</li>
	</ul>
	<h1>IBoard</h1>
	<ul>
		<li>iBoard0 : iOnBattery : 1 = true, 0 = false</li>
	</ul>
	@author Kenichi Yorozu
	@date 18th December 2011
	@sa SAModule
 */
class SenseBatteryCharger : public SAModule{
public:
	/**
		@brief Default Constructor
		Outputなどを追加していく．
		Sensorなので，Inputはない
	 */
	SenseBatteryCharger();
	/**
		@brief 実行時の動作
		Sensing結果を出力
		@sa SAModule::Run
	 */
	virtual void Run();
};

inline SenseBatteryCharger::SenseBatteryCharger(){
	this->addOutput("onBattery");
	this->addIBoard("iOnBattery");
}

inline void SenseBatteryCharger::Run(){
	int value = this->getIBoard(0);
	this->setOutput(0, (float)value);
}
#endif	//_Sense_Battery_Charger_HPP_