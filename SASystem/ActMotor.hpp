#ifndef _ActMotor_HPP_
#define _ActMotor_HPP_

#include "SAModule.h"
#include <iostream>
#define RPM_MAX	10000
#define SPEED_MAX 3.0f
/**
	@class ActMotor
	@brief ActMotorDriverからのPWMを受けて，実際に移動速度を更新するモジュール
	各モーターの移動速度を用いて，最終的に位置を決定する．
*/
class ActMotor :public SAModule{
public:
	/**
		@fn ActMotor();
		@brief Constructor.パラメータを初期化する．
	*/
	ActMotor();
	/**
		@fn Run(float signal)
		@brief PWM信号をうけて，位置を更新する
		@param signal PWM信号
		@return PWM信号をそのまま出力
	*/
	//float Run(float signal);

	/**
		@brief PWM信号に応じて，速度を変化させる
	 */
	void Run();

	/**
		@fn getRPM()
		@brief 現在の回転数(Rotation per Minute)を取得
		@return 現在の回転数 [RPM]
	*/
	int getRPM();
	/**
		@fn getSpeed()
		@brief 現在のスピードを取得
		@return 現在のスピード
	*/
	float getSpeed();
protected:
	/**
		@brief 現在の回転数
		(int)((signal - 0.5f) * (float)INT_MAX)
	*/
	int rpm;
	/**
		@brief 現在のスピード
		1.0f * (signal - 0.5f)
	*/
	float speed;
};

inline ActMotor::ActMotor(): SAModule(1, 0), rpm(0), speed(0.0){
}

inline void ActMotor::Run(){
	//rpmを更新
	this->rpm = (int)((inputs[0] - 0.5f) * 2.0 *(float)RPM_MAX);
	
	//speedを更新
	this->speed = (float)this->rpm / (float)RPM_MAX * SPEED_MAX;
	
	return;
}

inline int ActMotor::getRPM(){
	return this->rpm;
}

inline float ActMotor::getSpeed(){
	return this->speed;
}

#endif //_ActMotor_HPP_