#ifndef _Cont_Arbitrate_Destination_HPP_
#define _Cont_Arbitrate_Destination_HPP_

#include "SAModule.h"

/**
	@class ContArbitrateDestination
	@brief Mission : 探索場所の方向が，他のロボットと同じになるようにする
	<h1>Inputs</h1>
	<ul>
		<li>Input0 : posXCAd</li>
		<li>Input1 : posYCAd</li>
	</ul>
	<h1>Outputs</h1>
	No Outputs
	@author Kenichi Yorozu
	@date 16th December 2011
	@sa SAModule
	@sa ContExplore
 */
class ContArbitrateDestination : public SAModule {
public:
	/**
		@brief Default Constructor
		InputやOutputなどを追加していく．
		ContExploreのIBoardを用いるため，iBoardIndexを設定
		@sa ContExplore
	 */
	ContArbitrateDestination();
	/**
		@brief 実行時の動作
			<ul>
				<li>
					自身のExploreのDestinationが他のRobotと
					異なる方向にあるとき，DestinationをNO_SIGNALとする
				</li>
				<li>
					そうでないときは出力をNO_SIGNALとする
				</li>
			</ul>
	 */
	virtual void Run();
};
#endif	//_Cont_Arbitrate_Destination_HPP_