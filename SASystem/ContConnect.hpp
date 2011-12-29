#ifndef _Cont_Connect_HPP_
#define _Cont_Connect_HPP_

#include "SAModule.h"
#include <string.h>
#include "Random.hpp"

/**
	@class ContConnect
	@brief Mission : �߂��ɂ��钇�Ԃƌq���낤�Ƃ��鐧���
	<h1>Inputs</h1>
	<ul>
		<li>Input0: Robot0XCC : Robot[0]->posX</li>
		<li>Input1: Robot0YCC : Robot[0]->posY</li>
		<li>Input2: Robot1XCC : Robot[1]->posX</li>
		<li>Input3: Robot1YCC : Robot[1]->posY</li>
		<li>Input4: Robot2XCC : Robot[2]->posX</li>
		<li>Input5: Robot2YCC : Robot[2]->posY</li>
		<li>Input6: Robot3XCC : Robot[3]->posX</li>
		<li>Input7: Robot3YCC : Robot[3]->posY</li>
		<li>Input8: Robot4XCC : Robot[4]->posX</li>
		<li>Input9: Robot4YCC : Robot[4]->posY</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCC: delta X - differential of Motion X</li>
		<li>Output1: dYCC: delta Y - differential of Motion Y</li>
	</ul>
	@sa SenseNet
	@author Kenichi Yorozu
	@date 9th December 2011
 */
class ContConnect : public SAModule{
public:
	/**
		@brief Default Constructor
		Input��Output�Ȃǂ�ǉ����Ă���
	 */
	ContConnect();
	/**
		@brief ���s���̓���
		<ul>
			<li>Network���؂ꂻ����Robot������΁C������֌�����</li>
			<li>�����łȂ��ꍇ�C���X�ߖT�̃��{�b�g�̐^�񒆂ɐw���</li>
			<li>����ȊO��NO_SIGNAL</li>
		</ul>
		Network���؂ꂻ�� := WIFI_REACH * WIFI_WEAK�̋���
		���X := WIFI_BALANCE
		@sa SAModule::Run()
		@sa WIFI_REACH
		@sa WIFI_WEAK
		@sa WIFI_BALANCE
	 */
	virtual void Run();
protected:
	/**
		@brief Random Generator.WIFI_BALANCE�֘A�ŗ��p
	 */
	Random<boost::uniform_real<> > rand;
};

inline ContConnect::ContConnect() : rand(0.0, 1.0){
	std::string head = "Robot";
	std::string foot = "CC";
	//Add Inputs
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
		std::string name = head;
		name.append(intToString( i / 2 ) );
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addInput(name);
	}

	head = "d";
	//Add Outputs
	for(int i = 0; i < 2; i++){
		std::string name = head;
		if( i % 2 == 0){
			name.append("X");
		}else{
			name.append("Y");
		}
		name.append(foot);
		this->addOutput(name);
	}
}

inline void ContConnect::Run(){
	//�o�͐M���F��{NO_SIGNAL
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED

	//�؂ꂻ���Ȃ̂���������C�������̕��ցD
	//�؂ꂻ���Ȃ��̂̂����C��ԋ߂�Robot�̕��֌�����	//for Loop���t�ɂ��Ă���.
	for(int i = WIFI_CONNECT - 1; i >= 0 ; i--){
		float dx = this->getInput(i * 2);
		float dy = this->getInput(i * 2 + 1);
		float distance = this->norm(dx, dy);
		if(distance > WIFI_REACH * WIFI_WEAK && dx != NO_SIGNAL && dy != NO_SIGNAL){
			signalX = (float)MAX_DRIVE * dx / distance;
			signalY = (float)MAX_DRIVE * dy / distance;
#ifdef	IMPORTANCE_BASED
			this->importance = this->calcImportance(WIFI_CONNECT - 1 - i);
#endif	//IMPORTANCE_BASED
		}
	}

	//�؂ꂻ���Ȃ��̂��Ȃ�������C���X�o�����X���Ƃ�
	if(signalX == NO_SIGNAL && signalY == NO_SIGNAL){
		float random = rand();
		if(random < WIFI_BALANCE){
			signalX = 0.0f;
			signalY = 0.0f;
			for(int i = 0; i < WIFI_CONNECT; i++){
				signalX += this->getInput( i * 2 );
				signalY += this->getInput( i * 2 + 1 );
			}
			float distance = this->norm(signalX, signalY);
			if(distance != 0.0f){
				signalX /= distance;
				signalY /= distance;
			}
			signalX *= (float)MAX_DRIVE;
			signalY *= (float)MAX_DRIVE;
#ifdef	IMPORTANCE_BASED
			this->importance = this->calcImportance(1.0f - random / WIFI_BALANCE);
#endif	//IMPORTANCE_BASED
		}
	}

	//�o��
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}
	
#endif	_Cont_Connect_HPP_