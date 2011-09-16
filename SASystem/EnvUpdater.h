#ifndef _EnvUpdater_H_
#define _EnvUpdater_H_

#define DELTA	0.01		/**ゼロだとみなす最大値*/
#define MAX_RANGE 300.0		/**中心から壁までの距離；単位なし*/
#define WHEEL_DISTANCE 1.0f	/**車輪間の距離*/
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
		<b>現状ではupdatePose, updateRangeの呼び出しのみ</b>
		@param lSpeed Left Motorの速度値
		@param rSpeed Right Motorの速度値
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
		@brief 位置(position)と姿勢(orientation)の更新
		@param lSpeed Left Motorの速度値
		@param rSpeed Right Motorの速度値
	*/
	void updatePose(float lSpeed, float rSpeed);

	/**
		@brief ロボットの現在位置を用いて，最も近い壁との距離を算出する
		range: 0.0 - 6.0 [単位無し]
	*/
	void updateRange();

	/**
		@brief 角度を[-PI, PI]の間に正規化する
		@param radian 正規化したい角度
		@return 正規化された角度
	*/
	float regurateRadian(float radian);

	/**
		@brief ロボットの現在位置: 2-Dimensional
		x: 右方向が正
		y: 前方が正
	*/
	float position[2];

	/**
		@brief ロボットの直近の位置変化: 2-Dimensional
		x: 右方向が正
		y: 前方が正
	*/
	float diffPos[2];
	/**
		@brief ロボットの前方が0.0 左方が負，右方が正の値
		ロボットのLocal座標系がWorld座標系に対して回転している量.
		theta [radian] from -PI to PI
	*/
	float orientation;

	/**
		@brief ロボットの直近の向き変化
	*/
	float diffOrient;
	/**
		@brief ロボットに最も近い壁の座標．
		現在壁は6.0四方の正方形
		(-3.0, -3.0), (-3.0, 3.0), (3.0, 3.0), (3.0, -3.0)を頂点とする.
		大きさは単位無し
	*/
	float range;

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