#ifndef	_Cont_Spread_HPP_
#define	_Cont_Spread_HPP_

#include "SAModule.h"

/**
	@class ContSpread
	@brief Mission : RobotŠÔ‚Ì‹——£‚ğ“K“–‚É•Û‚Â
	<h1>Inputs</h1>
	<ul>
		<li>Input0: posXCSp: current Robot Position - X</li>
		<li>Input1: posYCSp: current Robot Position - Y</li>
		<li>Input2: Robot0XCSp : Robot[0]->posX</li>
		<li>Input3: Robot0YCSp : Robot[0]->posY</li>
		<li>Input4: Robot1XCSp : Robot[1]->posX</li>
		<li>Input5: Robot1YCSp : Robot[1]->posY</li>
		<li>Input6: Robot2XCSp : Robot[2]->posX</li>
		<li>Input7: Robot2YCSp : Robot[2]->posY</li>
		<li>Input8: Robot3XCSp : Robot[3]->posX</li>
		<li>Input9: Robot3YCSp : Robot[3]->posY</li>
		<li>Input10: Robot4XCSp : Robot[4]->posX</li>
		<li>Input11: Robot4YCSp : Robot[4]->posY</li>
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
		Input‚âOutput‚È‚Ç‚ğ’Ç‰Á‚µ‚Ä‚¢‚­.
	 */
	ContSpread();

	/**
		@brief Às‚Ì“®ì.
		‘¼‚ÌRobot‚Æ‚Ì‹——£‚ğˆê’è‚É•Û‚Â‚æ‚¤ˆÚ“®‚ğw¦‚·‚é
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
	int countNumberOfRobots();

	float calcStrength(float distance);
#ifdef	IMPORTANCE_BASED
	float computeImportance(float distance, int i);
#endif	//IMPORTANCE_BASED
};

#endif	//_Cont_Spread_HPP_