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
	/**
		@brief 直進するか，ランダムに動くかを，一定の確率で選択する
		@sa StochasitcSelector
	*/
	StochasticSelector* ss;
	/**
		@brief ランダムな動きを生成するのに用いる
		@sa Random
	*/
	Random<boost::uniform_real<> >* random;
};

inline Wander::Wander(){
	ss = new StochasticSelector(0.1);
	random = new Random<boost::uniform_real<> >(0, 1);
}

inline float Wander::Run(float signal){
	float output = 0.0f;
	///9割の確率で直進する
	float rightSignal = 1.0f;
	float leftSignal = 1.0f;
	if( ss->get() ){	///残りの1割の確率で，ランダムに動く
		rightSignal = random->operator()();
		leftSignal = random->operator()();
	}

	///両モーターの信号を一つにエンコード
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Wander_HPP_