#ifndef _ActMotor_HPP_
#define _ActMotor_HPP_

#include "SAModule.h"
#include <iostream>
#define RPM_MAX	10000
#define SPEED_MAX 3.0f
/**
	@class ActMotor
	@brief ActMotorDriver�����PWM���󂯂āC���ۂɈړ����x���X�V���郂�W���[��
	�e���[�^�[�̈ړ����x��p���āC�ŏI�I�Ɉʒu�����肷��D
*/
class ActMotor :public SAModule{
public:
	/**
		@fn ActMotor();
		@brief Constructor.�p�����[�^������������D
	*/
	ActMotor();
	/**
		@fn Run(float signal)
		@brief PWM�M���������āC�ʒu���X�V����
		@param signal PWM�M��
		@return PWM�M�������̂܂܏o��
	*/
	//float Run(float signal);

	/**
		@brief PWM�M���ɉ����āC���x��ω�������
	 */
	void Run();

	/**
		@fn getRPM()
		@brief ���݂̉�]��(Rotation per Minute)���擾
		@return ���݂̉�]�� [RPM]
	*/
	int getRPM();
	/**
		@fn getSpeed()
		@brief ���݂̃X�s�[�h���擾
		@return ���݂̃X�s�[�h
	*/
	float getSpeed();
protected:
	/**
		@brief ���݂̉�]��
		(int)((signal - 0.5f) * (float)INT_MAX)
	*/
	int rpm;
	/**
		@brief ���݂̃X�s�[�h
		1.0f * (signal - 0.5f)
	*/
	float speed;
};

inline ActMotor::ActMotor(): SAModule(1, 0), rpm(0), speed(0.0){
}

inline void ActMotor::Run(){
	//rpm���X�V
	this->rpm = (int)((inputs[0] - 0.5f) * 2.0 *(float)RPM_MAX);
	
	//speed���X�V
	this->speed = (float)this->rpm / (float)RPM_MAX * SPEED_MAX;
	
	return;
}

inline int ActMotor::getRPM(){
	return this->rpm;
}

inline float ActMotor::getSpeed(){
	return this->speed;
}

#endif //_ActMotor_HPP_