#ifndef _Constants_H_
#define _Constants_H_

//ContConnect��ContExplore�����Ⴂ�D��x�ɂ���Ƃ��錾����
//#define SWAP_CCCE

//Robot��, Robot-World�ԏ�񏈗��̒x�����l������ꍇ�C�錾����
//#define CONSIDER_DELAY

//Importance-Based�ł��Ƃ��錾
#define IMPORTANCE_BASED
#ifdef IMPORTANCE_BASED
#define IMPORTANCE_POWER	2
#define VERY_IMPORTANT		100.0f
#endif

/**
	NOW MODIFYING the meaning of SUPPRESSOR
	If using normal suppressor, Comment out this.
 */
#ifndef	IMPORTANCE_BASED
#define INVERSE_SUPPRESSOR
#endif

#define NUM_ROBOT			10

//�폜�\��
#define LENGTH				100
///Field�̈��(Field�͐����`)
#define FIELD_SIZE			100
/**
	@brief Field1�}�X���̒��� [m]
	@sa WIFI_REACH
 */
#define FIELD_SCALE			1
/**
	@brief 1 step ���̎��Ԃ̒��� [sec]
	Unmanned Ground Vehicle�̑����� 1 m/s��z��
 */
#define TIME_SCALE			10
///Sensor�̗L���Ȕ͈͂�Cell��: �}���n�b�^��������3
#define MAX_AREA			25
///Hash�f�[�^�����ő�index ( > MAX_AREA )
#define HASH_MAX			25

///Field��̑����Ƃ��̑Ή��l(Hash)
#define NO_DATA_ON_FIELD	-99
#define OUTOFAREA		-1
#define NORMAL			0
#define ONSTART			1
#define ONGOAL			2
#define ONCHARGER		3
#define ROBOTEXIST		4
///�S�̂ɂ������Q���̑��݊m��
#define P_BARRIER		0.05		//0.05

/////////ContAvoid////////////
///Avoid�̎��́CMaxSpeed��0.3�{�Ői��.
#define SPEED_DELAY		0.3

/////////ContAlive/////////////
///Battery���Ⴂ�Ɣ��f���邵�����l
#define BATTERY_LOW		0.2

/////////ContWander/////////////
///WANDER�����΂���m��
#define P_WANDER		0.1

/////////SenseRange/////////////
/*	
	����̉��s��:��������2�ȏ㗣��Ă���΁C��x��1����
	�����Ȃ����{�b�g���m�͂Ԃ���Ȃ�
*/
#define RANGE			4		//RANGE = (int)ceil(RANGE_DANGER);
#define RANGE_DANGER	4.0f
///RangeSensor�̑���������p��30�x����
#define RANGE_DEG		30.0
///RangeSensor�̑���������p��12 (360 / RANGE_DEG) ����
#define RANGE_DIV		12

//////////SenseRadiation/////////////
///���ː��ʍő�̃|�C���g�̐��̍ŏ��l
#define MIN_RAD_POINT	5
///���ː��ʍő�̃|�C���g�̐��̍ő�l
#define MAX_RAD_POINT	15
/**
	@brief ���ː��ʂ̍ő�l [mSv]
	<ul>
		<li>6000mSv�𒴂���ƈ��̔픚�Ŏ��S�Ɍq����</li>
		<li>500mSv���x�ł͈����x�ł́C�u�w�I�ɁC��`�I�e���̐S�z�͂Ȃ�</li>

	</ul>
	@sa <a href="http://homepage3.nifty.com/anshin-kagaku/anshin_level.html">���ː��̌��N���x���Ɗ댯���x��</a>
 */
#define MAX_RAD_VALUE	10000.0f

//////////SenseNet///////////////
/**
	@brief Wifi�̐ڑ��͈�:100 [m]�Ɛݒ肷��=>1�}�X��5m�ƂȂ�
	<ul>
		<li>Indoor : 70m</li>
		<li>Outdoor : 250m</li>
	</ul>
	@sa <a href="http://en.wikipedia.org/wiki/IEEE_802.11n">IEEE 802.11n-2009 - Wikipedia (English)</a>
	@sa <a href="http://making.ti-da.net/e3166838.html">Wi-Fi�i����LAN�j�̓d�g���B�������AiPhone�Ōv�����Ă݂��I</a>
 */
