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
protected:
	/**
		@brief ���݈ʒu
	 */
	int position;
	/**
		@brief ���݂̃o�b�e���[�c�� [%]
	 */
	int battery;
};

inline PositionUpdater::PositionUpdater() : SAModule(1, 0), position(0){
}

inline void PositionUpdater::Run(){
	battery = inputs[1];
	if(battery >= abs(inputs[0]) * 10){	//Battery�c�ʂ��\���̏ꍇ
		position += inputs[0];
	}else{								//Battery�c�ʂ����Ȃ��ꍇ
		position += inputs[0] / abs(inputs[0]) * (battery / 10);
	}
}

inline int PositionUpdater::getPosition(){
	return position;
}

inline int PositionUpdater::getBattery(){
	return battery;
}

#endif //PositionUpdater_HPP_