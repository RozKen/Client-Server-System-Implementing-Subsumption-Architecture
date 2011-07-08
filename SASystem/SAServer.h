#ifndef _SAServer_H_
#define _SAServer_H_

#define	NUM_MODULES	3		//Module�̐�

class SAServer{
public:
	/**
		Construct and Run SAServer
		1. Initialize()
		2. While(0){ Run(); Inhibit(); Suppress(); }
	*/
	SAServer();
protected:
	/**
		Initialize States
	*/
	void Initialize();
	/**
		Run all Modules
	*/
	void Run();
	/**
		���w��Module��}������.
		1. inhibited[]�̊e�v�f����1������
		2. inhibited[]�̒l��-1�ł�����̂́C0�ɒ����C
		3. probInhibition[][]�Ɋ�Â���inhibited[]���X�V����
		4. inhibited[]�̒l�����ł���v�f��inhibit����
		@sa inhibited[]
		@sa probInhibition[][]
	*/
	void Inhibit();
	/**
		���w��Module��}������.
		1. suppressed[]�̊e�v�f����1������
		2. suppressed[]�̒l��-1�ł�����̂́C0�ɒ����C
		3. probSuppression[][]�Ɋ�Â���suppressed[]���X�V����
		4. suppressed[]�̒l�����ł���v�f��suppress����
		@sa suppressed[]
		@sa probSuppression[][]
	*/
	void Suppress();

	/**
		����Module�ɑ�����M��
	*/
	float inbox[NUM_MODULES];
	/**
		Module���瑗���Ă����M��
	*/
	float outbox[NUM_MODULES];

	/**
		Inhibition�̊m���s��
								Inferior Layer
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0
						0.2, 0.0, 0.0, 0.0, 0.0, 0.0
		Superior Layer	0.0, 0.3, 0.0, 0.0, 0.0, 0.0
						0.0, 0.0, 0.5, 0.0, 0.0, 0.0
						0.0, 0.0, 0.0, 0.7, 0.0, 0.0
						0.0, 0.0, 0.0, 0.0, 0.2, 0.0
		���ʂ�Subsumption Architecture�Ȃ�C�s��ł���K�v�͂Ȃ��D
		����̊K�w��Inhibit����m����m��΂悢����C�z��ŗǂ��͂�
		����ǁC�����K�w�̂��̂�������肷��Ƃ��ɁC�s�񂪕K�v
	*/
	float probIhibition[NUM_MODULES][NUM_MODULES];
	/**
		Suppression�̊m���s��
								Inferior Layer
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0
						0.2, 0.0, 0.0, 0.0, 0.0, 0.0
		Superior Layer	0.0, 0.3, 0.0, 0.0, 0.0, 0.0
						0.0, 0.0, 0.5, 0.0, 0.0, 0.0
						0.0, 0.0, 0.0, 0.7, 0.0, 0.0
						0.0, 0.0, 0.0, 0.0, 0.2, 0.0
		���ʂ�Subsumption Architecture�Ȃ�C�s��ł���K�v�͂Ȃ��D
		����̊K�w��Suppression����m����m��΂悢����C�z��ŗǂ��͂�
		����ǁC�����K�w�̂��̂�������肷��Ƃ��ɁC�s�񂪕K�v
	*/
	float probSuppression[NUM_MODULES][NUM_MODULES];

	/**
		Inhibit���ꂽ�܂܂ł���c����
	*/
	int inhibited[NUM_MODULES];
	/**
		Suppress���ꂽ�܂܂ł���c����
	*/
	int suppressed[NUM_MODULES];
}

#endif