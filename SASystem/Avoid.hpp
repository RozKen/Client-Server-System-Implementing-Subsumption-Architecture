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
		デフォルトでは，信号を出さない( NO_SIGNAL ).
		回避は，phaseに応じて，異なる信号を出すことによって，ロボットの向きを
		変えることで実施される
	*/
	void Run();
protected:
	///衝突回避におけるフェーズ
	int phase;
};

inline Avoid::Avoid() : SAModule(1, 2), phase(0){
}

inline void Avoid::Run(){
	float output = 0.0f;
	///基本的に信号を出さない
	float rightSignal = NO_SIGNAL;
	float leftSignal = NO_SIGNAL;
	phase = 0;
	if(inputs[0] >= 0.5){	///近づきすぎの時．左に回転する
		switch(phase){
		case 0:
		case 1:
			rightSignal = 0.9f;
			leftSignal = 0.5f;
			phase++;
			break;
		case 2:
			rightSignal = 0.9f;
			leftSignal = 0.5f;
			phase++;
			break;
		case 15:
			rightSignal = 0.9f;
			leftSignal = 0.9f;
			phase = 0;
			break;
		default:
			rightSignal = 0.9f;
			leftSignal = 0.9f;
			phase++;
		}
	}

	///両モーターの信号をアウトプットへ出力
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Avoid_HPP_