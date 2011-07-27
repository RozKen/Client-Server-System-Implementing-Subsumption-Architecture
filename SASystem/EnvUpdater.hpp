#ifndef _EnvUpdater_hpp_
#define _EnvUpdater_hpp_

///�[�����Ƃ݂Ȃ��ő�l
#define DELTA	0.0001
#include <math.h>

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
};

inline EnvUpdater::EnvUpdater() : wheelDistance(1.0f), orientation(0.0f), PI(6.0 * asin(0.5) ){
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
	if(abs(lSpeed) < DELTA || abs(rSpeed) < DELTA){
		///�ǂ���Ƃ��C�X�s�[�h�̐�Βl��0�ɋ߂���
		if( abs(lSpeed) < DELTA && abs(rSpeed) < DELTA){
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
			//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
			double sign = (lSpeed - rSpeed) / abs( lSpeed - rSpeed );

			eta = y_b / wheelDistance;
			localPos[0] = (1 - cos(eta)) * wheelDistance / 2 * sign;
			localPos[1] = -sin(eta) * wheelDistance / 2 * sign;
			localOrient = PI / 2 - eta * sign;
		}
	}else{
		if( lSpeed > rSpeed){
			y_a = rSpeed;
			y_b = lSpeed;
		}else{
			y_a = lSpeed;
			y_b = rSpeed;
		}

		if(lSpeed * rSpeed > 0){
			x_a = y_a * wheelDistance / (y_b - y_a);
			x_b = x_a * y_b / y_a;
			eta = y_a / x_a;
			//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
			double sign = (lSpeed - rSpeed) / abs( lSpeed - rSpeed );
			localPos[0] = (1 - cos(eta)) * (x_a + x_b) / 2 * sign;
			localPos[1] = -sin(eta) * (x_a + x_b) / 2 * sign;
			localOrient = PI / 2 - eta * sign;
		}else{
			x_a = y_a * wheelDistance / (y_a + y_b);
			x_b = x_a * y_b / y_a;
			eta = x_b / y_b;
			//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
			double sign = (lSpeed - rSpeed) / abs( lSpeed - rSpeed );
			///////////////////////������ւ�������D�z���g�H
			localPos[0] = (1 - cos(eta)) * (x_b - x_a) / 2 * sign;
			localPos[1] = -sin(eta) * (x_b - x_a) / 2 * sign;
			localOrient = PI / 2 - eta * sign;
		}
	}
}

#endif //_EnvUpdater_hpp_