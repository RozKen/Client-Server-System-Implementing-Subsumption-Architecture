#ifndef _Cont_Explore_HPP_
#define _Cont_Explore_HPP_

#include "SAModule.h"
/**
	@class ContExplore
	@brief <h1>Mission</h1>: 探索していない場所へ行く
	<h1>Inputs</h1>
		Inputはなし．Robot内部のMapを利用する
	<h1>Outputs</h1>
	<ul>
		<li>dXCExp</li>
		<li>dYCExp</li>
	</ul>
	@author Kencihi Yorozu
	@date 8th December 2011
 */

class ContExplore : public SAModule{
public:
	/**
		@brief Default Constructor
		InputやOutputなどを追加していく．
	 */
	ContExplore();
	/**
		@brief 実行時の動作
			<ul>
				<li>
					radMapやgeoMapのデータがない(NO_DATA)ところを
					innerMapから探し，そこを目指して動く
				</li>
				<li>
					NO_DATAがない場合や，NO_DATAが自分の位置の時は
					出力をNO_SIGNALとする
				</li>
			</ul>
		@sa geoMap
		@sa radMap
	 */
	virtual void Run();
};

inline ContExplore::ContExplore(){
	this->addOutput("dXCExp");
	this->addOutput("dYCExp");
}

#endif	//_Cont_Explore_HPP_