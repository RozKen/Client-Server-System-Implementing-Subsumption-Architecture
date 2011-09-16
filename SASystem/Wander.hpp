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
		outputs[0] : 左のモータードライバー
		outputs[1] : 右のモータードライバー
	*/
	Wander();

	/**
		@brief うろ　つく信号を出す.
	*/
	void Run();
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

inline Wander::Wander(): SAModule(0,2) {
	ss = new StochasticSelector(0.1);
	random = new Random<boost::uniform_real<> >(0, 1);
}

inline void Wander::Run(){
	///9割の確率で直進する
	float leftSignal = 1.0f;
	float rightSignal = 1.0f;
	if( ss->get() ){	///残りの1割の確率で，ランダムに動く
		leftSignal = random->operator()();
		rightSignal = random->operator()();
	}

	///両モーターの信号を一つにエンコード
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Wander_HPP_