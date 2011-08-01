#ifndef _EnvUpdater_HPP_
#define _EnvUpdater_HPP_

///ゼロだとみなす最大値
#define DELTA	0.0001
#include <math.h>

//for Debug
#include <iostream>

/**
	@class EnvUpdater
	@brief ロボットのアクチュエーターに応じて環境を更新する主体．
	PhysXなどの代わりにかんたんなものを仕込む．
	<b>現状では，一体一体にenvUpdaterを仕込むような想定である．</b>
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
		@brief 環境変数すべての更新.
		順次update関数を呼ぶ.
		<b>現状ではupdatePoseの呼び出しのみ</b>
		@param lSpeed Left Motorの速度値
		@param rSpeed Right Motorの速度値
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
		@brief 位置(position)と姿勢(orientation)の更新
		@param lSpeed Left Motorの速度値
		@param rSpeed Right Motorの速度値
	*/
	void updatePose(float lSpeed, float rSpeed);

	/**
		ロボットの現在位置: 2-Dimensional
		x: 右方向が正
		y: 前方が正
	*/
	float position[2];
	/**
		ロボットのLocal座標系がWorld座標系に対して回転している量.
		theta [radian]
	*/
	float orientation;

	/**
		左右の車輪の間隔
	*/
	float wheelDistance;

	/**
		円周率PI
	*/
	const double PI;
	/**
	 * どのモードとして判定されたか？
	 * 0: ほとんど動かない
	 * 1: 外分点
	 * 2: 内分点
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

	///どちらかのスピードの絶対値が0に近い時．
	if(fabs(lSpeed) < DELTA || fabs(rSpeed) < DELTA){
		///どちらとも，スピードの絶対値が0に近い時
		if( fabs(lSpeed) < DELTA && fabs(rSpeed) < DELTA){
			///動きを無視する
			localPos[0] = 0.0;
			localPos[0] = 0.0;
			localOrient = 0.0;
		}else{	///一方のみのスピードの絶対値が0に近い時
			if(lSpeed > rSpeed){
				y_b = lSpeed;
			}else{
				y_b = rSpeed;
			}
			if( fabs(lSpeed - rSpeed) > DELTA){
				//右曲りと左曲りで符号が変わるのでsignで対応
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

		///回転中心が車輪軸の外分点であるとき。
		if(lSpeed * rSpeed > 0){
			x_a = y_a * wheelDistance / (y_b - y_a);
			x_b = x_a * y_b / y_a;
			eta = y_a / x_a;
			if ( fabs(lSpeed - rSpeed) > DELTA){
				//右曲りと左曲りで符号が変わるのでsignで対応
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
		}else{	///回転中心が車輪軸の内分点であるとき.
			//
			y_a = rSpeed;
			y_b = lSpeed;
			x_a = y_a * wheelDistance / (y_a + y_b);
			x_b = x_a * y_b / y_a;
			
			if( fabs( fabs(lSpeed) - fabs(rSpeed)) > DELTA){
				//右曲りと左曲りで符号が変わるのでsignで対応
				double sign = (fabs(lSpeed) - fabs(rSpeed)) / fabs( fabs(lSpeed) - fabs(rSpeed) );
				//左が大きいとき、eta = - y_b / x_bで、右が大きいとき、eta = y_b / x_b
				eta = - sign * y_b / x_b;
				///////////////////////ここらへん怪しい．ホント？
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