#ifndef _SAServer_H_
#define _SAServer_H_

#define	NUM_MODULES	7		//Module�̐�

class SAModule;	//header���ŕϐ���錾���邽�߂ɁCclass��錾
/**
	���ׂĂ�Module�̐ڑ��֌W�CInhibition, Suppression�֌W��ێ����C
	����ɉ������M���̌�����Ǘ�����N���X
	1Clock���Ƃɂ��ׂĂ�Module�𓮂����C���ꂼ��̏o�͂���ɁC
	���̓��͂����߂Ă���
	@sa SAModule
 */
class SAServer{
public:
	/**
		Construct and Run SAServer
		<ol>
			<li>Initialize()</li>
		</ol>
	*/
	SAServer();
	/**
		��N���b�N�������i�߂�
		<ol>
			<li>Run();</li>
			<li>Inhibit();</li>
			<li>Suppress();</li>
		</ol>
	 */
	void Process();
protected:
	/**
		Initialize States
	*/
	void Initialize();
	/**
		Server�ɓo�^����Ă��邷�ׂĂ�Module��Run����
	*/
	void Run();
	/**
		���w��Module��}������.
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
		���w��Module��}������.
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
		����Module�ɑ�����M��
	*/
	float inbox[NUM_MODULES];
	/**
		Module���瑗���Ă����M��
	*/
	float outbox[NUM_MODULES];

	/**
		Inhibition�̊m���s��
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
		���ʂ�Subsumption Architecture�Ȃ�C�s��ł���K�v�͂Ȃ��D
		����̊K�w��Inhibit����m����m��΂悢����C�z��ŗǂ��͂�
		����ǁC�����K�w�̂��̂�������肷��Ƃ��ɁC�s�񂪕K�v
	*/
	float probInhibition[NUM_MODULES][NUM_MODULES];
	/**
		Suppression�̊m���s��
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

	/**
		�Ǘ�����Ă���Module
	*/
	SAModule* modules[NUM_MODULES];
};

#endif //_SAServer_H_