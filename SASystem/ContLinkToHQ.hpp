#ifndef _Cont_Link_To_HQ_HPP_
#define	_Cont_Link_To_HQ_HPP_

#include "SAModule.h"
#include "Random.hpp"

/**
	@class ContLinkToHQ
	@brief Mission: 司令部との連絡経路を確保する制御器 Link to Headquaters
	<h1>Inputs</h1>
	<ul>
		<li>Input0 : posXCLTHQ : 現在位置(X座標)</li>
		<li>Input1 : posYCLTHQ : 現在位置(Y座標)</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : dXCLTHQ : 動きの指示(X座標)</li>
		<li>Output1 : dYCLTHQ : 動きの指示(Y座標)</li>
	</ul>
	<h1>iBoards</h1>
	<ul>
		<li>iBoard0 : iHop : 司令部へ到達するまでに経由するRobotの数</li>
	</ul>
	<h1>Others</h1>
	<ul>
		<li>Using (RobotUGV *)relative_root which data is stored on RobotUGV : setRelativeRoot, getRelativeRoot</li>
	</ul>
 */
class ContLinkToHQ : public SAModule{
public:
	/**
		@brief Default Constructor
		Input, Outputなどを追加していく．
	 */
	ContLinkToHQ();

	/**
		@brief 実行時の動作
			<ul>
				<li>hop = NO_SIGNALの時</li>
				<ul>
					<li>近くにhop >= 0 がいたら，それをrelative_rootとする</li>
					<li>いなければ，司令部へ向かう(START_X, START_Y)</li>
				</ul>
				<li>hop != NO_SIGNALの時</li>
				<ul>
					<li> hop == 0のとき，司令部との距離を確認して，繋がっているか，確認</li>
					<li>そうでないとき</li>
					<ul>
						<li>relative_rootのhop > this->hop なら，hop = NO_SIGNALとし，新たなrelative_rootを探す</li>
						<li>そうでないときthis->hop = relative_root->hop + 1とする</li>
						<li>時々，relative_rootの代替案があれば，そっちに乗り換えたりもする</li>
					</ul>
				</ul>
			</ul>
		@sa SAModule::Run
	 */
	virtual void Run();
protected:
	/**
		@brief HeadquarterへのRouteを探す
	 */
	bool findHQ();
	/**
		@brief hopとrelativeRootを更新する
		@return true : ちゃんとつながっている, false : START地点へ戻れ
	 */
	bool update();
	/**
		@brief Random Generator. relative_rootの代替案を探すかどうかを決める際に利用する
	 */
	Random<boost::uniform_real<> > rand;
};

#endif	//_Cont_Link_To_HQ_HPP_