#ifndef _SAModule_H_
#define _SAModule_H_

//���M�����	NO_SIGNAL��include
#include "Constants.h"
#include "Blackboard.h"

/**
	@class SAModule
	@brief Module��Interface�N���X
	Module��State Machine�CActuator, Sensor��3��ނ�z��
	��{�Cinbox�̐M�����󂯎���āCRun����ƁCoutbox�ɓ����M�����o�͂���
*/
class SAModule {
public:
	/**
		@brief Constructor. Initialize std::vector
	*/
	SAModule();
	/**
		@brief Destructor. Delete std::vector
	 */
	~SAModule();
	/**
		@brief ���W���[���𓮍삳����D
		�������z�֐��D�p�������q�N���X�ł̒�`���K�{
	 */
	virtual void Run() = 0;

	/**
		@brief ���̓|�[�g��ǉ�����
		@param title ���̓|�[�g�̖��O
	 */
	void addInput(std::string title);
	/**
		@brief �o�̓|�[�g��ǉ�����
		@param title �o�̓|�[�g�̖��O
	 */
	void addOutput(std::string title);
	/**
		@brief memory�ɂ�����|�[�g�ԍ���ǉ�����
		@param index ���̓|�[�g�ԍ�
	 */
	void addInputIndex(int index);
	/**
		@brief memory�ɂ�����|�[�g�ԍ���ǉ�����
		@param index �o�̓|�[�g�ԍ�
	 */
	void addOutputIndex(int index);

	///////////////Setters and Getters///////////////
	/**
		@brief �����C����Module�̐e�ƂȂ�Module���w�肷��
		��{�I�ɁCBlackboard�́C�e�̂��̂𗘗p����
		@sa Blackboard
	 */
	virtual void setParent(SAModule* parent);

	std::vector<std::string>* getInputTitles() const;
	std::vector<std::string>* getOutputTitles() const;

	/**
		@brief input�M����n���D
		@param index ����z��v�f��index
		@return input ���͐M���̔z��v�f�̒l
	 */
	float getInput(int index) const;
	/**
		@brief output��M���ݒ肷��
		@param output �o�͐M���̔z��v�f�֑������l
		@param index �ݒ肷��z��v�f��index
	 */
	void setOutput(int index, float signal);
	/**
		@brief ���͐M���|�[�g����Ԃ�
		@return ���͐M���|�[�g��
	 */
	int getNumOfInputPorts() const;
	/**
		@brief �o�͐M���|�[�g����Ԃ�
		@return �o�͐M���|�[�g��
	 */
	int getNumOfOutputPorts() const;
	/**
		@brief �����Ɏ��L���̈�ւ̃|�C���^��Ԃ�
		@return �����Ɏ��L���̈�
		@sa Blackboard
	 */
	Blackboard* getMemory() const;
	
protected:
	///SAModule�̓��͒l���i�[����Ă���memory���Index
	std::vector<int> *inputIndex;
	///SAModule�̏o�͒l���i�[����Ă���memory���Index
	std::vector<int> *outputIndex;
	///Log�ɂ�����C���͒l��������閼�O
	std::vector<std::string> *inputTitles;
	///Log�ɂ�����C�o�͒l��������閼�O
	std::vector<std::string> *outputTitles;
	///���͐M���|�[�g��
	int numOfInputPorts;
	///�o�͐M���|�[�g��
	int numOfOutputPorts;
	///�����C�e�ɓ����郂�W���[��
	SAModule* parent;
	///�l�̓��o�͂ɓ�����C���p����L���̈�
	Blackboard* memory;
};

#endif //_SAModule_H_