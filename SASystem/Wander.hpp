#ifndef _Wander_HPP_
#define _Wander_HPP_

#include "SAModule.h"
#include "StochasticSelecter.hpp"

/**
	@class Wander
	@brief ���ӂ�������@�\�������ǂ郂�W���[��
*/
class Wander : public SAModule{
public:
	/**
		@brief Constructor
	*/
	Wander();

	/**
		@brief ������M�����o��
		@param signal ����ł͓��͐M�����l���Ă��Ȃ�
		@return output ���[�^�[�ւ̐M��
	*/
	float Run(float signal);
};

inline Wander::Wander(){
}

inline float Wander::Run(float signal){
	float output = 0.0f;
	///9���̊m���Œ��i����
	float rightSignal = 1.0f;
	float leftSignal = 1.0f;
	StochasticSelector ss(0.9);
	if( !ss() ){	///�c���1���̊m���ŁC�����_���ɓ���
		Random<boost::uniform_real<> > random(0, 1);
		rightSignal = random();
		leftSignal = random();
	}

	///�����[�^�[�̐M������ɃG���R�[�h
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Wander_HPP_