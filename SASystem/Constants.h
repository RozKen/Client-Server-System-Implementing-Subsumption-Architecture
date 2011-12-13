#ifndef Constants_H_
#define Constants_H_

/**
	NOW MODIFYING the meaning of SUPPRESSOR
	If using normal suppressor, Comment out this.
 */
#define INVERSE_SUPPRESSOR

#define NUM_ROBOT			5

//�폜�\��
#define LENGTH				100
///Field�̈��(Field�͐����`)
#define FIELD_SIZE			100
/**
	@briefField1�}�X���̒��� [m]
	@sa WIFI_REACH
 */
#define FIELD_SCALE			1
/**
	@brief 1 step ���̎��Ԃ̒��� [sec]
	Unmanned Ground Vehicle�̑����� 1 m/s��z��
 */
#define TIME_SCALE			1
///Sensor�̗L���Ȕ͈͂�Cell��: �}���n�b�^��������3
#define MAX_AREA			25
///Hash�f�[�^�����ő�index ( > MAX_AREA )
#define HASH_MAX			25

///Field��̑����Ƃ��̑Ή��l(Hash)
#define NO_DATA			-99
#define OUTOFAREA		-1
#define NORMAL			0
#define ONSTART			1
#define ONGOAL			2
#define ONCHARGER		3
#define ROBOTEXIST		4
///�S�̂ɂ������Q���̑��݊m��
#define P_BARRIER		0.05		//0.05
///WANDER�����΂���m��
#define P_WANDER		0.1

/*	
	����̉��s��:��������2�ȏ㗣��Ă���΁C��x��1����
	�����Ȃ����{�b�g���m�͂Ԃ���Ȃ�
*/
#define RANGE			3		//RANGE = (int)ceil(RANGE_DANGER);
#define RANGE_DANGER	3.0f
///RangeSensor�̑���������p��30�x����
#define RANGE_DEG		30.0
///RangeSensor�̑���������p��12 (360 / RANGE_DEG) ����
#define RANGE_DIV		12

///���ː��ʍő�̃|�C���g�̐��̍ŏ��l
#define MIN_RAD_POINT	1
///���ː��ʍő�̃|�C���g�̐��̍ő�l
#define MAX_RAD_POINT	10
/**
	@brief ���ː��ʂ̍ő�l [mSv]
	<ul>
		<li>6000mSv�𒴂���ƈ��̔픚�Ŏ��S�Ɍq����</li>
		<li>500mSv���x�ł͈����x�ł́C�u�w����C��`�I�e���̐S�z�͂Ȃ�</li>

	</ul>
	@sa <a href="http://homepage3.nifty.com/anshin-kagaku/anshin_level.html">���ː��̌��N���x���Ɗ댯���x��</a>
 */
#define MAX_RAD_VALUE	10000.0f

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
///Wifi�̐ڑ����S�ւƈړ����闦
#define WIFI_BALANCE	0.1f
///Wifi�Őڑ����郍�{�b�g�̐�
#define WIFI_CONNECT	5

///�o�b�e���[�̏��՗� point/step
#define BAT_LOSS		1.0
#define BAT_GAIN		2.0
#define MAX_BAT			100.0

///���M�����
#define NO_SIGNAL		-99.0f

///�~������ : 1.15���܂� (double �̗L��������10�i����16������)
#define PI				3.141592653589793

///Start�n�_�̍��W
#define START_X			50.0
#define START_Y			15.0
/*
	Start�n�_�̋ߖT�ƌ��Ȃ��Ƃ���D
	<ul>
		<li>Battery��Charge�����</li>
		<li>�w�߂���̖������͂�</li>
	</ul>
 */
#define START_R			20.0

///��x�̓����鋗��
#define MAX_DRIVE		1.0f

///World��Run����Interval [millisecond]
#define TIME_STEP		300.0

#endif //Constants_H_