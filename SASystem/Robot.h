#ifndef _Robot_H_
#define _Robot_H_

#include <vector>
#include "SAModule.h"
#include "Blackboard.h"

class Arbiter;

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
		@brief Constructor
	 */
	Robot();

	/**
		@brief Constructor
		@param inputPorts �Z���T�ւ̓��͂̐�
		@param outputPorts �A�N�`���G�[�^�ɂ��o�͂̐�
	 */
	Robot(int inputPorts, int outputPorts);

	/**
		@brief Mission: Operate a Robot
		<ol>
			<li>RunModules</li>
			<li>ProcessArbiters</li>
			<li>Log</li>
		</ol>
	 */
	void Run();

	/**
		@brief ���W���[���ɓ��̓|�[�g���쐬����. �w�肵��������񂾂��쐬����
		SAModule�̂��̂��㏑��
		@param numberOfPorts �쐬������̓|�[�g�̐�
	 */
	virtual void createInputPort(int numberOfPorts);
	/**
		@brief ���W���[���ɏo�̓|�[�g���쐬����.�w�肵��������񂾂��쐬����
		SAModule�̂��̂��㏑��
		@param numberOfPorts �쐬����o�̓|�[�g�̐�
	 */
	virtual void createOutputPort(int numberOfPorts);
protected:
	/**
		@brief ����Robot�̂����L���̈� Internal Blackboard
	 */
	Blackboard* memory;
	/**
		@brief ���{�b�g����Module�����ׂĎ��s����
	 */
	void RunModules();
	/**
		@brief ���ׂĂ�Arbiter�����s����
	 */
	void ProcessArbiters();
	/**
		@brief ���O���Ƃ�
	 */
	void Log();
	/**
		@brief Initialize States
		���̍\�z,���O�̏�����
		@sa Blackboard
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
		@sa Arbiter
	 */
	void addArbiter(Arbiter *arbiter);

	/**
		@brief �Ǘ�����Ă���Module
		Module�̓o�^���ꂽ���Ɋi�[����Ă���.
	*/
	std::vector<SAModule*> modules;

	/**
		@brief �o�^����Ă���Arbiter
		Modifier�̓o�^���ꂽ���Ɋi�[����Ă���.
	 */
	std::vector<Arbiter*> arbiters;

};

#endif _Robot_H_