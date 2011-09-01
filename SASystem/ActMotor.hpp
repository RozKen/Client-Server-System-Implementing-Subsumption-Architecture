#ifndef _ActMotor_HPP_
#define _ActMotor_HPP_

#include "SAModule.h"
#include <iostream>
#define RPM_MAX	10000
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
	float Run(float signal);
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

inline ActMotor::ActMotor(): rpm(0), speed(0.0){
}

inline float ActMotor::Run(float signal){
	//rpmを更新
	this->rpm = (int)((signal - 0.5f) * 2.0 *(float)RPM_MAX);
	//speedを更新
	this->speed = 2.0f * (signal - 0.5f);
	return signal;
}

inline int ActMotor::getRPM(){
	return this->rpm;
}

inline float ActMotor::getSpeed(){
	return this->speed;
}

#endif //_ActMotor_HPP_