#ifndef _Robot_MAV_H_
#define _Robot_MAV_H_

#include "Constants.h"
#include "Sensors.h"
#include "Controllers.h"
#include "Actuators.h"
#include "Robot.h"

/**
	@brief 探索Robot
	<h1>Sensors</h1>
	<ul>
		<li>Battery Level</li>
		<li>Position</li>
		<li>Range</li>
	</ul>
	<h1>Controllers</h1>
	<ul>
		<li>Avoid</li>
		<li>Alive</li>
		<li>Wander</li>
	</ul>
	<h1>Actuators</h1>
	<ul>
		<li>Position</li>
	</ul>
	@sa Actuators.h
	@sa Controllers.h
	@sa Sensors.h
	
	@sa SenseBattery
	@sa SenseRange
	@sa SenseRange
	
	@sa ContAvoid
	@sa ContAlive
	@sa ContWander

	@sa ActPos

 */
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

	/////////Getters and Setters/////////////
	///These are Created Only for Easy Code Reading
	///Each Methods are equivalent to [get/set]Inputs(index) excepts getColor[R,G,B]

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
		@brief get Range Sensor Value
		@param index 角度に応じたindex
		@return Range Sensor値
	 */
	float getRange(int index) const;
	/**
		@brief get Radiation Sensor Value
		@param index Hashに応じたindex
		@return Radiation Sensor 値
	 */
	float getRad(int index) const;
	/**
		@brief get Red Color of Current Robot
	 */
	float getColorR() const;
	/**
		@brief get Green Color of Current Robot
	 */
	float getColorG() const;
	/**
		@brief get Blue Color of Current Robot
	 */
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
		@brief geoMapを更新する
	 */
	void updateInnerGeoMap();
	/**
		@brief radMapを更新する
	 */
	void updateInnerRadMap();
	
	/**
		@brief 地形マップ.各ロボットが独自に所有する.
	 */
	float geoMap[FIELD_SIZE][FIELD_SIZE];
	/**
		@brief 放射線量マップ.各ロボットが独自に所有する.
	 */
	float radMap[FIELD_SIZE][FIELD_SIZE];
	
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