#define WIFI_REACH		20.0f			//50.0f
/**
	@brief Wifi�̐ڑ����؂ꂻ�����Ɣ��f����̂ɗ��p����D
	WIFI_REACH * WIFI_WEAK�̋����ɒB������CContConnect�쓮
 */
#define WIFI_WEAK		0.9f
///LinkToHQ�Ƃ̐ڑ��͂�苭���m�ۂ���
#define WIFI_WEAK_HQ	0.8f
///Wifi�̐ڑ����S�ւƈړ����闦
#define WIFI_BALANCE	0.0f
///Wifi�Őڑ����郍�{�b�g�̐�
#define WIFI_CONNECT	5

/////////ContSpread/////////
///����Robot�ƕۂ��������ϋ���
#define WIFI_NEUTRAL	0.6f
///��������NEUTRAL�ł���ƍl������ߖT(0.0 - 1.0)
#define WIFI_NEUTRAL_AROUND		0.2f

/////////ContLinkToHQ/////////
#define P_RECONNECT		0.0f			//0.01f

///�o�b�e���[�̏��՗� point/step
/**
	@brief Battery Specification
	<table>
	<tr><th>Name</th><td>Carbon Pro 6400mAh 90C 14,8V (Deans plug)</td></tr>
	<tr><th>Number of Cells</th><td>4</td></tr>
	<tr><th>Voltage</th><td> 3.7 x 4 = 14.8 [V]</td></tr>
	<tr><th>Discharge</th><td>90C</td></tr>
	<tr><th>Charge</th><td>5C</td></tr>
	<tr><th>Maximum Power Output</th><td>8325 [W] = 14.8 [V] * 6.4 [Ah] * 90C</td></tr>
	<tr><th>Maximum Power Input</th><td>473.6 [W] = 14.8 [V] * 6.4 [Ah] * 5C</td></tr>
	<tr><th>Weight</th><td>449.3</td></tr>
	</table>
	@sa http://www.teamorion.com/carbon-pro-6400mah-90c-14-8v-deans-plug-en.html
 */
/**
	@brief Motor Specification
	���[�^�[�͉E����2��
	�g���N�̊m�F���K�v
	�{���́CBrushless Motor�̕����ǂ������D
	<table>
		<tr><th>Model</th><td>�}�u�` FC-280PC-22125</td></tr>
		<tr><th>�d��</th><td>12 [V] Constant</td></tr>
		<tr><th>�d��</th><td>0.71 [A]</td></tr>
		<tr><th>�g���N</th><td>4.76 [mN�Em]</td></tr>
		<tr><th>�o��</th><td>5.52 [W]</td></tr>
		<tr><th></th><td></td></tr>
		<tr><th></th><td></td></tr>
	</table>
 */
#ifdef CONSIDER_DELAY
#define BAT_LOSS		3.68
#define BAT_GAIN		157.9
#else
#define BAT_LOSS		11.04
#define BAT_GAIN		473.6
#endif
#define MAX_BAT			900			//142.1

////ContArbitrateDestination
///Destination�������Ɣ��f����ۂ�threshold
#define DEST_FAR		5.0
///���̂��̂������ʂ̕����֐i��ł���Ɣ��f����ۂ�threshold
#define DEST_STRONG_WRONG	1.0

////ContSmartAlive
///�]�T�������Ė߂邽��,�����ɂ�����W��
#define SURPLUS			3.0f

///���M�����
#define NO_SIGNAL		-99.0f
#define	DISABLED		-999.0f

///�~������ : 1.15���܂� (double �̗L��������10�i����16������)
#define PI				3.141592653589793

///Start�n�_�̍��W
#define START_X			50.0
#define START_Y			5.0
/*
	Start�n�_�̋ߖT�ƌ��Ȃ��Ƃ���D
	<ul>
		<li>Battery��Charge�����</li>
	</ul>
 */
#define START_R			10.0

///��x�̓����鋗��
#ifdef CONSIDER_DELAY
#define MAX_DRIVE		0.3333f
#else
#define MAX_DRIVE		1.0f
#endif	//CONSIDER_DELAY

///World��Run����Interval [millisecond]
#ifdef CONSIDER_DELAY
#define TIME_STEP		33.33
#else
#define TIME_STEP		100.0
#endif	//CONSIDER_DELAY

#endif //_Constants_H_