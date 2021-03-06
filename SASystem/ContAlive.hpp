#ifndef _Cont_Alive_HPP_
#define _Cont_Alive_HPP_

#include "SAModule.h"
#include "Constants.h"
#include <math.h>

/**
	@class ContAlive
	@brief Mission : バッテリー残量を一定に維持しようとする制御器
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
		InputやOutputなどを追加していく.
	 */
	ContAlive();
	/**
		@brief 実行時の動作.
		batteryLevelが低かったら，出発地点へ戻るよう信号を出す.
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
	/**
		@brief Batteryが足りないと判断するための閾値
		現在は0.2
		@sa BATTERY_LOW
	 */
	float threshold;
};

inline ContAlive::ContAlive(): threshold((float)BATTERY_LOW){
	this->addInput("batLevelCAl");
	this->addInput("posXCAl");
	this->addInput("posYCAl");

	this->addOutput("dXCAl");
	this->addOutput("dYCAl");
}

#endif	//_Cont_Alive_HPP_