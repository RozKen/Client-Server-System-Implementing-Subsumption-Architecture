#ifndef _Cont_Avoid_HPP_
#define _Cont_Avoid_HPP_

#include "SAModule.h"
#include "Constants.h"

/**
	@class ContAvoid
	@brief ���̂��̂ɂԂ���Ȃ��悤�ɂ��悤�Ƃ��鐧���
	<h1>Inputs</h1>
	<ul>
		<li>RangeCAv0 : 0</li>
		<li>RangeCAv1 : 30</li>
		<li>RangeCAv2 : 60</li>
		<li>RangeCAv3 : 90</li>
		<li>RangeCAv4 : 120</li>
		<li>RangeCAv5 : 150</li>
		<li>RangeCAv6 : 180</li>
		<li>RangeCAv7 : 210</li>
		<li>RangeCAv8 : 240</li>
		<li>RangeCAv9 : 270</li>
		<li>RangeCAv10 : 300</li>
		<li>RangeCAv11 : 330</li>
	</ul>
	<h1>Outputs</h1>
	<ul>
		<li>Output0: dXCAv: delta X - differential of Motion X</li>
		<li>Output1: dXCAv: delta Y - differential of Motion Y</li>
	</ul>
	@author Kenichi Yorozu
	@date 29th November 2011
 */
class ContAvoid : public SAModule{
public:
	/**
		@brief Default Constructor
		Input, Output�Ȃǂ�ǉ����Ă���.
	 */
	ContAvoid();
	/**
		@brief ���s���̓���.
		<ul>
			<li>�߂��Ɋ댯�ȕ��̂�����Ƃ�</li>
			<ul>
				<li>���S�ȕ���������΂������</li>
				<li>�Ȃ���Β�~����</li>
			</ul>
			<li>���肪���ׂĈ��S�ȂƂ��CNO_SIGNAL</li>
		</ul>
		@sa SAModule::Run()
	 */
	virtual void Run();
protected:
};

inline ContAvoid::ContAvoid(){
	std::string temp;
	for(int i = 0; i < RANGE_DIV; i++){
		temp = "RangeCAv";
		temp.append(this->intToString(i));
		this->addInput(temp);
	}
	this->addOutput("dXCAv");
	this->addOutput("dXCAv");
}

inline void ContAvoid::Run(){
	//�댯�ȕ��p�����邩�ǂ���
	bool danger = false;
	//���S�ȕ����̃��X�g
	std::vector<int> safeIndex;
	//�o�͐M��
	float signalX, signalY;

	for(int i = 0; i < RANGE_DIV; i++){
		if(this->getInput(i) < RANGE_DANGER){
			danger = true;
		}else{
			safeIndex.push_back(i);
		}
	}

	if(danger){
		if(safeIndex.empty()){
			signalX = 0.0f;
			signalY = 0.0f;
		}else{
			int index = safeIndex.size() / 2;
			double theta = (RANGE_DEG * PI / 180.0) * (double)(safeIndex.at(index));
			signalX = (float)cos(theta);
			signalY = (float)sin(theta);
		}
	}else{
		signalX = NO_SIGNAL;
		signalY = NO_SIGNAL;
	}

	this->setOutput(0, signalX);
	this->setOutput(1, signalY);
}


#endif	//_Cont_Avoid_HPP_