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
		outputs[0] : ���̃��[�^�[�h���C�o�[
		outputs[1] : �E�̃��[�^�[�h���C�o�[
	*/
	Return();

	/**
		@brief ������ς���M�����o���D
	*/
	void Run();
};

inline Return::Return(): SAModule(0, 2){
}

inline void Return::Run(){
	///���v���ɉ�]����
	float leftSignal = 1.0f;
	float rightSignal = 0.0f;

	///�����[�^�[�̐M������ɃG���R�[�h
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Return_HPP_