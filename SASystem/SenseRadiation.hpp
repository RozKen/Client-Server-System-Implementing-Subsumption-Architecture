#ifndef _Sense_Radiation_HPP_
#define _Sense_Radiation_HPP_

#include "SAModule.h"

/**
	@class SenseRadiation
	@brief 近傍の放射線量を検知するセンサ
	<h1>fBoard</h1>
	<ul>
		<li>fBoard 0 : fRad[0] : Radiation Value at hash[0][0], hash[1][0]</li>
		<li>fBoard i : fRad[i] : Radiation Value at hash[0][i], hash[1][i]</li>
		<li>fBoard24 : fRad[MAX_AREA - 1] : Radiation Value at hash[0][25], hash[1][25]</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output 0 : radiation[0] : Radiation Value at hash[0][0], hash[1][0]</li>
		<li>Output i : radiation[i] : Radiation Value at hash[0][i], hash[1][i]</li>
		<li>Output24 : radiation[MAX_AREA - 1] : Radiation Value at hash[0][25], hash[1][25]</li>
	</ul>
	@author Kenichi Yorozu
	@date 14th December 2011
 */
class SenseRadiation : public SAModule{
public:
	/**
		@brief Default Constructor
		Outputなどを追加していく.
		Sensorなので，Inputはない．
	 */
	SenseRadiation();
	/**
		@brief 実行時の動作
		@sa SAModule::Run()
	 */
	virtual void Run();
};

inline SenseRadiation::SenseRadiation(){
	for(int i = 0; i < MAX_AREA; i++){
		addFBoard("fRad[" + intToString(i) + "]");
		addOutput("radiation[" + intToString(i) + "]");
	}
}

inline void SenseRadiation::Run(){
	for(int i = 0; i < MAX_AREA; i++){
		//fBoardの値をOutput
		setOutput(i, this->getFBoard(i));
	}
}

#endif	//_Sense_Radiation_HPP_