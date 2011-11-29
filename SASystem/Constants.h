#ifndef Constants_H_
#define Constants_H_

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
/*	
	視野の奥行き:自分から2以上離れていれば，一度に1しか
	動かないロボット同士はぶつからない
*/
#define RANGE_DANGER	3.0f
///RangeSensorの走査する方角は30度刻み
#define RANGE_DEG		30.0
///RangeSensorの走査する方角は12 (360 / RANGE_DEG) 方向
#define RANGE_DIV		12

///バッテリーの消耗率 point/step
#define BATTLOSS		3.0
#define MAX_BAT			100.0

///無信号状態	テストのため，暫定的に0.0fとしている．
#define NO_SIGNAL		0.0f

///円周率π : 1.15桁まで (double の有効数字は10進数で16桁未満)
#define PI				3.141592653589793

///Start地点の座標
#define START_X			50.0f
#define START_Y			0.0f

///一度の動ける距離
#define MAX_DRIVE		1.0f

#endif //Constants_H_