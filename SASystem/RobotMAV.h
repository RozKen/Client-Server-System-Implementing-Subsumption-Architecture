#ifndef _Robot_MAV_H_
#define _Robot_MAV_H_

#include "Constants.h"
#include "Sensors.h"
#include "Controllers.h"
#include "Actuators.h"
#include "Robot.h"

class RobotMAV : public Robot{
public:
	/**
		@brief Default Constructor
		Moduleを追加していく．
	 */
	RobotMAV();
	RobotMAV(std::string directoryPath, std::string fileName);

	/**
		@brief 実行時の動作
		@sa SAModule::Run()
	 */
	virtual void Run();
	/**
		@brief getBatteryStatus via Input
	 */
	float getBattery() const;
	/**
		@brief setBatteryStatus via Input
	 */
	void setBattery(float value);
	/**
		@brief get X position via Input
	 */
	float getPosX() const;
	/**
		@brief set X position via Input
	 */
	void setPosX(float value);
	/**
		@brief get Y position via Input
	 */
	float getPosY() const;
	/**
		@brief set Y position via Input
	 */
	void setPosY(float value);
	/**
		@brief getColor of Current Robot
	 */
	float getColorR() const;
	float getColorG() const;
	float getColorB() const;

	/**
		@brief すべてのArbiterを実行する
	 */
	virtual void ProcessArbiters();
protected:
	/**
		@brief Moduleの登録などを行なう．
		Constructorから呼び出されることを想定
	 */
	void Initialize();
	/**
		@brief RobotのColor
		どのモジュールが発現しているかによって，変化する
	 */
	float color[3];
	/**
		@brief ModuleごとのColor(R,G,B)
		modColor[module][r/g/b]
	 */
	float modColor[3][3];
	/**
		@brief Layerの数
	 */
	int numOfLayers;
};

#endif	//_Robot_MAV_H_