#ifndef Constants_H_
#define Constants_H_

/**
	NOW MODIFYING the meaning of SUPPRESSOR
	If using normal suppressor, Comment out this.
 */
#define INVERSE_SUPPRESSOR

#define NUM_ROBOT			5

//削除予定
#define LENGTH				100
///Fieldの一辺(Fieldは正方形)
#define FIELD_SIZE			100
/**
	@briefField1マス分の長さ [m]
	@sa WIFI_REACH
 */
#define FIELD_SCALE			1
/**
	@brief 1 step 分の時間の長さ [sec]
	Unmanned Ground Vehicleの速さが 1 m/sを想定
 */
#define TIME_SCALE			1
///Sensorの有効な範囲のCell数: マンハッタン距離で3
#define MAX_AREA			25
///Hashデータが持つ最大index ( > MAX_AREA )
#define HASH_MAX			25

///Field上の属性とその対応値(Hash)
#define NO_DATA			-99
#define OUTOFAREA		-1
#define NORMAL			0
#define ONSTART			1
#define ONGOAL			2
#define ONCHARGER		3
#define ROBOTEXIST		4
///全体における障害物の存在確率
#define P_BARRIER		0.05		//0.05
///WANDERが発火する確率
#define P_WANDER		0.1

/*	
	視野の奥行き:自分から2以上離れていれば，一度に1しか
	動かないロボット同士はぶつからない
*/
#define RANGE			3		//RANGE = (int)ceil(RANGE_DANGER);
#define RANGE_DANGER	3.0f
///RangeSensorの走査する方角は30度刻み
#define RANGE_DEG		30.0
///RangeSensorの走査する方角は12 (360 / RANGE_DEG) 方向
#define RANGE_DIV		12

///放射線量最大のポイントの数の最小値
#define MIN_RAD_POINT	1
///放射線量最大のポイントの数の最大値
#define MAX_RAD_POINT	10
/**
	@brief 放射線量の最大値 [mSv]
	<ul>
		<li>6000mSvを超えると一回の被爆で死亡に繋がる</li>
		<li>500mSv程度では一回程度では，疫学手金，遺伝的影響の心配はない</li>

	</ul>
	@sa <a href="http://homepage3.nifty.com/anshin-kagaku/anshin_level.html">放射線の健康レベルと危険レベル</a>
 */
#define MAX_RAD_VALUE	10000.0f

/**
	@brief Wifiの接続範囲:100 [m]と設定する=>1マスが5mとなる
	<ul>
		<li>Indoor : 70m</li>
		<li>Outdoor : 250m</li>
	</ul>
	@sa <a href="http://en.wikipedia.org/wiki/IEEE_802.11n">IEEE 802.11n-2009 - Wikipedia (English)</a>
	@sa <a href="http://making.ti-da.net/e3166838.html">Wi-Fi（無線LAN）の電波到達距離を、iPhoneで計測してみた！</a>
 */
#define WIFI_REACH		20.0f			//50.0f
/**
	@brief Wifiの接続が切れそうだと判断するのに利用する．
	WIFI_REACH * WIFI_WEAKの距離に達したら，ContConnect作動
 */
#define WIFI_WEAK		0.9f
///Wifiの接続中心へと移動する率
#define WIFI_BALANCE	0.1f
///Wifiで接続するロボットの数
#define WIFI_CONNECT	5

///バッテリーの消耗率 point/step
#define BAT_LOSS		1.0
#define BAT_GAIN		2.0
#define MAX_BAT			100.0

///無信号状態
#define NO_SIGNAL		-99.0f

///円周率π : 1.15桁まで (double の有効数字は10進数で16桁未満)
#define PI				3.141592653589793

///Start地点の座標
#define START_X			50.0
#define START_Y			15.0
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