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
};

#endif //_SAModule_H_