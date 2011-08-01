#ifndef _EnvUpdater_HPP_
#define _EnvUpdater_HPP_

///�[�����Ƃ݂Ȃ��ő�l
#define DELTA	0.0001
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
		<b>����ł�updatePose�̌Ăяo���̂�</b>
		@param lSpeed Left Motor�̑��x�l
		@param rSpeed Right Motor�̑��x�l
		@sa updatePose
	*/
	void update(float lSpeed, float rSpeed);

	float getPositionX();
	float getPositionY();
	float getOrientation();
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
		���{�b�g�̌��݈ʒu: 2-Dimensional
		x: �E��������
		y: �O������
	*/
	float position[2];
	/**
		���{�b�g��Local���W�n��World���W�n�ɑ΂��ĉ�]���Ă����.
		theta [radian]
	*/
	float orientation;

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

inline EnvUpdater::EnvUpdater() : orientation(0.0f), wheelDistance(1.0f), PI(6.0 * asinf(0.5) ), mode(0){
	position[0] = 0.0f;
	position[1] = 0.0f;
}

inline void EnvUpdater::update(float lSpeed, float rSpeed){
	updatePose(lSpeed, rSpeed);
}

inline void EnvUpdater::updatePose(float lSpeed, float rSpeed){
	///�X�s�[�h����������(a)�̉�]���S�����X������
	double x_a;
	///�X�s�[�h���傫����(b)�̉�]���S�����X������
	double x_b;
	///�X�s�[�h����������(a)�̃X�s�[�h
	double y_a;
	///�X�s�[�h���傫����(b)�̃X�s�[�h
	double y_b;
	
	///Local���W�ɂ�����ʒu�̕ω�
	double localPos[2] = {0.0, 0.0};
	///Local���W�ɂ���������̕ω�: phi [rad]
	double localOrient = 0.0f;
	///�ԑ̂̉�]���S�ɂ������]�p: eta[rad]
	double eta;

	///�ǂ��炩�̃X�s�[�h�̐�Βl��0�ɋ߂����D
	if(fabs(lSpeed) < DELTA || fabs(rSpeed) < DELTA){
		///�ǂ���Ƃ��C�X�s�[�h�̐�Βl��0�ɋ߂���
		if( fabs(lSpeed) < DELTA && fabs(rSpeed) < DELTA){
			///�����𖳎�����
			localPos[0] = 0.0;
			localPos[0] = 0.0;
			localOrient = 0.0;
		}else{	///����݂̂̃X�s�[�h�̐�Βl��0�ɋ߂���
			if(lSpeed > rSpeed){
				y_b = lSpeed;
			}else{
				y_b = rSpeed;
			}
			if( fabs(lSpeed - rSpeed) > DELTA){
				//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
				double sign = (lSpeed - rSpeed) / fabs( lSpeed - rSpeed );

				eta = y_b / wheelDistance;
				localPos[0] = (1.0 - cosf(eta)) * wheelDistance / 2.0 * sign;
				localPos[1] = -sinf(eta) * wheelDistance / 2.0 * sign;
				localOrient = PI / 2.0 - eta * sign;
			}else{
				eta = 0.0;
				localOrient = 0.0;
				localPos[0] = 0.0;
				localPos[1] = (lSpeed + rSpeed) / 2.0;
			}
		}
		mode = 0;
	}else{
		if( fabs(lSpeed) > fabs(rSpeed)){
			y_a = rSpeed;
			y_b = lSpeed;
		}else{
			y_a = lSpeed;
			y_b = rSpeed;
		}

		///��]���S���ԗ֎��̊O���_�ł���Ƃ��B
		if(lSpeed * rSpeed > 0){
			x_a = y_a * wheelDistance / (y_b - y_a);
			x_b = x_a * y_b / y_a;
			eta = y_a / x_a;
			if ( fabs(lSpeed - rSpeed) > DELTA){
				//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
				double sign = (lSpeed - rSpeed) / fabs( lSpeed - rSpeed );
				localPos[0] = (1.0 - cosf(eta)) * (x_a + x_b) / 2.0 * sign;
				localPos[1] = -sinf(eta) * (x_a + x_b) / 2.0 * sign;
				localOrient = PI / 2.0 - eta * sign;
			}else{
				eta = 0.0;
				localOrient = 0.0;
				localPos[0] = 0.0;
				localPos[1] = (lSpeed + rSpeed) / 2.0;
			}
			mode = 1;
		}else{	///��]���S���ԗ֎��̓����_�ł���Ƃ�.
			//
			y_a = rSpeed;
			y_b = lSpeed;
			x_a = y_a * wheelDistance / (y_a + y_b);
			x_b = x_a * y_b / y_a;
			
			if( fabs( fabs(lSpeed) - fabs(rSpeed)) > DELTA){
				//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
				double sign = (fabs(lSpeed) - fabs(rSpeed)) / fabs( fabs(lSpeed) - fabs(rSpeed) );
				//�����傫���Ƃ��Aeta = - y_b / x_b�ŁA�E���傫���Ƃ��Aeta = y_b / x_b
				eta = - sign * y_b / x_b;
				///////////////////////������ւ�������D�z���g�H
				localPos[0] = (cosf(eta) - 1.0) * (x_b - x_a) / 2.0 * sign;
				localPos[1] = sinf(eta) * (x_b - x_a) / 2.0 * sign;
				localOrient = PI / 2.0 + eta;
				
			}else{
				eta = 0.0;
				localOrient = 0.0;
				localPos[0] = 0.0;
				localPos[1] = (lSpeed + rSpeed) / 2.0;
			}
			mode = 2;
		}
	}

	//�e�X�g�p�ɁAlocal���W�n�̒l�����̂܂�Global���W�n�ł���Ƃ��đ��
/*	position[0] = localPos[0];
	position[1] = localPos[1];
	orientation = localOrient;
*/
	//�ُ�l�����o
/*	if(position[0] > 100.0 || position[1] > 100.0){
		std::cout << lSpeed << ", " << rSpeed << ", " << position[0] << ", " << position[1] << ", " << orientation << ", " << mode << std::endl;
	}
*/

	//�z���g�͂�����
	position[0] += localPos[0];
	position[1] += localPos[1];
	orientation += localOrient;
	
}

inline float EnvUpdater::getPositionX(){
	return position[0];
}
inline float EnvUpdater::getPositionY(){
	return position[1];
}
inline float EnvUpdater::getOrientation(){
	return orientation;
}
inline float EnvUpdater::getWheelDistance(){
	return wheelDistance;
}
inline int EnvUpdater::getMode(){
	return mode;
}

#endif //_EnvUpdater_HPP_