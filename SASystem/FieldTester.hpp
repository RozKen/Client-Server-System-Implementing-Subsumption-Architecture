#ifndef _FieldTester_HPP_
#define _FieldTester_HPP_

#include "FieldConnectorTester.h"

/**
	@class FieldTeste
	@brief —^‚¦‚ç‚ê‚½Fieldã‚ÅAWire, Inhibitor, Supress, probSelecter, probSuperposer
	‚Ì5Ží‚Ì“®‚«‚É‚Â‚¢‚ÄTest‚·‚éƒNƒ‰ƒX
	@date 18th October 2011
	@author Kenichi Yorozu
 */
class FieldTester{
public:
	FieldTester(const int* field);
	void Test();
protected:
	const int* field;
};

FieldTester::FieldTester(const int* field){
	this->field = field;
}

void FieldTester::Test(){
	for(int i = 0; i < 5; i++){
		if(i <= 2){
			FieldConnectorTester test = FieldConnectorTester((const int *)field, i);
			test.Test(1, 70 * 3);
		}else if(i == 3){
			for(int j = 0; j <= 10; j++){
				double prob = (double)j * 0.1;
				FieldConnectorTester test = FieldConnectorTester((const int *)field, i, prob);
				test.Test();
			}
		}else{
			FieldConnectorTester test = FieldConnectorTester((const int *)field, i);
			test.Test();
		}
	}
}

#endif //_FieldTester_HPP_