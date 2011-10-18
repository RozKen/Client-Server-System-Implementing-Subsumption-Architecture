#ifndef _SAServer_H_
#define _SAServer_H_

#include <fstream>
#include <vector>

//#define	NUM_MODULES	10		//Module�̐�

#ifndef _SAModule_H_
class SAModule;	//header���ŕϐ���錾���邽�߂ɁCclass��錾
#endif
#ifndef SAConnector_H_
class SAConnector;
#endif
#ifndef _EnvUpdater_H_
class EnvUpdater;
#endif
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
		@brief Construct SAServer. Initialize <b>clock</b> as 0
		<ol>
			<li>Initialize()</li>
		</ol>
		@param field �^�X�N�t�B�[���h
		@param logDirectoryPath ���O��ۑ�����f�B���N�g��
		@sa clock
	*/
	SAServer(const int* field, std::string logDirectoryPath);
	/**
		@brief Construct SAServer. Initialize <b>clock</b> as 0
		<ol>
			<li>Initialize()</li>
		</ol>
		@param field �^�X�N�t�B�[���h
		@param logDirectoryPath ���O��ۑ�����f�B���N�g��
		@param index ���O�ɘA�Ԃ�t���邽�߂�index
		@sa clock
	*/
	SAServer(const int* field, std::string logDirectoryPath, int index);
	/**
		@brief ��N���b�N�������i�߂�
		<ol>
			<li>RunModules();</li>
			<li>ProcessConnections();</li>
			<li>Log();</li>
			<li>clock++</li>
		</ol>
		@sa RunModules()
		@sa ProcessConnections()
		@sa Log()
	 */
	void Process();

	/**
		@brief Initialize States
		���̍\�z,���O�̏�����
		@sa EnvUpdater
		@sa Log();
	*/
	void Initialize();

	/**
		@brief ���W���[����o�^����
		@sa SAModule
	 */
	void addModule(SAModule *module);
	/**
		@brief �R�l�N�^�[��o�^����
		@sa SAConnector
	 */
	void addConnector(SAConnector *connector);

	/**
		@brief EnvUpdater��Getter
	 */
	EnvUpdater* getEnv();

	/**
		@brief getter of logFileName
	 */
	std::string getLogFileName();

	int getStepForward();

	int getStepStop();
	
	int getStepBackward();

	int getStepSwitchDirection();

	protected:
	/**
		@brief int�^��number��4�P�^�̕�����ɂ���
		@param number ���̐���
	 */
	std::string intToString(int number);
	/**
		@brief Server�ɓo�^����Ă��邷�ׂĂ�Module��Run����
		���̑��ɁC���݂͗���(LM, RM)��speed����ɁC�ʒu�ƌ������Z�o���C
		�������Z���T�[�ɑ���D
		@sa SAModules
	*/
	void RunModules();

	/**
		@brief Server�ɐݒ肳��Ă���S�Ă�Wire, Inhibitor, Suppressor����������
		@sa SAConnector
	 */
	void ProcessConnectors();

	
	/**
		@brief Log Datas
	*/
	void Log();

	/**
		@brief �Ǘ�����Ă���Module
		Module�̓o�^���ꂽ���Ɋi�[����Ă���.
	*/
	std::vector<SAModule*> modules;

	/**
		@brief �o�^����Ă���Modifiers
		Modifier�̓o�^���ꂽ���Ɋi�[����Ă���.
	 */
	std::vector<SAConnector*> connectors;

	/**
		@brief Module���o�͂����M����Inhibit�O�̏o�͐M��
	 */
	std::vector<float> outputs;
	/**
		@brief Inhibit��̏o�͐M��
	 */
	std::vector<float> inhibited;
	/**
		@brief Suppress�O�̓��͐M��
	 */
	std::vector<float> preSuppress;
	/**
		@brief Module�ɓ��͂����M����Suppress��̓��͐M��
	 */
	std::vector<float> inputs;
	/**
		@brief �b��I�ɗ��p���Ă����
	*/
	EnvUpdater* env;

	/**
		@brief �^�X�N�t�B�[���h
		0-99�܂ł̒����̔z��ւ̃|�C���^�̂͂�
	 */
	const int* field;

	/**
		@brief Log�t�@�C����ۑ�����f�B���N�g���ւ̃p�X
	 */
	std::string logDirectoryPath;

	/**
		@brief Log�t�@�C���̖��O
	*/
	std::string logFileName;
	/**
		@brief Log�t�@�C���p�C�����o���X�g���[��
	*/
	std::ofstream ofs;

	/**
		@brief �J�n���Ă����clock��
	*/
	long int clock;

	///�O�i���Ă����
	int stepForward;
	///��~���Ă����
	int stepStop;
	///��i���Ă����
	int stepBackward;
	///�O��i���؂�ւ������
	int stepSwitchDirection;
	///�O��̃|�W�V����
	int prevPos;
	/**
		@brief �O��̐i�s����
		true : Forward
		false : Backward
	 */
	bool prevDirection;
	///�t�@�C���ɘA�Ԃ�t���邽�߂̒l
	int index;
};

inline EnvUpdater* SAServer::getEnv(){
	return env;
}

inline std::string SAServer::getLogFileName(){
	return logFileName;
}

inline int SAServer::getStepForward(){
	return stepForward;
}

inline int SAServer::getStepStop(){
	return stepStop;
}
	
inline int SAServer::getStepBackward(){
	return stepBackward;
}

inline int SAServer::getStepSwitchDirection(){
	return stepSwitchDirection;
}
#endif //_SAServer_H_