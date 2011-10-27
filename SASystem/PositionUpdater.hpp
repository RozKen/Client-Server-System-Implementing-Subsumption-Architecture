#ifndef PositionUpdater_HPP_
#define PositionUpdater_HPP_

#include "SAModule.h"
#include "EnvUpdater.h"
#include "Constants.h"

#include <math.h>

/**
	@class PositionUpdater
	@brief Controllerの信号をもとに現在位置を算出するモジュール
	inputs[0] : progress
	inputs[1] : battery
 */
class PositionUpdater : public SAModule{
public:
	/**
		@brief Constructor
		inputs[0] : progress
		inputs[1] : battery : batteryがゼロになってしまえば，進めない
	 */
	PositionUpdater();
	/**
		@brief 入力のprogressを元に，現在位置を算出
	 */
	void Run();
	/**
		@brief getter of position
		@sa position
	 */
	int getPosition();
	/**
		@brief getter of battery
		@sa battery
	 */
	int getBattery();
	/**
		@brief getter of progress
		@sa progress
	 */
	int getProgress();
protected:
	/**
		@brief 現在位置
	 */
	int position;
	/**
		@brief 現在のバッテリー残量 [%]
	 */
	int battery;
	/**
		@brief 現在の進んだ距離
	 */
	int progress;
};

inline PositionUpdater::PositionUpdater() : SAModule(2, 0), position(0), battery(100), progress(0){
	inputs[0] = 0;
	inputs[1] = 100;
}

inline void PositionUpdater::Run(){
	//batteryを更新
	battery = inputs[1];
	//progressを更新
	if(battery >= abs(inputs[0]) * BATTLOSS){	//Battery残量が十分の場合
		progress = inputs[0];
	}else{								//Battery残量が少ない場合
		//この場合のinputs[0]は0でないことが保証されている
		int sign = inputs[0] / abs(inputs[0]);
		progress = sign * (battery / BATTLOSS);
	}
	//
	int tmp = position;
	//positionを更新
	position += progress;
	if(position < 0){
		position = 0;
		progress = position - tmp;
	}else if(position >= LENGTH){
		position = LENGTH - 1;
		progress = position - tmp;
	}
}

inline int PositionUpdater::getPosition(){
	return position;
}

inline int PositionUpdater::getBattery(){
	return battery;
}

inline int PositionUpdater::getProgress(){
	return progress;
}
#endif //PositionUpdater_HPP_