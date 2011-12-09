#ifndef _Cont_Explore_HPP_
#define _Cont_Explore_HPP_

#include "SAModule.h"
/**
	@class ContExplorer
	@brief 
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
		radMapやgeoMapのデータがないところを目指して動く
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