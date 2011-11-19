#ifndef Constants_H_
#define Constants_H_

///Fieldの長さ
#define LENGTH			100

///Field上の属性とその対応値(Hash)
#define OUTOFAREA		-1
#define NORMAL			0
#define ONSTART			1
#define ONGOAL			2
#define ONCHARGER		3
///視野の長さ (自分との相対位置-5から5まで)
#define RANGEVISION		11

///バッテリーの消耗率 point/step
#define BATTLOSS		3

///無信号状態
#define NO_SIGNAL		2.0f

///円周率π : 1.15桁まで (double の有効数字は10進数で16桁未満)
#define PI				3.141592653589793

#endif //Constants_H_