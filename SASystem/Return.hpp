#ifndef _Return_HPP_
#define _Return_HPP_

#include "SAModule.h"
#include "StochasticSelecter.hpp"

/**
	@class Return
	@brief ������ς���@�\�������ǂ郂�W���[��
*/
class Return : public SAModule{
public:
	/**
		@brief Constructor
	*/
	Return();

	/**
		@brief ������ς���M�����o���D
		@param signal ����ł͓��͐M�����l���Ă��Ȃ��D�{���͒n�����C�Z���T�[�I�Ȃ̂��~����
		@return output ���[�^�[�ւ̐M��
	*/
	float Run(float signal);
};

inline Return::Return(){
}

inline float Return::Run(float signal){
	float output = 0.0f;
	///���v���ɉ�]����
	float rightSignal = 1.0f;
	float leftSignal = 0.0f;
	

	///�����[�^�[�̐M������ɃG���R�[�h
	output = SignalEncoder(rightSignal, leftSignal);
	return output;
}

#endif //_Return_HPP_