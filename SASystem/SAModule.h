#ifndef _SAModule_H_
#define _SAModule_H_
/**
	Module��Interface�N���X
	Module��State Machine�CActuator, Sensor��3��ނ�z��
	��{�Cinbox�̐M�����󂯎���āCRun����ƁCoutbox�ɓ����M�����o�͂���
*/
class SAModule {
public:
	/**
		�R���X�g���N�^
	*/
	SAModule();
	/**
		���W���[���𓮍삳����
		@param	signal ���͐M��
		@return �M���o��
	*/
	virtual float Run(float signal);
protected:
	/**
	 * @fn SignalDecoder
	 * @brief ���float�^�̒l�����̐M���𒊏o����.
	 * @param input ���͒l
	 * @param output1 �o�͒l1
	 * @param output2 �o�͒l2
	 */

	void SignalDecoder(float input, float &output1, float &output2);
	/**
	 * @fn SignalEncoder
	 * @brief 2��float�^�̒l����1�̐M���𐶐�����.
	 * @param input1 ���͒l1
	 * @param input2 ���͒l2
	 * @return output �o�͒l
	 */
	float SignalEncoder(float input1, float input2);
};

#endif //_SAModule_H_