#ifndef _EnvUpdater_H_
#define _EnvUpdater_H_

#define DELTA	0.01		/**�[�����Ƃ݂Ȃ��ő�l*/
#define MAX_RANGE 300.0		/**���S����ǂ܂ł̋����G�P�ʂȂ�*/
#define WHEEL_DISTANCE 1.0f	/**�ԗ֊Ԃ̋���*/
#include <math.h>

//for Debug
#include <iostream>

/**
	@class EnvUpdater
	@brief ���{�b�g�̃A�N�`���G�[�^�[�ɉ����Ċ����X�V�����́D
	PhysX�Ȃǂ̑���ɂ��񂽂�Ȃ��̂��d���ށD
	<b>����ł́C��̈�̂�envUpdater���d���ނ悤�ȑz��ł���D</b>
	@date 26th July 2011
	@author Kenichi Yorozu
*/
class EnvUpdater {
public:
	/**
		@brief Constructor
	*/
	EnvUpdater();
	/**
		@brief ���ϐ����ׂĂ̍X�V.
		����update�֐����Ă�.
		<b>����ł�updatePose, updateRange�̌Ăяo���̂�</b>
		@param lSpeed Left Motor�̑��x�l
		@param rSpeed Right Motor�̑��x�l
		@sa updatePose
	*/
	void update(float lSpeed, float rSpeed);

	float getPositionX();
	float getPositionY();
	float getDiffPosX();
	float getDiffPosY();
	float getOrientation();
	float getDiffOrient();
	float getRange();
	float getWheelDistance();
	int getMode();
	
protected:
	/**
		@brief �ʒu(position)�Ǝp��(orientation)�̍X�V
		@param lSpeed Left Motor�̑��x�l
		@param rSpeed Right Motor�̑��x�l
	*/
	void updatePose(float lSpeed, float rSpeed);

	/**
		@brief ���{�b�g�̌��݈ʒu��p���āC�ł��߂��ǂƂ̋������Z�o����
		range: 0.0 - 6.0 [�P�ʖ���]
	*/
	void updateRange();

	/**
		@brief �p�x��[-PI, PI]�̊Ԃɐ��K������
		@param radian ���K���������p�x
		@return ���K�����ꂽ�p�x
	*/
	float regurateRadian(float radian);

	/**
		@brief ���{�b�g�̌��݈ʒu: 2-Dimensional
		x: �E��������
		y: �O������
	*/
	float position[2];

	/**
		@brief ���{�b�g�̒��߂̈ʒu�ω�: 2-Dimensional
		x: �E��������
		y: �O������
	*/
	float diffPos[2];
	/**
		@brief ���{�b�g�̑O����0.0 ���������C�E�������̒l
		���{�b�g��Local���W�n��World���W�n�ɑ΂��ĉ�]���Ă����.
		theta [radian] from -PI to PI
	*/
	float orientation;

	/**
		@brief ���{�b�g�̒��߂̌����ω�
	*/
	float diffOrient;
	/**
		@brief ���{�b�g�ɍł��߂��ǂ̍��W�D
		���ݕǂ�6.0�l���̐����`
		(-3.0, -3.0), (-3.0, 3.0), (3.0, 3.0), (3.0, -3.0)�𒸓_�Ƃ���.
		�傫���͒P�ʖ���
	*/
	float range;

	/**
		���E�̎ԗւ̊Ԋu
	*/
	float wheelDistance;

	/**
		�~����PI
	*/
	const double PI;
	/**
	 * �ǂ̃��[�h�Ƃ��Ĕ��肳�ꂽ���H
	 * 0: �قƂ�Ǔ����Ȃ�
	 * 1: �O���_
	 * 2: �����_
	 */
	int mode;
};

inline float EnvUpdater::getPositionX(){
	return position[0];
}
inline float EnvUpdater::getPositionY(){
	return position[1];
}
inline float EnvUpdater::getDiffPosX(){
	return diffPos[0];
}
inline float EnvUpdater::getDiffPosY(){
	return diffPos[1];
}
inline float EnvUpdater::getDiffOrient(){
	return diffOrient;
}
inline float EnvUpdater::getOrientation(){
	return orientation;
}
inline float EnvUpdater::getRange(){
	return range;
}
inline float EnvUpdater::getWheelDistance(){
	return wheelDistance;
}
inline int EnvUpdater::getMode(){
	return mode;
}

inline float EnvUpdater::regurateRadian(float radian){
	while(radian > PI){
		radian = radian - PI * 2.0f;
	}
	while(radian < -PI){
		radian = radian + PI * 2.0f;
	}
	return radian;
}

#endif //_EnvUpdater_H_