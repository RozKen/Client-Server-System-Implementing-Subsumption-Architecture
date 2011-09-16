#ifndef _SenseRange_HPP_
#define _SenseRange_HPP_

#include "SAModule.h"
#include <iostream>
#include "EnvUpdater.h"

/**
	@class SenseRange
	@brief �����Z���T�[�̃��W���[��
	���N���b�N�����𑪂�C�댯�ł���΁C0.0�ȊO�̒l���o�͂���
 */
class SenseRange :public SAModule{
public:
	/**
		@fn SenseRange()
		@brief Constructor.�����o�ϐ�������������
		outputs[0] : �ł��߂����̂Ƃ̋���
	*/
	SenseRange(EnvUpdater* environment);
	/**
		@brief �����𑪂�C���S�͈͂𒴂���ƁC0.0�ȊO�̒l���o�͂���
	 */
	void Run();
protected:
	/**
		@brief ���ۂɋ����𑪂��Ă��郂�W���[���D
		�������F�Ȃɂ�����ߖT�̕��̂Ƃ̋����𑪂��@����������K�v������
		@return �ł��߂����̂Ƃ̋���
	 */
	double getRange();
	///���݂̋���
	double range;
	///��
	EnvUpdater* env;

};

inline SenseRange::SenseRange(EnvUpdater* environment): SAModule(0, 1), range(100.0), env(environment){
}

inline void SenseRange::Run(){
	float signal;
	//�Z���T�[�ŋ��������m
	getRange();
	//���v�ł���΁C0.0
	//�����łȂ���Ώ��X�ɒl��1.0�ɋ߂Â��Ă���
	if(range > 60.0){
		signal = 0.0;
	}else{
		signal = 0.6;
		//TODO ���݂͎b��I��0.5�ŌŒ�
	}

	outputs[0] = signal;
	return;
}

inline double SenseRange::getRange(){
	range = env->getRange();
	return range;
}

#endif //_SenseRange_HPP_