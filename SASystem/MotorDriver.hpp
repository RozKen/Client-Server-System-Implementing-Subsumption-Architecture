#ifndef _MotorDriver_HPP_
#define _MotorDriver_HPP_

#include "SAModule.h"

/**
	@class MotorDriver
	@brief Subsumption Architecture�̉�H���M�����C
	���[�^�[�ւ̎w�ߐM��PWM�֕ύX���郂�W���[��
	@author Kenichi Yorozu
	@date 14th July 2011
	@sa SAModule
 */
class MotorDriver : public SAModule{
public:
	/**
		@brief Constructor.
		@param left true�Ȃ獶�p�Dfalse�Ȃ�E�p
	 */
	MotorDriver(bool left);
	/**
		@brief ���͐M�����G���R�[�h���āC�Ή�����PWM���o�͂���D
		<ol>
			<li>���͐M���̃G���R�[�h�FSignalDecoder</li>
			<li>PWM�M�����擾�FGeneratePWM</li>
		</ol>
		@param signal ���͐M��
		@return PWM�M��
		@sa SignalDecoder
		@sa GeneratePWM
	 */
	float Run(float signal);
protected:
	/**
		@brief ���͐M���̒l0.0 - 1.0��L����PWM�M���т�Mapping����
		@param signal ���͐M��
		@return PWM�M���F����ł�PWM�ł͂Ȃ��āC0.0 - 1.0�ŁC������SA��H���M���Ɠ���
	 */
	float GeneratePWM(float signal);
	/**@brief ���p��Motor Driver�ł���Ȃ�Ctrue/�E�p�Ȃ�false.���̑��͑z��O*/
	bool left;
};

MotorDriver::MotorDriver(bool left): left(left){
}

float MotorDriver::Run(float signal){
	//���p�M��
	float leftSignal;
	//�E�p�M��
	float rightSignal;
	//�M���̉��
	SignalDecoder(signal, leftSignal, rightSignal);
	//�o�͐M��
	float output;

	if(left == true){
		output = leftSignal;
	}else{
		output = rightSignal;
	}
	//PWM�M���̎擾
	output = GeneratePWM(output);
	return output;
}

float GeneratePWM(float signal){
	//TODO PWM�ւ�Mapping���s�����C���݂�0.0 - 1.0�̂܂�
	return signal;
}
#endif //_MotorDriver_HPP_