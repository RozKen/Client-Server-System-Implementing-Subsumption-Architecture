#ifndef _Return_HPP_
#define _Return_HPP_

#include "SAModule.h"
#include "StochasticSelecter.hpp"

/**
	@class Return
	@brief 向きを変える機能をつかさどるモジュール
*/
class Return : public SAModule{
public:
	/**
		@brief Constructor
		outputs[0] : 左のモータードライバー
		outputs[1] : 右のモータードライバー
	*/
	Return();

	/**
		@brief 向きを変える信号を出す．
	*/
	void Run();
};

inline Return::Return(): SAModule(0, 2){
}

inline void Return::Run(){
	///時計回りに回転する
	float leftSignal = 1.0f;
	float rightSignal = 0.0f;

	///両モーターの信号を一つにエンコード
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Return_HPP_