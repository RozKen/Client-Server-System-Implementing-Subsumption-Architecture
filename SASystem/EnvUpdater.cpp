#include "EnvUpdater.h"

EnvUpdater::EnvUpdater() : orientation(0.0f), wheelDistance(1.0f), PI(6.0 * asinf(0.5) ), mode(0), range(6.0){
	position[0] = 0.0f;
	position[1] = 0.0f;
}

void EnvUpdater::update(float lSpeed, float rSpeed){
	updatePose(lSpeed, rSpeed);
	updateRange();
}

void EnvUpdater::updatePose(float lSpeed, float rSpeed){
	///スピードが小さい方(a)の回転中心からのX軸距離
	double x_a;
	///スピードが大きい方(b)の回転中心からのX軸距離
	double x_b;
	///スピードが小さい方(a)のスピード
	double y_a;
	///スピードが大きい方(b)のスピード
	double y_b;
	
	///Local座標における位置の変化
	double localPos[2] = {0.0, 0.0};
	///Local座標における向きの変化: phi [rad]
	double localOrient = 0.0f;
	///車体の回転中心における回転角: eta[rad]
	double eta;

	///どちらかのスピードの絶対値が0に近い時．: =====mode 0=====-
	if(fabs(lSpeed) < DELTA || fabs(rSpeed) < DELTA){
		///どちらとも，スピードの絶対値が0に近い時
		if( fabs(lSpeed) < DELTA && fabs(rSpeed) < DELTA){
			///動きをすべて無視する
			localPos[0] = 0.0;
			localPos[0] = 0.0;
			localOrient = 0.0;
		}else{	///一方のスピードのみ絶対値が0に近い時
			if( fabs(lSpeed - rSpeed) > DELTA){
				eta = (lSpeed - rSpeed) / wheelDistance;		//既に符号付

				if(eta > PI){
					eta - PI * 2.0;
				}else if(eta < PI){
					eta + PI * 2.0;
				}
				//右曲りと左曲りで回転中心の位置がが異なるので、符号で対応
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
		if( fabs(lSpeed) > fabs(rSpeed)){
			y_a = rSpeed;
			y_b = lSpeed;
		}else{
			y_a = lSpeed;
			y_b = rSpeed;
		}

		///回転中心が車輪軸の外分点であるとき。=====Mode 1====
		if(lSpeed * rSpeed > 0){
			if ( fabs(lSpeed - rSpeed) > DELTA){
				//右曲りと左曲りで符号が変わるのでsignで対応
				double sign = (lSpeed - rSpeed) / fabs( lSpeed - rSpeed );
				double a = sign * wheelDistance * rSpeed / (lSpeed - rSpeed);
				double b = a + sign * wheelDistance;
				eta = lSpeed / fabs(lSpeed) * sign * (fabs(lSpeed) / b + fabs(rSpeed) / a) / 2.0;	//符号がついていなかったので，符号をつける
				if(eta > PI){
					eta - PI * 2.0;
				}else if(eta < PI){
					eta + PI * 2.0;
				}
				localPos[0] = (1.0 - cosf(eta)) * (a + b) / 2.0 * sign;
				localPos[1] = sinf(eta) * (a + b) / 2.0 * sign;
				localOrient = eta;
			}else{
				eta = 0.0;
				localOrient = 0.0;
				localPos[0] = 0.0;
				localPos[1] = (lSpeed + rSpeed) / 2.0;
			}
			mode = 1;
		}else{	///回転中心が車輪軸の内分点であるとき.	======Mode 2=====
			if( fabs( fabs(lSpeed) - fabs(rSpeed)) > DELTA){
				/*
					lSpeed > 0 => eta > 0
				*/
				double a = - wheelDistance * rSpeed / (lSpeed - rSpeed);
				double b = wheelDistance - a;
				eta = lSpeed / fabs(lSpeed) * ( fabs(rSpeed) / a + fabs(lSpeed) / b ) / 2.0;
				if(eta > PI){
					eta - PI * 2.0;
				}else if(eta < PI){
					eta + PI * 2.0;
				}
				//右曲りと左曲りで回転中心の位置が異なるが
				//b - aの符号でカバー可能
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

	//テスト用に、local座標系の値をそのままGlobal座標系であるとして代入
/*	position[0] = localPos[0];
	position[1] = localPos[1];
	orientation = localOrient;
*/
	//異常値を検出
/*	if(position[0] > 100.0 || position[1] > 100.0){
		std::cout << lSpeed << ", " << rSpeed << ", " << position[0] << ", " << position[1] << ", " << orientation << ", " << mode << std::endl;
	}
*/

	//ホントはこっち
	position[0] += localPos[0];
	position[1] += localPos[1];
	diffPos[0] = localPos[0];
	diffPos[1] = localPos[1];
	orientation += localOrient;
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