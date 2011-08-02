#ifndef _SAServer_H_
#define _SAServer_H_

#define	NUM_MODULES	9		//Module�̐�

class SAModule;	//header���ŕϐ���錾���邽�߂ɁCclass��錾
class EnvUpdater;
/**
	@class SAServer
	@brief ���ׂĂ�Module�̐ڑ��֌W�CInhibition, Suppression�֌W��ێ����C
	����ɉ������M���̌�����Ǘ�����N���X
	1Clock���Ƃɂ��ׂĂ�Module�𓮂����C���ꂼ��̏o�͂���ɁC
	���̓��͂����߂Ă���
	@sa SAModule
 */
class SAServer{
public:
	/**
		@brief Construct and Run SAServer
		<ol>
			<li>Initialize()</li>
		</ol>
	*/
	SAServer();
	/**
		@brief ��N���b�N�������i�߂�
		<ol>
			<li>Run();</li>
			<li>Inhibit();</li>
			<li>Suppress();</li>
		</ol>
	 */
	void Process();
protected:
	/**
		@brief Initialize States
	*/
	void Initialize();
	/**
		@brief Server�ɓo�^����Ă��邷�ׂĂ�Module��Run����
		���̑��ɁC���݂͗���(LM, RM)��speed����ɁC�ʒu�ƌ������Z�o���C
		//�������Z���T�[�ɑ���D��������
	*/
	void Run();
	/**
		@brief ���w��Module����̏o�͂�}������.
		<ol>
			<li>inhibited[]�̊e�v�f����1������</li>
			<li>inhibited[]�̒l��-1�ł�����̂́C0�ɒ����C</li>
			<li>probInhibition[][]�Ɋ�Â���inhibited[]���X�V����</li>
			<li>inhibited[]�̒l�����ł���v�f��inhibit����</li>
		</ol>
		@sa inhibited[]
		@sa probInhibition[][]
	*/
	void Inhibit();
	/**
		@brief ���w��Module�ւ̓��͂�}������.
		<ol>
			<li>suppressed[]�̊e�v�f����1������</li>
			<li>suppressed[]�̒l��-1�ł�����̂́C0�ɒ����C</li>
			<li>probSuppression[][]�Ɋ�Â���suppressed[]���X�V����</li>
			<li>suppressed[]�̒l�����ł���v�f��suppress����</li>
		</ol>
		@sa suppressed[]
		@sa probSuppression[][]
	*/
	void Suppress();

	/**
		@brief ����Module�ɑ�����M��
		outbox ---[inhibit]-->connector---[suppress]--><b>inbox</b>-->Modules
		@sa outbox
		@sa connector
	*/
	float inbox[NUM_MODULES];
	/**
		@brief Module���瑗���Ă����M��
		<b>outbox</b> ---[inhibit]-->connector---[suppress]-->inbox-->Modules
		@sa inbox
		@sa connector
	*/
	float outbox[NUM_MODULES];
	/**
		@brief Connector�𗬂��M��.
		outbox ---[inhibit]--><b>connector</b>---[suppress]-->inbox-->Modules
		@sa outbox
		@sa inbox
	*/
	float connector[NUM_MODULES];

	/**
		@brief Inhibition�̊m���s��
		<table width="200" border="1">
		  <tr>
			<td>&nbsp;</td>
			<td colspan="6">Inferior Layer</td>
		  </tr>
		  <tr>
			<td rowspan="6">Superior Layer</td>
		<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.2</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.3</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.5</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.7</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.2</td><td>0.0</td>
		  </tr>
		</table>
		probInhibition[A][B] -> A inhibits B

		���ʂ�Subsumption Architecture�Ȃ�C�s��ł���K�v�͂Ȃ��D
		����̊K�w��Inhibit����m����m��΂悢����C�z��ŗǂ��͂�
		����ǁC�����K�w�̂��̂�������肷��Ƃ��ɁC�s�񂪕K�v
	*/
	float probInhibition[NUM_MODULES][NUM_MODULES];
	/**
		@brief Suppression�̊m���s��
		<table width="200" border="1">
		  <tr>
			<td>&nbsp;</td>
			<td colspan="6">Inferior Layer</td>
		  </tr>
		  <tr>
			<td rowspan="6">Superior Layer</td>
		<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.2</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.3</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.5</td><td>0.0</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.7</td><td>0.0</td><td>0.0</td>
		  </tr>
		  <tr>
			<td>0.0</td><td>0.0</td><td>0.0</td><td>0.0</td><td>0.2</td><td>0.0</td>
		  </tr>
		</table>
		probSuppression[A][B] -> A suppresses B

		���ʂ�Subsumption Architecture�Ȃ�C�s��ł���K�v�͂Ȃ��D
		����̊K�w��Suppression����m����m��΂悢����C�z��ŗǂ��͂�
		����ǁC�����K�w�̂��̂�������肷��Ƃ��ɁC�s�񂪕K�v
	*/
	float probSuppression[NUM_MODULES][NUM_MODULES];

	/**
		@brief Inhibit���鎞�Ԃ��w�肷��s��D�P�ʂ̓N���b�N
	*/
	int	timeInhibition[NUM_MODULES][NUM_MODULES];
	/**
		@brief Suppress���鎞�Ԃ��w�肷��s��D�P�ʂ̓N���b�N
	*/
	int timeSuppression[NUM_MODULES][NUM_MODULES];

	/**
		@brief Inhibit���ꂽ�܂܂ł���c����
	*/
	int inhibited[NUM_MODULES];
	/**
		@brief Suppress���ꂽ�܂܂ł���c����
	*/
	int suppressed[NUM_MODULES];

	/**
		@brief �Ǘ�����Ă���Module
	*/
	SAModule* modules[NUM_MODULES];

	/**
		@brief �b��I�ɗ��p���Ă����
	*/
	EnvUpdater* env;
};

#endif //_SAServer_H_