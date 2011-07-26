#ifndef _Wander_HPP_
#define _Wander_HPP_

#include "SAModule.h"
#include "StochasticSelecter.hpp"

/**
	@class Wander
	@brief 周辺をうろつく機能をつかさどるモジュール
*/
class Wander : public SAModule{
public:
	/**
		@brief Constructor
	*/
	Wander();

	/**
		@brief うろつく信号を出す
		@param signal 現状では入力信号を考えていない
		@return output モーターへの信号
	*/
	float Run(float signal);
};

inline Wander::Wander(){
}

inline float Wander::Run(float signal){
	float output = 0.0f;
	///9割の確率で直進する
	float rightSignal = 1.0f;
	float leftSignal = 1.0f;
	StochasticSelector ss(0.9);
	if( !ss() ){	///残りの1割の確率で，ランダムに動く
		Random<boost::uniform_real<> > random(0, 1);
		rightSignal = random();
		leftSignal = random();
	}

	///両モーターの信号を一つにエンコード
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Wander_HPP_