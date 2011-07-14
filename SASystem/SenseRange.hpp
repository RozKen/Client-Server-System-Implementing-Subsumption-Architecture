#ifndef _SenseRange_HPP_
#define _SenseRange_HPP_

#include "SAModule.h"
#include <iostream>

class SenseRange :public SAModule{
public:
	float Run(float signal);
	double getRange();
protected:
	//現在の距離
	double range;
};
inline SenseRange(): range(100.0){
}
inline float SenseRange::Run(float signal = 0.0){
	//センサーで距離を感知
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
	return range;
}

#endif //_SenseRange_HPP_