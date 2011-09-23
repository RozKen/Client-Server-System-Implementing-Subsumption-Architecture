#ifndef PositionUpdater_HPP_
#define PositionUpdater_HPP_

#include "SAModule.h"
#include "EnvUpdater.h"
#include "Constants.h"

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
protected:
	/**
		@brief 現在位置
	 */
	int position;
};

inline PositionUpdater::PositionUpdater() : SAModule(1, 0), position(0){
}

inline void PositionUpdater::Run(){
	position += inputs[0];
}

#endif //PositionUpdater_HPP_