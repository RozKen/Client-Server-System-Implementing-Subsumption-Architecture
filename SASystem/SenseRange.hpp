#ifndef _SenseRange_HPP_
#define _SenseRange_HPP_

#include "SAModule.h"
#include <iostream>

class SenseRange :public SAModule{
public:
	float Run(float signal);
	double getRange();
protected:
	//���݂̋���
	double range;
};
inline SenseRange(): range(100.0){
}
inline float SenseRange::Run(float signal = 0.0){
	//�Z���T�[�ŋ��������m
	//���v�ł���΁C0.0
	//�����łȂ���Ώ��X�ɒl��1.0�ɋ߂Â��Ă���
	if(range > 25.0){
		signal = 0.0;
	}else{
		signal = 0.5;
		//���݂͎b��I��0.5�ŌŒ�
	}
	return signal;
}

inline int SenseRange::getRange(){
	return range;
}

#endif //_SenseRange_HPP_