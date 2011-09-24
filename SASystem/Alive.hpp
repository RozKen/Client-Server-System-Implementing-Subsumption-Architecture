#ifndef Alive_HPP_
#define Alive_HPP_

#include "SAModule.h"
#include "Constants.h"

/**
	@brief Mission: �o�b�e���[���[���ɂ��Ȃ�
	<ol>
		<li>���݃o�b�e���[��ŁCBattery Status < 100%�̂Ƃ��C�o��=0</li>
		<li>���E����Battery Charger������Ƃ��C�����܂Ői�ނ悤�o��</li>
		<li>���̑��̎��C�o��=0</li>
	</ol>
 */
class Alive : public SAModule {
public:
	/**
		@brief Constructor
		<ul>
			<li>outputs[0] : �ړ���̑��Έʒu</li>
			<li>inputs[0] - inputs[10] : Vision Scope</li>
			<li>inputs[11] : Battery Status</li>
		</ul>
	 */
	Alive();
	/**
		@brief Mission: �o�b�e���[���[���ɂ��Ȃ�
		<ol>
			<li>���݃o�b�e���[��ŁCBattery Status < 100%�̂Ƃ��C�o��=0</li>
			<li>���E����Battery Charger������Ƃ��C�����܂Ői�ނ悤�o��</li>
			<li>���̑��̎��C�o��=0</li>
		</ol>
	 */
	void Run();
protected:
	/**
		@brief �����Ă���͈�(RANGEVISION��)��Battery Charger�����邩
		�m�F����
		@return Battery Charger�̗L��
	 */
	bool isChargerExist();
	/**
		@brief �ŋߖT��BatteryCharger��T���C���Έʒu��Ԃ�
		����Charger��ł��邱�Ƃ͑z�肵�Ă��Ȃ��D
		@return �ŋߖT��BatteryCharger�̑��Έʒu
	 */
	int findNearestCharger();
	///�o�b�e���[�c��
	int battery;
	///�����Ă������
	int vision[RANGEVISION];
	///���݈ʒu��vision�z����index
	int CURRENT;
	///���ΐ���Counter
	int count;
};

inline Alive::Alive()
	: SAModule(RANGEVISION + 1, 1), battery(0), CURRENT((RANGEVISION - 1) / 2), count(0){
	for(int i = 0; i < RANGEVISION; i++){
		vision[i] = 0;
		inputs[i] = 0;
	}
	vision[CURRENT] = ONSTART;
	inputs[CURRENT] = ONSTART;
	inputs[RANGEVISION] = 100;
}
inline void Alive::Run(){
	if(count % 3 == 0){
		//Inpute����̏��œ����ϐ����X�V
		for(int i = 0; i < RANGEVISION; i++){
			vision[i] = inputs[i];
		}
		battery = inputs[RANGEVISION];

		if(vision[CURRENT] == ONCHARGER && battery < 100){
			outputs[0] = 0;
		}else if(isChargerExist()){
			outputs[0] = findNearestCharger();
		}else{
			outputs[0] = 0;
		}
	}else{
		outputs[0] = 0;
	}
	count++;
}

inline bool Alive::isChargerExist(){
	for(int i = 0; i < RANGEVISION; i++){
		if(i != CURRENT){
			if(vision[i] == ONCHARGER){
				return true;
			}
		}
	}
	return false;
}

inline int Alive::findNearestCharger(){
	for(int i = 1; i < (RANGEVISION + 1) / 2; i++){
		if(vision[CURRENT + i] == ONCHARGER){
			return i;
		}else if(vision[CURRENT - i] == ONCHARGER){
			return -i;
		}
	}
	//������Ȃ���ʂł̂��̊֐��̗��p�͑z��O.
	return -100;
}

#endif //Alive_HPP_