#include "ContLinkToHQ.hpp"
#include "RobotMAV.h"

ContLinkToHQ::ContLinkToHQ() : rand(0.0, 1.0){
	this->addInput("posXCLTHQ");
	this->addInput("posYCLTHQ");

	this->addOutput("dXCLTHQ");
	this->addOutput("dXCLTHQ");

	this->addIBoard("iHop");
}

void ContLinkToHQ::Run(){
	int hop = this->getIBoard(0);

	float posX = this->getInput(0);
	float posY = this->getInput(1);

	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED

	bool toStart = !update();
	//start�n�_�֌������ꍇ
	if(toStart){
		float dX = ((float)START_X) - posX;
		float dY = ((float)START_Y) - posY;
		float d = norm(dX, dY);
		signalX = ((float)MAX_DRIVE) * dX / d;
		signalY = ((float)MAX_DRIVE) * dY / d;
#ifdef	IMPORTANCE_BASED
		float value = d * 2 / FIELD_SIZE;
		if(value > 1.0f){
			value = 1.0f;
		}
		this->importance = this->calcImportance(value);
#endif	//IMPORTANCE_BASED
		//std::cout << "Headquarter 0: " << signalX << ", " << signalY << std::endl;
	}else{	//start�n�_�֌������K�v�͂Ȃ��ꍇ�D
		float dXP;
		float dYP;
		//hop = 0�̎���relativeRoot�����Ȃ��FStart�n�_�֌�����
		if(hop == 0 || hop == NO_SIGNAL){
			dXP = (float)START_X - posX;
			dYP = (float)START_Y - posY;
		}else{	//hop != 0�̂Ƃ��́CrelativeRoot�֌������D
			float pPosX = ((RobotMAV*)this->parent)->getRelativeRoot()->getPosX();
			float pPosY = ((RobotMAV*)this->parent)->getRelativeRoot()->getPosY();
			dXP = pPosX - posX;
			dYP = pPosY - posY;
		}
		float dP = norm(dXP, dYP);
		//relativeRoot / START �����������Ƃ�
		if(dP >= WIFI_CONNECT * WIFI_WEAK){
			//�ړI�n�Ɍ�����
			signalX = (float)MAX_DRIVE * dXP / dP;
			signalY = (float)MAX_DRIVE * dYP / dP;
#ifdef	IMPORTANCE_BASED
			float value = dP / (WIFI_CONNECT * WIFI_WEAK);
			this->importance = this->calcImportance(value);
#endif	//IMPORTANCE_BASED
			//std::cout << "Headquarter 1: " << signalX << ", " << signalY << std::endl;
		}else{
			//Wifi��ڑ�����̂ɏ[���߂��Ƃ��C�M���͏o���Ȃ�
			signalX = NO_SIGNAL;
			signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
			this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
		}
	}
	//set Outputs
	////For Now
	//signalX = NO_SIGNAL;
	//signalY = NO_SIGNAL;
#ifdef	IMPORTANCE_BASED
	//this->importance = NO_SIGNAL;
#endif	//IMPORTANCE_BASED
	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}

bool ContLinkToHQ::update(){
	bool result = false;
	bool find = false;

	int hop = this->getIBoard(0);
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	float dX = ((float)START_X) - posX;
	float dY = ((float)START_Y) - posY;
	float d = norm(dX, dY);
	float signalX = NO_SIGNAL;
	float signalY = NO_SIGNAL;
	
	//findHQ���邩�ǂ��������߂Chop���Čv�Z

	//�Ƃ�����CrelativeRoot������������@���^����
	if(P_RECONNECT > rand()){
		find = true;
	}else{	//�m���I�ɂ͏��������Ȃ��ꍇ
		if(hop == 0){
			//���݂��܂��ڑ����m������Ă��Ȃ���΁C�V���ɒT���悤�w��
			if(d >= START_R){
				find = true;
				hop = NO_SIGNAL;
			}else{
				find = false;
			}
		}else if(hop != NO_SIGNAL){
			int pHop = ((RobotMAV*)parent)->getRelativeRoot()->getHop();
			//relativeRoot��Hop���C������Hop�����傫��������CNO_SIGNAL�Ƃ���
			if( pHop >= ((RobotMAV*)this->parent)->getHop()){
				hop = NO_SIGNAL;
			}else{
				//��������Ȃ��Ƃ��́C������Hop���v�Z�������D
				hop = pHop + 1;
			}
		}
	}
	//hop���X�V
	this->setIBoard(0, hop);
	//���̎��_��hop == NO_SIGNAL�Ȃ�C��������悤�Z�b�g����
	if(hop == NO_SIGNAL){
		find = true;
	}

	//�Ƃɂ����T�����Ă݂�
	find = true;

	//�V���ɒT������ꍇ
	if(find){
		//������Ȃ�������
		if(!findHQ()){
			//START�n�_�֖߂�悤�`����
			result = false;
		}else{
			//���������Ƃ��́C
			result = true;
		}
	}else{
		//�V���ɒT������K�v���Ȃ��ꍇ
		result = true;
	}

	return result;
}

bool ContLinkToHQ::findHQ(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	float dX = START_X - posX;
	float dY = START_Y - posY;
	float d = norm(dX, dY);
	RobotMAV* parent = ((RobotMAV*)this->parent);

	//nearest->size() = 0�̎�
	if(parent->getNearest()->size() == 0){
		//hop = NO_SIGNAL�Ƃ��āCresult = false
		parent->setHop(NO_SIGNAL);
		return false;
	}else{
		bool flag = false;
		for(int i = 0; i < parent->getNearest()->size(); i++){
			int pHop = parent->getNearestAt(i)->getHop();
			if(pHop != NO_SIGNAL){
				//nearest�̒��ŁC�q�����Ă�����̂�����ꍇ
				//relativeRobot���X�V
				parent->setRelativeRoot(parent->getNearestAt(i));
				//Hop���X�V
				parent->setHop(pHop + 1);
				flag = true;
				result = true;
				//�Ȃ�ׂ������̂��̂ƌq����悤�ɂ��Ă݂��D
				//����ɂ��C�����q����C������
			}
		}
		//nearest��hop = NO_SIGNAL�̎�
		if(!flag){
			//hop = NO_SIGNAL�Ƃ��āCresult = false
			parent->setHop(NO_SIGNAL);
			result = false;
		}
	}
	//���̎��_�ŁChop = NO_SIGNAL��
	//�i�ߕ�����߂����
	if(d < START_R && parent->getHop() == NO_SIGNAL){	//�i�ߕ�����߂��Ƃ�
		//hop = 0�Ƃ���
		parent->setHop(0);
		result = true;
	}

	return result;
}