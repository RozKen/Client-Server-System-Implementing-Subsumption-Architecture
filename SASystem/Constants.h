#ifndef Constants_H_
#define Constants_H_

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
///����̒��� (�����Ƃ̑��Έʒu-5����5�܂�)
#define RANGEVISION		11

///�o�b�e���[�̏��՗� point/step
#define BATTLOSS		3

///���M�����	�e�X�g�̂��߁C�b��I��0.0f�Ƃ��Ă���D
#define NO_SIGNAL		0.0f

///�~������ : 1.15���܂� (double �̗L��������10�i����16������)
#define PI				3.141592653589793

/**
	@brief index���w������x, y���W�𓾂邽�߂�hash[x/y][index]
 */
int hash[2][HASH_MAX] = {
	{0,0,1,0,-1,0,1,2,1,0,-1,-2,-1,0,1,2,3,2,1,0,-1,-2,-3,-2,-1},
	{0,1,0,-1,0,2,1,0,-1,-2,-1,0,1,3,2,1,0,-1,-2,-3,-2,-1,0,1,2}
};

#endif //Constants_H_