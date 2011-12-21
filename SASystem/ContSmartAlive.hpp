#ifndef _Cont_Smart_Alive_HPP_
#define _Cont_Smart_Alive_HPP_

#include "SAModule.h"

/**
	@class ContSmartAlive
	@brief Mission : 充電に関して、よりスマートな動きを発現させる.
	<h1>Inputs</h1>
	<ul>
		<li>Input0 : posXCS</li>
		<li>Input1 : posYCS</li>
		<li>Input2 : batCS</li>
		<li>Input3 : onBatChCS</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0 : dXCS</li>
		<li>Output1 : dYCS</li>
	</ul>
	<h1>iBoard</h1>
	<ul>
		<li>iBoard0 : iChargeF ; Charge Flag : 1 = Stop and Charge, 0 = Other</li>
	</ul>
	@author Kenichi Yorozu
	@date 18th December 2011
	@sa SAModule
 */

class ContSmartAlive : public SAModule{
public:
	/**
		@brief Default Constructor
		InputやOutputなどを追加していく．
	 */
	ContSmartAlive();
	/**
		@brief 実行時の動作
			<ul>
				<li>Battery Level < 50% かつ ON_BATTERYの時は、100%になるまで充電する</li>
				<li>もっとも近いBattery Chargerまで移動できるぎりぎりのBattery Levelになったら，戻る</li>
				<li>そうでないときは出力をNO_SIGNALとする</li>
			</ul>
		@sa SAModule::Run
	 */
	virtual void Run();

protected:
	/**
		@brief 見つけた，近傍のバッテリー場所
	 */
	float nearestCharger[2];
	/**
		@brief 見つけた場所との距離
	 */
	float distance;
	/**
		@brief 充電場所のうち，もっとも近い場所があるかどうか，探す．
		あれば，その座標と距離をそれぞれ
		nearestChargerとdistanceに格納する
		@sa nearestCharger
	 */
	bool findNearestCharger();
};
#endif	//_Cont_Smart_Alive_HPP_
