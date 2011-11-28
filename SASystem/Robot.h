#ifndef _Robot_H_
#define _Robot_H_

#include <vector>
#include "SAModule.h"
#include "Blackboard.h"
#include "Arbiter.h"

/**
	@class Robot
	@brief ���{�b�g��̂̓����𐧌䂷�郂�W���[��.
	�ȑO��SAServer�ɋ߂����������邪�CBlackboard System���������Ă���

	inputs: sensor�ւ̓���
	outputs: actuator�ɂ��o��
	@sa SAModule
 */
class Robot : public SAModule{
public:
	/**
		@brief Default Constructor
	 */
	Robot();
	/**
		@brief Constructor with Log File Path
		@param directoryPath	���O��ۑ�����f�B���N�g���ւ̃p�X
		@param fileName			���O�t�@�C����
	 */
	Robot(std::string directoryPath, std::string fileName);

	/**
		@brief Destructor. delete vectors
	 */
	~Robot();
	virtual void Run();
	/**
		@brief ���W���[����o�^����
		@sa SAModule
	 */
	void addModule(SAModule *module);
	/**
		@brief �R�l�N�^�[��o�^����
		@sa Arbiter
	 */
	void addArbiter(Arbiter *arbiter);
	/**
		@brief	���O��ۑ�����ꏊ��ݒ肷��
		@param directoryPath	���O��ۑ�����f�B���N�g���ւ̃p�X
		@param fileName			���O�t�@�C����
	 */
	void setLogDirectoryPath(std::string directoryPath, std::string fileName);
	std::string getLogFilePath() const;
protected:
	/**
		@brief ���{�b�g����Module�����ׂĎ��s����
	 */
	void RunModules();
	/**
		@brief ���ׂĂ�Arbiter�����s����
	 */
	void ProcessArbiters();
	/**
		@brief Inner Wire�̓��͂Ɋւ�镔��������
		Robot�ւ̓���(inputs)���CRobot��innerMemory��iBoard/fBoard�փR�s�[����
	 */
	void ProcessInputs();
	/**
		@brief Inner Wire�̏o�͂Ɋւ�镔��������
		Robot����̏o��(outputs)���CRobot��innerMemory��iBoard/fBoard����R�s�[����
	 */
	void ProcessOutputs();
	/**
		@brief Initialize States
		���̍\�z,���O�̏�����
		@sa Blackboard
		@sa Log();
	*/
	void Initialize();
	/**
		@brief �Ǘ�����Ă���Module
		Module�̓o�^���ꂽ���Ɋi�[����Ă���.
	*/
	std::vector<SAModule*> *modules;

	/**
		@brief �o�^����Ă���Arbiter
		Modifier�̓o�^���ꂽ���Ɋi�[����Ă���.
	 */
	std::vector<Arbiter*> *arbiters;

	/*
		iBoard/fBoard��Robot��input/output������
		Inner Wire�̒�`
	 */
	/**
		@brief
		Source Type
		<ul>
			<li>0: input</li>
			<li>1: output</li>
			<li>2: iBoard</li>
			<li>3: fBoard</li>
		</ul>
	 */
	std::vector<int> *innerWireSrcType;
	std::vector<int> *innerWireSrcIndex;
	std::vector<int> *innerWireDestType;
	std::vector<int> *innerWireDestIndex;
};

#endif _Robot_H_