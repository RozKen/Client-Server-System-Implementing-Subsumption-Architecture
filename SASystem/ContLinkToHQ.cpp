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
	//hop, relativeRoot���X�V
	if(hop == NO_SIGNAL){
		//������Ȃ�������D
		if(!findHQ()){
			//Start�n�_�֖߂�
			float dX = ((float)START_X - posX);
			float dY = ((float)START_Y - posY);
			float d = norm(dX, dY);
			signalX = (float)MAX_DRIVE * dX / d;
			signalY = (float)MAX_DRIVE * dY / d;
		}
	}else{	//����hop�����鎞
		if(hop == 0){	//hop����0�̎���relativeRoot���Ȃ�
			float dX = ((float)START_X - posX);
			float dY = ((float)START_Y - posY);
			float d = norm(dX, dY);
			if(d >= START_R){
				hop = NO_SIGNAL;
			}
		}else{
			int pHop = ((RobotMAV*)parent)->getRelativeRoot()->getHop();
			//relativeRoot��Hop���C������Hop�����傫��������CNO_SIGNAL�Ƃ���
			if( pHop >= ((RobotMAV*)this->parent)->getHop()){
				hop = NO_SIGNAL;
			}else{
				//��������Ȃ��Ƃ��́C������Hop���v�Z�������D
				hop = pHop + 1;;
			}
		}
	}
	this->setIBoard(0, hop);

	//�Ƃ�����CrelativeRoot������������@���^����
	if(P_RECONNECT > rand()){
		findHQ();
	}


}

bool ContLinkToHQ::findHQ(){
	bool result = false;
	float posX = this->getInput(0);
	float posY = this->getInput(1);
	float dX = START_X - posX;
	float dY = START_Y - posY;
	float d = norm(dX, dY);
	RobotMAV* parent = ((RobotMAV*)this->parent);
	if(d < START_R){	//�i�ߕ�����߂��Ƃ�
		parent->setHop(0);
		return true;
	}else{	//�����łȂ��Ƃ��C
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
					return true;
				}
			}
			//nearest��hop = NO_SIGNAL�̎�
			if(!flag){
				//hop = NO_SIGNAL�Ƃ��āCresult = false
				parent->setHop(NO_SIGNAL);
				return false;
			}
		}
	}
	return result;
}