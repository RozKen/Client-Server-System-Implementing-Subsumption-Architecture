#ifndef Constants_H_
#define Constants_H_

/**
	NOW MODIFYING the meaning of SUPPRESSOR
	If using normal suppressor, Comment out this.
 */
#define INVERSE_SUPPRESSOR

//削除予定
#define LENGTH				100
///Fieldの一辺(Fieldは正方形)
#define FIELD_SIZE			100
///Sensorの有効な範囲のCell数: マンハッタン距離で3
#define MAX_AREA			25
///Hashデータが持つ最大index ( > MAX_AREA )
#define HASH_MAX			25

///Field上の属性とその対応値(Hash)
#define OUTOFAREA		-1
#define NORMAL			0
#define ONSTART			1
#define ONGOAL			2
#define ONCHARGER		3
#define ROBOTEXIST		4
///全体における障害物の存在確率
#define P_BARRIER		0.03
///WANDERが発火する確率
#define P_WANDER		0.03

/*	
	視野の奥行き:自分から2以上離れていれば，一度に1しか
	動かないロボット同士はぶつからない
*/
#define RANGE			2		//RANGE = (int)ceil(RANGE_DANGER);
#define RANGE_DANGER	2.0f
///RangeSensorの走査する方角は30度刻み
#define RANGE_DEG		30.0
///RangeSensorの走査する方角は12 (360 / RANGE_DEG) 方向
#define RANGE_DIV		12

///バッテリーの消耗率 point/step
#define BAT_LOSS		3.0
#define BAT_GAIN		2.0
#define MAX_BAT			100.0

///無信号状態	テストのため，暫定的に0.0fとしている．
#define NO_SIGNAL		0.0f

///円周率π : 1.15桁まで (double の有効数字は10進数で16桁未満)
#define PI				3.141592653589793

///Start地点の座標
#define START_X			50.0
#define START_Y			0.0
/*
	Start地点の近傍と見なすところ．
	<ul>
		<li>BatteryがChargeされる</li>
		<li>指令からの無線が届く</li>
	</ul>
 */
#define START_R			20.0

///一度の動ける距離
#define MAX_DRIVE		1.0f

///WorldをRunするInterval [millisecond]
#define TIME_STEP		300.0

#endif //Constants_H_