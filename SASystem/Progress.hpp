#ifndef ProgressController_HPP_
#define ProgressController_HPP_

#include "SAModule.h"
#include "Constants.h"
#include <iostream>
/**
	@brief Mission : �S�[���̕����֐i��
	<ol>
		<li>���E���ɃS�[�������鎞�C�����ֈړ�</li>
		<li>position / step < threshold�̎��C5�}�X�i��</li>
		<li>���̑��̎��C�o��0</li>
	</ol>
	*/
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
	///���ΐ���Counter
	int count;
};

inline Progress::Progress() 
	: SAModule(RANGEVISION + 2, 1), stepCount(0), progressCount(0), threshold(0.7), count(0){
	for(int i = 0; i < RANGEVISION; i++){
		vision[i] = 0;
		inputs[i] = 0;
	}
	inputs[RANGEVISION] = 0;
	inputs[RANGEVISION + 1] = 0;
}

inline void Progress::Run(){
	if(count % 3 == 0){
		//Update Local Variables
		for(int i = 0; i < RANGEVISION; i++){
			vision[i] = inputs[i];
		}
		stepCount = inputs[RANGEVISION];
		progressCount = inputs[RANGEVISION + 1];

		if(isSeeGoal()){
			outputs[0] = stepToGoal();
		}else if(stepCount < 10){
			outputs[0] = 0;
		}else if((double)progressCount / (double)stepCount < threshold){
	//		std::cout << "progressCount: " << progressCount << std::endl;
	//		std::cout << "stepCount: " << stepCount << std::endl;
	//		std::cout << "ratio: " << (double)progressCount / (double)stepCount << std::endl;
	//		std::cout << "threshold: " << threshold << std::endl;
			//TODO �{����[1-10]�̃����_���ɂ���\��
			outputs[0] = 5;
		}else{
			outputs[0] = 0;
		}
	}else{
		outputs[0] = 0;
	}
	count++;
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