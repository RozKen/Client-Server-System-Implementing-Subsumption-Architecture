#ifndef _SensePosition_HPP_
#define _SensePosition_HPP_

#include "SAModule.h"
#include <iostream>
#include "EnvUpdater.h"

/**
	@class SensePosition
	@brief �ʒu�Z���T�̃��W���[��
	���N���b�NEnvUpdater����C�ʒu����肵�Csignal�ɕύX����
 */
class SensePosition :public SAModule{
public:
	/**
		@fn SensePosition()
		@param environment: �����X�V�����́C���ꂩ��C�ʒu�����擾����
		@brief Constructor.�����o�ϐ�������������
		outputs[0] : position[0] : x-pos
		outputs[1] : position[1] : y-pos
	*/
	SensePosition(EnvUpdater* environment);
	/**
		@brief �ʒu�����o���C2�������W��Encode���ďo�͂���
	 */
	void Run();
	/*
		@brief X���W��Ԃ�
		@return ���݂�X���W
	*/
	double getPositionX();
	/*
		@brief Y���W��Ԃ�
		@return ���݂�X���W
	*/
	double getPositionY();
protected:
	/**
		@brief ���ۂɈʒu�𑪂��Ă��郂�W���[���D
		EnvUpdater����ʒu���擾���C�����ϐ��֑������
	 */
	void updatePosition();

	///���݂̋���
	double position[2];
	///��
	EnvUpdater* env;
};

inline SensePosition::SensePosition(EnvUpdater* environment): SAModule(0, 2), env(environment){
	position[0] = 0.0;
	position[1] = 0.0;
}

inline void SensePosition::Run(){
	updatePosition();
	outputs[0] = position[0];
	outputs[1] = position[1];
	return;
}

inline void SensePosition::updatePosition(){
	position[0] = env->getPositionX();
	position[1] = env->getPositionY();
	return;
}

inline double SensePosition::getPositionX(){
	return position[0];
}

inline double SensePosition::getPositionY(){
	return position[1];
}

#endif //_SensePosition_HPP_