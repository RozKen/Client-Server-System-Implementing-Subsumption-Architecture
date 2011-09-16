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
		outputs[0] : ���̃��[�^�[�h���C�o�[
		outputs[1] : �E�̃��[�^�[�h���C�o�[
	*/
	Wander();

	/**
		@brief ����@���M�����o��.
	*/
	void Run();
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

inline Wander::Wander(): SAModule(0,2) {
	ss = new StochasticSelector(0.1);
	random = new Random<boost::uniform_real<> >(0, 1);
}

inline void Wander::Run(){
	///9���̊m���Œ��i����
	float leftSignal = 1.0f;
	float rightSignal = 1.0f;
	if( ss->get() ){	///�c���1���̊m���ŁC�����_���ɓ���
		leftSignal = random->operator()();
		rightSignal = random->operator()();
	}

	///�����[�^�[�̐M������ɃG���R�[�h
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Wander_HPP_