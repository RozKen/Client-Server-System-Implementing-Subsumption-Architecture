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
		<li>Output0 : dXCExp</li>
		<li>Output1 : dYCExp</li>
	</ul>
	<h1>iBoard</h1>
	<ul>
		<li>iBoard0 : iDestinationX</li>
		<li>iBoard1 : iDestinationY</li>
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
	/**
		@brief 現在の目的地のX座標を得る
		@return 現在の目的地のX座標
		@sa destination
	 */
	int getDestinationX() const;
	/**
		@brief 現在の目的地のY座標を得る
		@return 現在の目的地のY座標
		@sa destination
	 */
	int getDestinationY() const;
protected:
};

inline ContExplore::ContExplore(){
	this->addOutput("dXCExp");
	this->addOutput("dYCExp");

	this->addIBoard("iDestinationX");
	this->addIBoard("iDestinationY");
}

inline int ContExplore::getDestinationX() const{
	return this->getIBoard(0);
}

inline int ContExplore::getDestinationY() const{
	return this->getIBoard(1);
}

#endif	//_Cont_Explore_HPP_