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
		inputs[0] : RangeSensor����̓���
		outputs[0] : ���̃��[�^�[�h���C�o�[
		outputs[1] : �E�̃��[�^�[�h���C�o�[
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
	///��{�I�ɐM�����o���Ȃ�
	float leftSignal = NO_SIGNAL;
	float rightSignal = NO_SIGNAL;
	phase = 0;
	if(inputs[0] >= 0.5){	///�߂Â������̎��D���ɉ�]����
		switch(phase){
		case 0:
		case 1:
			leftSignal = 0.0f;
			rightSignal = 0.8f;
			phase++;
			break;
		case 2:
			leftSignal = 0.0f;
			rightSignal = 0.8f;
			phase++;
			break;
		case 15:
			leftSignal = 1.0f;
			rightSignal = 1.0f;
			phase = 0;
			break;
		default:
			leftSignal = 1.0f;
			rightSignal = 1.0f;
			phase++;
		}
	}

	///�����[�^�[�̐M�����A�E�g�v�b�g�֏o��
	outputs[0] = leftSignal;
	outputs[1] = rightSignal;
	return;
}

#endif //_Avoid_HPP_