#ifndef _SenseOrientation_HPP_
#define _SenseOrientation_HPP_

#include "SAModule.h"
#include <iostream>
#include "EnvUpdater.h"

/**
	@class SenseOrientation
	@brief 位置センサのモジュール
	毎クロックEnvUpdaterから，向きを入手し，signalに変更する
 */
class SenseOrientation :public SAModule{
public:
	/**
		@fn SenseOrientation()
		@param environment: 環境を更新する主体，これから，向き情報を取得する
		@brief Constructor.メンバ変数を初期化する
	*/
	SenseOrientation(EnvUpdater* environment);
	/**
		@brief 向きを検出し，進行方向を0.0，右向きを正として角度をEncodeして出力する
		@param signal 入力信号：Senserには無いはず．
		@return 信号出力：向きをエンコードしたもの
	 */
	float Run(float signal);
	/*
		@brief 向きを返す
		@return 現在の向き
	*/
	double getOrientation();
protected:
	/**
		@brief 実際に向きを測っているモジュール．
		EnvUpdaterから向きを取得し，内部変数へ代入する
	 */
	void updateOrientation();


	/**
		@brief 現在の方向
		進行方向を0.0，右向きを正とする
	*/
	double orientation;
	///環境
	EnvUpdater* env;

	/**
		円周率PI
	*/
	const double PI;
};

inline SenseOrientation::SenseOrientation(EnvUpdater* environment):orientation(0.0), env(environment), PI(6.0 * asinf(0.5) ){
}

inline float SenseOrientation::Run(float signal = 0.0){
	updateOrientation();
	orientation = PI / 2.0 - orientation;
	if(orientation < - PI){
		orientation += 2.0 * PI;
	}else if(orientation > PI){
		orientation -= 2.0 * PI;
	}
	return (float)orientation;
}

inline void SenseOrientation::updateOrientation(){
	orientation = env->getOrientation();
	return;
}

inline double SenseOrientation::getOrientation(){
	return orientation;
}

#endif //_SenseOrientation_HPP_