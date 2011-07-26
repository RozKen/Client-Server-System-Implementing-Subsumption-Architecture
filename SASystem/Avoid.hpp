#ifndef _Avoid_HPP_
#define _Avoid_HPP_

#include "SAModule.h"

/**
	@class Avoid
	@brief 物体を避ける機能をつかさどるモジュール
*/
class Avoid : public SAModule{
public:
	/**
		@brief Constructor
	*/
	Avoid();

	/**
		@brief RangeSensorから受け取った信号を基に，モーターへの回避命令を出す．
		デフォルトでは，直進する
		@param signal RangeSensorからの信号
		@return output モーターへの信号
	*/
	float Run(float signal);
};

inline Avoid::Avoid(){
}

inline float Avoid::Run(float signal){
	float output = 0.0f;
	///基本的に直進する
	float rightSignal = 1.0f;
	float leftSignal = 1.0f;

	if(signal >= 0.5){	///近づきすぎの時．右に回転する
		rightSignal = 1.0f;
		leftSignal = 0.0f;
	}

	///両モーターの信号を一つにエンコード
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Avoid_HPP_