#ifndef _SenseRange_HPP_
#define _SenseRange_HPP_

#include "SAModule.h"
#include <iostream>

/**
	距離センサーのモジュール
	毎クロック距離を測り，危険であれば，0.0以外の値を出力する
 */
class SenseRange :public SAModule{
public:
	/**
		距離を測り，安全範囲を超えると，0.0以外の値を出力する
		@param signal 入力信号
		@return 信号出力
	 */
	float Run(float signal);
protected:
	/**
		実際に距離を測っているモジュール．
		未実装：なにかしら近傍の物体との距離を測る手法を実装する必要がある
		@return 最も近い物体との距離
	 */
	double getRange();
	///現在の距離
	double range;
};

inline SenseRange(): range(100.0){
}

inline float SenseRange::Run(float signal = 0.0){
	//センサーで距離を感知
	getRange();
	//大丈夫であれば，0.0
	//そうでなければ徐々に値を1.0に近づけていく
	if(range > 25.0){
		signal = 0.0;
	}else{
		signal = 0.5;
		//現在は暫定的に0.5で固定
	}
	return signal;
}

inline int SenseRange::getRange(){
	//TODO なにかしら近傍の物体との距離を測る手法を実装する必要がある
	return range;
}

#endif //_SenseRange_HPP_