#ifndef _Cont_Explore_HPP_
#define _Cont_Explore_HPP_

#include "SAModule.h"
/**
	@class ContExplore
	@brief Mission : 探索していない場所へ行こうとする制御器
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
					radMapやgeoMapのデータがない(NO_DATA_ON_FIELD)ところを
					innerMapから探し，そこを目指して動く
				</li>
				<li>
					すでに目的地が設定されている場合は，新規に探さず，
					そこを目指して動く
				</li>
				<li>
					NO_DATA_ON_FIELDがない場合や，NO_DATA_ON_FIELDが自分の位置の時は
					出力をNO_SIGNALとする
				</li>
			</ul>
		@sa geoMap
		@sa radMap
	 */
	virtual void Run();
	/**
		@brief 新たに目的地を定める
	 */
	void DecideDestination();
protected:
	///目的地の座標
	int destination[2];
};

inline ContExplore::ContExplore(){
	this->addOutput("dXCExp");
	this->addOutput("dYCExp");

	destination[0] = NO_DATA_ON_FIELD;
	destination[1] = NO_DATA_ON_FIELD;
}

#endif	//_Cont_Explore_HPP_