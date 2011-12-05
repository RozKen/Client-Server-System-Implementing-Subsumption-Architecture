#ifndef Constants_H_
#define Constants_H_

/**
	NOW MODIFYING the meaning of SUPPRESSOR
	If using normal suppressor, Comment out this.
 */
#define INVERSE_SUPPRESSOR

//�폜�\��
#define LENGTH				100
///Field�̈��(Field�͐����`)
#define FIELD_SIZE			100
///Sensor�̗L���Ȕ͈͂�Cell��: �}���n�b�^��������3
#define MAX_AREA			25
///Hash�f�[�^�����ő�index ( > MAX_AREA )
#define HASH_MAX			25

///Field��̑����Ƃ��̑Ή��l(Hash)
#define OUTOFAREA		-1
#define NORMAL			0
#define ONSTART			1
#define ONGOAL			2
#define ONCHARGER		3
#define ROBOTEXIST		4
///�S�̂ɂ������Q���̑��݊m��
#define P_BARRIER		0.03
///WANDER�����΂���m��
#define P_WANDER		0.03

/*	
	����̉��s��:��������2�ȏ㗣��Ă���΁C��x��1����
	�����Ȃ����{�b�g���m�͂Ԃ���Ȃ�
*/
#define RANGE			2		//RANGE = (int)ceil(RANGE_DANGER);
#define RANGE_DANGER	2.0f
///RangeSensor�̑���������p��30�x����
#define RANGE_DEG		30.0
///RangeSensor�̑���������p��12 (360 / RANGE_DEG) ����
#define RANGE_DIV		12

///�o�b�e���[�̏��՗� point/step
#define BAT_LOSS		3.0
#define BAT_GAIN		2.0
#define MAX_BAT			100.0

///���M�����	�e�X�g�̂��߁C�b��I��0.0f�Ƃ��Ă���D
#define NO_SIGNAL		0.0f

///�~������ : 1.15���܂� (double �̗L��������10�i����16������)
#define PI				3.141592653589793

///Start�n�_�̍��W
#define START_X			50.0
#define START_Y			0.0
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