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
		inputs[0] : ���͐M��
		output[0] : ���[�^�[�֑���PWM�M��
	 */
	MotorDriver();
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
	void Run();
protected:
	/**
		@brief ���͐M���̒l��L����PWM�M���т�Mapping����
		@param signal ���͐M��
		@return PWM�M���F����ł�PWM�ł͂Ȃ��āC���͐M�����̂܂܂ŁC������SA��H���M���Ɠ���
	 */
	float GeneratePWM(float signal);
};

inline MotorDriver::MotorDriver(): SAModule(1, 1){
}

inline void MotorDriver::Run(){
	//PWM�M���̎擾
	outputs[0] = GeneratePWM(inputs[0]);
	return;
}

inline float MotorDriver::GeneratePWM(float signal){
	//TODO PWM�ւ�Mapping���s�����C���݂�0.0 - 1.0�̂܂�
	if(signal == NO_SIGNAL){
		signal == NO_SIGNAL;
	}
	return signal;
}
#endif //_MotorDriver_HPP_