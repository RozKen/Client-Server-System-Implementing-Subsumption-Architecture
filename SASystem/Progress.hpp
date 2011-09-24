#ifndef Progress_HPP_
#define Progress_HPP_

#include "SAModule.h"
#include "Constants.h"

class Progress : public SAModule {
public:
	/**
		@brief Constructor
		<ul>
			<li>outputs[0] : �ړ���̑��Έʒu</li>
			<li>inputs[0] - inputs[RANGEVISION - 1] : �����Ă������</li>
			<li>inputs[RANGEVISION] ; step��</li>
			<li>inputs[RANGEVISION + 1] : progress��</li>
		</ul>
	 */
	Progress();
	/**
		@brief Mission : �S�[���̕����֐i��
		<ol>
			<li>���E���ɃS�[�������鎞�C�����ֈړ�</li>
			<li>position / step < threshold�̎��C5�}�X�i��</li>
			<li>���̑��̎��C�o��0</li>
		</ol>
	 */
	void Run();

protected:
	/**
		@brief ���E����Goal�����邩�ǂ������ׂ�
		@return ���E����Goal�����邩�ǂ���
	 */
	bool isSeeGoal();
	/**
		@brief �S�[���̑��Έʒu��Ԃ�
		@return �S�[���̑��Έʒu
	 */
	int stepToGoal();

	///step��
	int stepCount;
	///�i�x
	int progressCount;
	///���E
	int vision[RANGEVISION];
	///�i�݂����鐫���̋���[0.0 - 1.0]
	float threshold;
};

inline Progress::Progress() 
	: SAModule(RANGEVISION + 2, 1), stepCount(0), progressCount(0), threshold(0.3){
	for(int i = 0; i < RANGEVISION; i++){
		vision[i] = 0;
	}
}

inline void Progress::Run(){
	//Update Local Variables
	for(int i = 0; i < RANGEVISION; i++){
		vision[i] = inputs[i];
	}
	stepCount = inputs[RANGEVISION];
	progressCount = inputs[RANGEVISION + 1];

	if(isSeeGoal()){
		outputs[0] = stepToGoal();
	}else if(progressCount / stepCount < threshold){
		//TODO �{����[1-10]�̃����_���ɂ���\��
		outputs[0] = 5;
	}else{
		outputs[0] = 0;
	}
}

inline bool Progress::isSeeGoal(){
	for(int i = 0; i < RANGEVISION; i++){
		if(vision[i] == ONGOAL){
			return true;
		}
	}
	return false;
}

inline int Progress::stepToGoal(){
	int index = -100;
	for(int i = 0; i < RANGEVISION; i++){
		if(vision[i] == ONGOAL){
			index = i - ((RANGEVISION - 1) / 2);
			break;
		}
	}
	return index;
}

#endif //Progress_HPP_