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
	/**
		@brief ���i���邩�C�����_���ɓ��������C���̊m���őI������
		@sa StochasitcSelector
	*/
	StochasticSelector* ss;
	/**
		@brief �����_���ȓ����𐶐�����̂ɗp����
		@sa Random
	*/
	Random<boost::uniform_real<> >* random;
};

inline Wander::Wander(){
	ss = new StochasticSelector(0.1);
	random = new Random<boost::uniform_real<> >(0, 1);
}

inline float Wander::Run(float signal){
	float output = 0.0f;
	///9���̊m���Œ��i����
	float rightSignal = 1.0f;
	float leftSignal = 1.0f;
	if( ss->get() ){	///�c���1���̊m���ŁC�����_���ɓ���
		rightSignal = random->operator()();
		leftSignal = random->operator()();
	}

	///�����[�^�[�̐M������ɃG���R�[�h
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Wander_HPP_