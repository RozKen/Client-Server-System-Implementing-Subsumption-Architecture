#ifndef Constants_H_
#define Constants_H_

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
/*	
	����̉��s��:��������2�ȏ㗣��Ă���΁C��x��1����
	�����Ȃ����{�b�g���m�͂Ԃ���Ȃ�
*/
#define RANGE_DANGER	3.0f
///RangeSensor�̑���������p��30�x����
#define RANGE_DEG		30.0
///RangeSensor�̑���������p��12 (360 / RANGE_DEG) ����
#define RANGE_DIV		12

///�o�b�e���[�̏��՗� point/step
#define BATTLOSS		3.0
#define MAX_BAT			100.0

///���M�����	�e�X�g�̂��߁C�b��I��0.0f�Ƃ��Ă���D
#define NO_SIGNAL		0.0f

///�~������ : 1.15���܂� (double �̗L��������10�i����16������)
#define PI				3.141592653589793

///Start�n�_�̍��W
#define START_X			50.0f
#define START_Y			0.0f

///��x�̓����鋗��
#define MAX_DRIVE		1.0f

#endif //Constants_H_