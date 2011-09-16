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
		inputs[0] : 入力信号
		output[0] : モーターへ送るPWM信号
	 */
	MotorDriver();
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
	void Run();
protected:
	/**
		@brief 入力信号の値を有効なPWM信号帯へMappingする
		@param signal 入力信号
		@return PWM信号：現状ではPWMではなくて，入力信号そのままで，ただのSA回路内信号と同じ
	 */
	float GeneratePWM(float signal);
};

inline MotorDriver::MotorDriver(): SAModule(1, 1){
}

inline void MotorDriver::Run(){
	//PWM信号の取得
	outputs[0] = GeneratePWM(inputs[0]);
	return;
}

inline float MotorDriver::GeneratePWM(float signal){
	//TODO PWMへのMappingを行うが，現在は0.0 - 1.0のまま
	if(signal == NO_SIGNAL){
		signal == NO_SIGNAL;
	}
	return signal;
}
#endif //_MotorDriver_HPP_