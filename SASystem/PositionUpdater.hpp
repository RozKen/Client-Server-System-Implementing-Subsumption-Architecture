#ifndef PositionUpdater_HPP_
#define PositionUpdater_HPP_

#include "SAModule.h"
#include "EnvUpdater.h"
#include "Constants.h"

#include <math.h>

/**
	@class PositionUpdater
	@brief Controller�̐M�������ƂɌ��݈ʒu���Z�o���郂�W���[��
	inputs[0] : progress
	inputs[1] : battery
 */
class PositionUpdater : public SAModule{
public:
	/**
		@brief Constructor
		inputs[0] : progress
		inputs[1] : battery : battery���[���ɂȂ��Ă��܂��΁C�i�߂Ȃ�
	 */
	PositionUpdater();
	/**
		@brief ���͂�progress�����ɁC���݈ʒu���Z�o
	 */
	void Run();
	/**
		@brief getter of position
		@sa position
	 */
	int getPosition();
	/**
		@brief getter of battery
		@sa battery
	 */
	int getBattery();
	/**
		@brief getter of progress
		@sa progress
	 */
	int getProgress();
protected:
	/**
		@brief ���݈ʒu
	 */
	int position;
	/**
		@brief ���݂̃o�b�e���[�c�� [%]
	 */
	int battery;
	/**
		@brief ���݂̐i�񂾋���
	 */
	int progress;
};

inline PositionUpdater::PositionUpdater() : SAModule(2, 0), position(0), battery(100), progress(0){
	inputs[0] = 0;
	inputs[1] = 100;
}

inline void PositionUpdater::Run(){
	//battery���X�V
	battery = inputs[1];
	//progress���X�V
	if(battery >= abs(inputs[0]) * BATTLOSS){	//Battery�c�ʂ��\���̏ꍇ
		progress = inputs[0];
	}else{								//Battery�c�ʂ����Ȃ��ꍇ
		//���̏ꍇ��inputs[0]��0�łȂ����Ƃ��ۏ؂���Ă���
		int sign = inputs[0] / abs(inputs[0]);
		progress = sign * (battery / BATTLOSS);
	}
	//
	int tmp = position;
	//position���X�V
	position += progress;
	if(position < 0){
		position = 0;
		progress = position - tmp;
	}else if(position >= LENGTH){
		position = LENGTH - 1;
		progress = position - tmp;
	}
}

inline int PositionUpdater::getPosition(){
	return position;
}

inline int PositionUpdater::getBattery(){
	return battery;
}

inline int PositionUpdater::getProgress(){
	return progress;
}
#endif //PositionUpdater_HPP_