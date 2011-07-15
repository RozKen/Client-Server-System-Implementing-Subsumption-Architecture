#ifndef _SenseRange_HPP_
#define _SenseRange_HPP_

#include "SAModule.h"
#include <iostream>

/**
	�����Z���T�[�̃��W���[��
	���N���b�N�����𑪂�C�댯�ł���΁C0.0�ȊO�̒l���o�͂���
 */
class SenseRange :public SAModule{
public:
	/**
		�����𑪂�C���S�͈͂𒴂���ƁC0.0�ȊO�̒l���o�͂���
		@param signal ���͐M��
		@return �M���o��
	 */
	float Run(float signal);
protected:
	/**
		���ۂɋ����𑪂��Ă��郂�W���[���D
		�������F�Ȃɂ�����ߖT�̕��̂Ƃ̋����𑪂��@����������K�v������
		@return �ł��߂����̂Ƃ̋���
	 */
	double getRange();
	///���݂̋���
	double range;
};

inline SenseRange(): range(100.0){
}

inline float SenseRange::Run(float signal = 0.0){
	//�Z���T�[�ŋ��������m
	getRange();
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
	//TODO �Ȃɂ�����ߖT�̕��̂Ƃ̋����𑪂��@����������K�v������
	return range;
}

#endif //_SenseRange_HPP_