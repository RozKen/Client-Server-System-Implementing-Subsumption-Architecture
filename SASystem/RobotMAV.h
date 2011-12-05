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
		Module��ǉ����Ă����D
	 */
	RobotMAV();
	RobotMAV(std::string directoryPath, std::string fileName);

	/**
		@brief ���s���̓���
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
		@brief ���ׂĂ�Arbiter�����s����
	 */
	virtual void ProcessArbiters();
protected:
	/**
		@brief Module�̓o�^�Ȃǂ��s�Ȃ��D
		Constructor����Ăяo����邱�Ƃ�z��
	 */
	void Initialize();
	/**
		@brief Robot��Color
		�ǂ̃��W���[�����������Ă��邩�ɂ���āC�ω�����
	 */
	float color[3];
	/**
		@brief Module���Ƃ�Color(R,G,B)
		modColor[module][r/g/b]
	 */
	float modColor[3][3];
	/**
		@brief Layer�̐�
	 */
	int numOfLayers;
};

#endif	//_Robot_MAV_H_