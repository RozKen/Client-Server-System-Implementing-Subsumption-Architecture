#ifndef _MotorDriver_HPP_
#define _MotorDriver_HPP_

#include "SAModule.h"

/**
	@class MotorDriver
	@brief Subsumption Architectureの回路内信号を，
	モーターへの指令信号PWMへ変更するモジュール
	@author Kenichi Yorozu
	@date 14th July 2011
	@sa SAModule
 */
class MotorDriver : public SAModule{
public:
	/**
		@brief Constructor.
		@param left trueなら左用．falseなら右用
	 */
	MotorDriver(bool left);
	/**
		@brief 入力信号をエンコードして，対応するPWMを出力する．
		<ol>
			<li>入力信号のエンコード：SignalDecoder</li>
			<li>PWM信号を取得：GeneratePWM</li>
		</ol>
		@param signal 入力信号
		@return PWM信号
		@sa SignalDecoder
		@sa GeneratePWM
	 */
	float Run(float signal);
protected:
	/**
		@brief 入力信号の値0.0 - 1.0を有効なPWM信号帯へMappingする
		@param signal 入力信号
		@return PWM信号：現状ではPWMではなくて，0.0 - 1.0で，ただのSA回路内信号と同じ
	 */
	float GeneratePWM(float signal);
	/**@brief 左用のMotor Driverであるなら，true/右用ならfalse.その他は想定外*/
	bool left;
};

MotorDriver::MotorDriver(bool left): left(left){
}

float MotorDriver::Run(float signal){
	//左用信号
	float leftSignal;
	//右用信号
	float rightSignal;
	//信号の解読
	SignalDecoder(signal, leftSignal, rightSignal);
	//出力信号
	float output;

	if(left == true){
		output = leftSignal;
	}else{
		output = rightSignal;
	}
	//PWM信号の取得
	output = GeneratePWM(output);
	return output;
}

float GeneratePWM(float signal){
	//TODO PWMへのMappingを行うが，現在は0.0 - 1.0のまま
	return signal;
}
#endif //_MotorDriver_HPP_