#ifndef _SensePosition_HPP_
#define _SensePosition_HPP_

#include "SAModule.h"
#include <iostream>
#include "EnvUpdater.hpp"

/**
	@class SensePosition
	@brief 位置センサのモジュール
	毎クロックEnvUpdaterから，位置を入手し，signalに変更する
 */
class SensePosition :public SAModule{
public:
	/**
		@fn SensePosition()
		@param environment: 環境を更新する主体，これから，位置情報を取得する
		@brief Constructor.メンバ変数を初期化する
	*/
	SensePosition(EnvUpdater* environment);
	/**
		@brief 位置を検出し，2次元座標をEncodeして出力する
		@param signal 入力信号：Senserには無いはず．
		@return 信号出力：2次元座標をエンコードしたもの
	 */
	float Run(float signal);
	/*
		@brief X座標を返す
		@return 現在のX座標
	*/
	double getPositionX();
	/*
		@brief Y座標を返す
		@return 現在のX座標
	*/
	double getPositionY();
protected:
	/**
		@brief 実際に位置を測っているモジュール．
		EnvUpdaterから位置を取得し，内部変数へ代入する
	 */
	void updatePosition();

	///現在の距離
	double position[2];
	///環境
	EnvUpdater* env;
};

inline SensePosition::SensePosition(EnvUpdater* environment): env(environment){
	position[0] = 0.0;
	position[1] = 0.0;
}

inline float SensePosition::Run(float signal = 0.0){
	updatePosition();
	SignalEncoder(position[0], position[1]);
	return signal;
}

inline void SensePosition::updatePosition(){
	position[0] = env->getPositionX();
	position[1] = env->getPositionY();
	return;
}

inline double SensePosition::getPositionX(){
	return position[0];
}

inline double SensePosition::getPositionY(){
	return position[1];
}

#endif //_SensePosition_HPP_