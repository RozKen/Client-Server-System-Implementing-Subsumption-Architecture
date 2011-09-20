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
		inputs[0] : RangeSensorからの入力
		outputs[0] : 左のモータードライバー
		outputs[1] : 右のモータードライバー
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
	///基本的に信号を出さない
	float leftSignal = NO_SIGNAL;
	float rightSignal = NO_SIGNAL;
	phase = 0;
	if(inputs[0] >= 0.5){	///近づきすぎの時．左に回転する
		switch(phase){
		case 0:
		case 1:
			leftSignal = 0.0f;
			rightSignal = 0.8f;
			phase++;
			break;
		case 2:
			leftSignal = 0.0f;
			rightSignal = 0.8f;
			phase++;
			break;
		case 15:
			leftSignal = 1.0f;
			rightSignal = 1.0f;
			phase = 0;
			break;
		default:
			leftSignal = 1.0f;
			rightSignal = 1.0f;
			phase++;
		}
	}

	///両モーターの信号をアウトプットへ出力
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Avoid_HPP_