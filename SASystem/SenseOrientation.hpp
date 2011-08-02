#ifndef _SenseOrientation_HPP_
#define _SenseOrientation_HPP_

#include "SAModule.h"
#include <iostream>
#include "EnvUpdater.h"

/**
	@class SenseOrientation
	@brief �ʒu�Z���T�̃��W���[��
	���N���b�NEnvUpdater����C��������肵�Csignal�ɕύX����
 */
class SenseOrientation :public SAModule{
public:
	/**
		@fn SenseOrientation()
		@param environment: �����X�V�����́C���ꂩ��C���������擾����
		@brief Constructor.�����o�ϐ�������������
	*/
	SenseOrientation(EnvUpdater* environment);
	/**
		@brief ���������o���C�i�s������0.0�C�E�����𐳂Ƃ��Ċp�x��Encode���ďo�͂���
		@param signal ���͐M���FSenser�ɂ͖����͂��D
		@return �M���o�́F�������G���R�[�h��������
	 */
	float Run(float signal);
	/*
		@brief ������Ԃ�
		@return ���݂̌���
	*/
	double getOrientation();
protected:
	/**
		@brief ���ۂɌ����𑪂��Ă��郂�W���[���D
		EnvUpdater����������擾���C�����ϐ��֑������
	 */
	void updateOrientation();


	/**
		@brief ���݂̕���
		�i�s������0.0�C�E�����𐳂Ƃ���
	*/
	double orientation;
	///��
	EnvUpdater* env;

	/**
		�~����PI
	*/
	const double PI;
};

inline SenseOrientation::SenseOrientation(EnvUpdater* environment):orientation(0.0), env(environment), PI(6.0 * asinf(0.5) ){
}

inline float SenseOrientation::Run(float signal = 0.0){
	updateOrientation();
	orientation = PI / 2.0 - orientation;
	if(orientation < - PI){
		orientation += 2.0 * PI;
	}else if(orientation > PI){
		orientation -= 2.0 * PI;
	}
	return (float)orientation;
}

inline void SenseOrientation::updateOrientation(){
	orientation = env->getOrientation();
	return;
}

inline double SenseOrientation::getOrientation(){
	return orientation;
}

#endif //_SenseOrientation_HPP_