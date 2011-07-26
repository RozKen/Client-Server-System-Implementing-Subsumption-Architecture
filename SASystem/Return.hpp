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
	*/
	Return();

	/**
		@brief 向きを変える信号を出す．
		@param signal 現状では入力信号を考えていない．本当は地球磁気センサー的なのが欲しい
		@return output モーターへの信号
	*/
	float Run(float signal);
};

inline Return::Return(){
}

inline float Return::Run(float signal){
	float output = 0.0f;
	///時計回りに回転する
	float rightSignal = 1.0f;
	float leftSignal = 0.0f;
	

	///両モーターの信号を一つにエンコード
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Return_HPP_