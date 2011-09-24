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
protected:
	/**
		@brief 現在位置
	 */
	int position;
	/**
		@brief 現在のバッテリー残量 [%]
	 */
	int battery;
};

inline PositionUpdater::PositionUpdater() : SAModule(1, 0), position(0){
}

inline void PositionUpdater::Run(){
	battery = inputs[1];
	if(battery >= abs(inputs[0]) * 10){	//Battery残量が十分の場合
		position += inputs[0];
	}else{								//Battery残量が少ない場合
		position += inputs[0] / abs(inputs[0]) * (battery / 10);
	}
}

inline int PositionUpdater::getPosition(){
	return position;
}

inline int PositionUpdater::getBattery(){
	return battery;
}

#endif //PositionUpdater_HPP_