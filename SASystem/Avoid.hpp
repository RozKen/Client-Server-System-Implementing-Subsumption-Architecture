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
		�f�t�H���g�ł́C�M�����o���Ȃ�( NO_SIGNAL ).
		����́Cphase�ɉ����āC�قȂ�M�����o�����Ƃɂ���āC���{�b�g�̌�����
		�ς��邱�ƂŎ��{�����
	*/
	void Run();
protected:
	///�Փˉ���ɂ�����t�F�[�Y
	int phase;
};

inline Avoid::Avoid() : SAModule(1, 2), phase(0){
}

inline void Avoid::Run(){
	float output = 0.0f;
	///��{�I�ɐM�����o���Ȃ�
	float rightSignal = NO_SIGNAL;
	float leftSignal = NO_SIGNAL;
	phase = 0;
	if(inputs[0] >= 0.5){	///�߂Â������̎��D���ɉ�]����
		switch(phase){
		case 0:
		case 1:
			rightSignal = 0.9f;
			leftSignal = 0.5f;
			phase++;
			break;
		case 2:
			rightSignal = 0.9f;
			leftSignal = 0.5f;
			phase++;
			break;
		case 15:
			rightSignal = 0.9f;
			leftSignal = 0.9f;
			phase = 0;
			break;
		default:
			rightSignal = 0.9f;
			leftSignal = 0.9f;
			phase++;
		}
	}

	///�����[�^�[�̐M�����A�E�g�v�b�g�֏o��
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Avoid_HPP_