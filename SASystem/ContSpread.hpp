#ifndef	_Cont_Spread_HPP_
#define	_Cont_Spread_HPP_

#include "SAModule.h"

/**
	@class ContSpread
	@brief Mission : Robot�Ԃ̋�����K���ɕۂ�
	<h1>Inputs</h1>
	<ul>
		<li>Input0: posXCSp: current Robot Position - X</li>
		<li>Input1: posYCSp: current Robot Position - Y</li>
		<li>Input2: Robot0XCC : Robot[0]->posX</li>
		<li>Input3: Robot0YCC : Robot[0]->posY</li>
		<li>Input4: Robot1XCC : Robot[1]->posX</li>
		<li>Input5: Robot1YCC : Robot[1]->posY</li>
		<li>Input6: Robot2XCC : Robot[2]->posX</li>
		<li>Input7: Robot2YCC : Robot[2]->posY</li>
		<li>Input8: Robot3XCC : Robot[3]->posX</li>
		<li>Input9: Robot3YCC : Robot[3]->posY</li>
		<li>Input10: Robot4XCC : Robot[4]->posX</li>
		<li>Input11: Robot4YCC : Robot[4]->posY</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCSp: delta X - differential of Motion X</li>
		<li>Output1: dXCSp: delta Y - differential of Motion Y</li>
	</ul>
	@author Kenichi Yorozu
	@date 5th January 2012
 */
class ContSpread : public SAModule{
public:
	/**
		@brief Default Constructor
		Input��Output�Ȃǂ�ǉ����Ă���.
	 */
	ContSpread();

	/**
		@brief ���s���̓���.
		����Robot�Ƃ̋��������ɕۂ悤�ړ����w������
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
	int countNumberOfRobots();

	float calcStrength(float distance);
#ifdef	IMPORTANCE_BASED
	float computeImportance(float distance);
#endif	//IMPORTANCE_BASED
};

#endif	//_Cont_Spread_HPP_