#ifndef _EnvUpdater_hpp_
#define _EnvUpdater_hpp_

///ゼロだとみなす最大値
#define DELTA	0.0001
#include <math.h>

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
};

inline EnvUpdater::EnvUpdater() : wheelDistance(1.0f), orientation(0.0f), PI(6.0 * asin(0.5) ){
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
	if(abs(lSpeed) < DELTA || abs(rSpeed) < DELTA){
		///どちらとも，スピードの絶対値が0に近い時
		if( abs(lSpeed) < DELTA && abs(rSpeed) < DELTA){
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
			//右曲りと左曲りで符号が変わるのでsignで対応
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
			//右曲りと左曲りで符号が変わるのでsignで対応
			double sign = (lSpeed - rSpeed) / abs( lSpeed - rSpeed );
			localPos[0] = (1 - cos(eta)) * (x_a + x_b) / 2 * sign;
			localPos[1] = -sin(eta) * (x_a + x_b) / 2 * sign;
			localOrient = PI / 2 - eta * sign;
		}else{
			x_a = y_a * wheelDistance / (y_a + y_b);
			x_b = x_a * y_b / y_a;
			eta = x_b / y_b;
			//右曲りと左曲りで符号が変わるのでsignで対応
			double sign = (lSpeed - rSpeed) / abs( lSpeed - rSpeed );
			///////////////////////ここらへん怪しい．ホント？
			localPos[0] = (1 - cos(eta)) * (x_b - x_a) / 2 * sign;
			localPos[1] = -sin(eta) * (x_b - x_a) / 2 * sign;
			localOrient = PI / 2 - eta * sign;
		}
	}
}

#endif //_EnvUpdater_hpp_