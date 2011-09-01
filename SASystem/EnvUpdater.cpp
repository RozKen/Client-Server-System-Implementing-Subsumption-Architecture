#include "EnvUpdater.h"

EnvUpdater::EnvUpdater() : orientation(0.0f), wheelDistance(1.0f), PI(6.0 * asinf(0.5) ), mode(0), range(300.0), diffOrient(0.0f){
	position[0] = 0.0f;
	position[1] = 0.0f;
	diffPos[0] = 0.0f;
	diffPos[1] = 0.0f;
}

void EnvUpdater::update(float lSpeed, float rSpeed){
	updatePose(lSpeed, rSpeed);
	updateRange();
}

void EnvUpdater::updatePose(float lSpeed, float rSpeed){
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

	///�ǂ��炩�̃X�s�[�h�̐�Βl��0�ɋ߂����D: =====mode 0=====-
	if(fabs(lSpeed) < DELTA || fabs(rSpeed) < DELTA){
		///�ǂ���Ƃ��C�X�s�[�h�̐�Βl��0�ɋ߂���
		if( fabs(lSpeed) < DELTA && fabs(rSpeed) < DELTA){
			///���������ׂĖ�������
			localPos[0] = 0.0;
			localPos[0] = 0.0;
			localOrient = 0.0;
		}else{	///����̃X�s�[�h�̂ݐ�Βl��0�ɋ߂���
			if( fabs(lSpeed - rSpeed) > DELTA){
				eta = (lSpeed - rSpeed) / wheelDistance;		//���ɕ����t
				eta = regurateRadian(eta);
				//�E�Ȃ�ƍ��Ȃ�ŉ�]���S�̈ʒu�����قȂ�̂ŁA�����őΉ�
				double sign = 1;
				if(fabs(rSpeed) > fabs(lSpeed)){
					sign = -1;
				}
				
				localPos[0] = (1.0 - cosf(eta)) * wheelDistance / 2.0 * sign;
				localPos[1] = sinf(eta) * wheelDistance / 2.0 * sign;
				localOrient = eta;
			}else{
				eta = 0.0;
				localOrient = 0.0;
				localPos[0] = 0.0;
				localPos[1] = (lSpeed + rSpeed) / 2.0;
			}
		}
		mode = 0;
	}else{
		if(fabs(lSpeed - rSpeed) < DELTA){
			eta = 0.0;
			localOrient = 0.0;
			localPos[0] = 0.0;
			localPos[1] = (lSpeed + rSpeed) / 2.0;
			mode = 4;
		}else{
			if( fabs(lSpeed) > fabs(rSpeed)){
				y_a = rSpeed;
				y_b = lSpeed;
			}else{
				y_a = lSpeed;
				y_b = rSpeed;
			}

			///��]���S���ԗ֎��̊O���_�ł���Ƃ��B=====Mode 1====
			if(lSpeed * rSpeed > 0){
				//�E�Ȃ�ƍ��Ȃ�ŕ������ς��̂�sign�őΉ�
				double sign = (lSpeed - rSpeed) / fabs( lSpeed - rSpeed );
				double a = sign * wheelDistance * rSpeed / (lSpeed - rSpeed);
				double b = a + sign * wheelDistance;
				eta = lSpeed / fabs(lSpeed) * sign * (fabs(lSpeed) / b + fabs(rSpeed) / a) / 2.0;	//���������Ă��Ȃ������̂ŁC����������
				eta = regurateRadian(eta);
				localPos[0] = (1.0 - cosf(eta)) * (a + b) / 2.0 * sign;
				localPos[1] = sinf(eta) * (a + b) / 2.0 * sign;
				localOrient = eta;
				mode = 1;
			}else{	///��]���S���ԗ֎��̓����_�ł���Ƃ�.	======Mode 2=====
				if( fabs( fabs(lSpeed) - fabs(rSpeed)) > DELTA){
					/*
						lSpeed > 0 => eta > 0
					*/
					double a = - wheelDistance * rSpeed / (lSpeed - rSpeed);
					double b = wheelDistance - a;
					eta = lSpeed / fabs(lSpeed) * ( fabs(rSpeed) / a + fabs(lSpeed) / b ) / 2.0;
					eta = regurateRadian(eta);
					//�E�Ȃ�ƍ��Ȃ�ŉ�]���S�̈ʒu���قȂ邪
					//b - a�̕����ŃJ�o�[�\
					localPos[0] = (1.0 - cosf(eta)) * (b - a) / 2.0;// * sign;
					localPos[1] = sinf(eta) * (b - a) / 2.0;// * sign;
					localOrient = eta;
				
				}else{
					eta = 0.0;
					localOrient = 0.0;
					localPos[0] = 0.0;
					localPos[1] = (lSpeed + rSpeed) / 2.0;
				}
				mode = 2;
			}
		}
	}

	//�z���g�͂�����
	diffPos[0] = localPos[0];
	diffPos[1] = localPos[1];

	double cos = cosf(-orientation);
	double sin = sinf(-orientation);
	position[0] += cos * localPos[0] - sin * localPos[1];
	position[1] += sin * localPos[0] + cos * localPos[1];

	orientation += localOrient;
	orientation = regurateRadian(orientation);
	diffOrient = localOrient;
	
}

void EnvUpdater::updateRange(){
	float tmpRange = MAX_RANGE;
	float tmp[4];
	tmp[0] = fabs(MAX_RANGE - position[0]);
	tmp[1] = fabs(position[0] + MAX_RANGE);
	tmp[2] = fabs(MAX_RANGE - position[1]);
	tmp[3] = fabs(position[1] + MAX_RANGE);
	for(int i = 0; i < 4; i++){
		if( tmp[i] < tmpRange){
			tmpRange = tmp[i];
		}
	}
	range = tmpRange;
}