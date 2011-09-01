#ifndef _Avoid_HPP_
#define _Avoid_HPP_

#include "SAModule.h"

/**
	@class Avoid
	@brief ���̂������@�\�������ǂ郂�W���[��
*/
class Avoid : public SAModule{
public:
	/**
		@brief Constructor
	*/
	Avoid();

	/**
		@brief RangeSensor����󂯎�����M������ɁC���[�^�[�ւ̉�𖽗߂��o���D
		�f�t�H���g�ł́C���i����
		@param signal RangeSensor����̐M��
		@return output ���[�^�[�ւ̐M��
	*/
	float Run(float signal);
};

inline Avoid::Avoid(){
}

inline float Avoid::Run(float signal){
	float output = 0.0f;
	///��{�I�ɒ��i����
	float rightSignal = 0.9f;
	float leftSignal = 0.9f;

	if(signal >= 0.5){	///�߂Â������̎��D���ɉ�]����
		rightSignal = 0.8f;
		leftSignal = 0.6f;
	}

	///�����[�^�[�̐M������ɃG���R�[�h
	output = SignalEncoder(leftSignal, rightSignal);
	return output;
}

#endif //_Avoid_HPP_