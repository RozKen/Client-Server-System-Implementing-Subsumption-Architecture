#ifndef _SAModule_H_
#define _SAModule_H_
/**
	@class SAModule
	@brief Module��Interface�N���X
	Module��State Machine�CActuator, Sensor��3��ނ�z��
	��{�Cinbox�̐M�����󂯎���āCRun����ƁCoutbox�ɓ����M�����o�͂���
*/
class SAModule {
public:
	/**
		@brief �R���X�g���N�^.�������Ȃ���
	*/
	SAModule();
	SAModule(int numberOfInputPorts, int numberOfOutputPorts);
	/**
		@brief ���W���[���𓮍삳����
		�������z�֐��D�p�������q�N���X�ł̒�`���K�{
		@param	signal ���͐M��
		@return �M���o��
	*/
	virtual float Run(float signal) = 0;
	//���݂̏��C�ꉞ�c���Ă���

	/**
		@brief ���W���[���𓮍삳����D
		�������z�֐��D�p�������q�N���X�ł̒�`���K�{
	 */
	virtual void Run() = 0;

	/**
		@brief ���W���[���ɓ��̓|�[�g���쐬����
		@param numberOfPorts �쐬������̓|�[�g�̐�
	 */
	void createInputPort(int numberOfPorts);

	/**
		@brief ���W���[���ɏo�̓|�[�g���쐬����.�w�肵��������񂾂��쐬����
		@param numberOfPorts �쐬����o�̓|�[�g�̐�
	 */
	void createOutputPort(int numberOfPorts);
	/**
		@brief inputs�ւ̃|�C���^��^����.SAConnector�̐ڑ��֗��p����.
		@return *inputs
		@sa SAConnector
	 */
	float* getInputsPtr();
	/**
		@brief outputs�ւ̃|�C���^��^����.SAConnector�̐ڑ��֗��p����.
		@return *outputs
		@sa SAConnector
	 */
	float* getOutputsPtr();
	/**
		@brief input�M����ݒ肷��D
		@param input ���͐M���̔z��v�f�֑������l
		@param index �ݒ肷��z��v�f��index
	 */
	void setInput(float inputSignal, int index);
	/**
		@brief input�M����n���D
		@param index ����z��v�f��index
		@return input ���͐M���̔z��v�f�̒l
	 */
	float getInput(int index);
	/**
		@brief output��M���ݒ肷��
		@param output �o�͐M���̔z��v�f�֑������l
		@param index �ݒ肷��z��v�f��index
	 */
	void setOutput(float outputSignal, int index);
	/**
		@brief output�M����n��
		@param index ����z��v�f��index
		@return outputs
	 */
	float getOutput(int index);

	
protected:
	///���͐M��Buffer
	float* inputs;
	///�o�͐M��Nuffer
	float* outputs;
};

inline SAModule::SAModule(){
}

inline SAModule::SAModule(int numberOfInputPorts, int numberOfOutputPorts){
	//�M��Buffer��������
	inputs = new float[numberOfInputPorts];
	outputs = new float[numberOfOutputPorts];
}

inline void SAModule::createInputPort(int numberOfPorts){
	//���͐M��Buffer��������
	inputs = new float[numberOfPorts];
}

inline void SAModule::createOutputPort(int numberOfPorts){
	//���͐M��Buffer��������
	outputs = new float[numberOfPorts];
}

inline float* SAModule::getInputsPtr(){
	return inputs;
}

inline float* SAModule::getOutputsPtr(){
	return outputs;
}

inline void SAModule::setInput(float inputSignal, int index){
	inputs[index] = inputSignal;
}

inline float SAModule::getInput(int index){
	return inputs[index];
}

inline void SAModule::setOutput(float outputSignal, int index){
	outputs[index] = outputSignal;
}

inline float SAModule::getOutput(int index){
	return outputs[index];
}
#endif //_SAModule_H_