#ifndef _FieldTester_HPP_
#define _FieldTester_HPP_

#include "FieldConnectorTester.h"

/**
	@class FieldTeste
	@brief �^����ꂽField��ŁAWire, Inhibitor, Supress, probSelecter, probSuperposer
	��5��̓����ɂ���Test����N���X
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
		FieldConnectorTester test = FieldConnectorTester((const int *)field, i);
		if(i <= 2){
			test.Test(1, 70 * 3);
		}else if(i == 3 || i == 4){
			for(int j = 0; j <= 10; j++){
				double prob = (double)j * 0.1;
				test = FieldConnectorTester((const int *)field, i, prob);
				test.Test();
			}
		}else{
			test.Test();
		}
	}
}

#endif //_FieldTester_HPP_