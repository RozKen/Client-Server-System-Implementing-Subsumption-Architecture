#ifndef _SAModule_H_
#define _SAModule_H_

class SAModule {
public:
	/**
		コンストラクタ
	*/
	SAModule();
	/**
		モジュールを動作させる
		@param	signal 入力信号
		@return 信号出力
	*/
	float Run(float signal);
protected:
};

#endif //_SAModule_H_