#ifndef _SAServer_H_
#define _SAServer_H_

#define	NUM_MODULES	3		//Moduleの数

class SAServer{
public:
	/**
		Construct and Run SAServer
		1. Initialize()
		2. While(0){ Run(); Inhibit(); Suppress(); }
	*/
	SAServer();
protected:
	/**
		Initialize States
	*/
	void Initialize();
	/**
		Run all Modules
	*/
	void Run();
	/**
		下層のModuleを抑制する.
		1. inhibited[]の各要素から1を引く
		2. inhibited[]の値が-1であるものは，0に直し，
		3. probInhibition[][]に基づいてinhibited[]を更新する
		4. inhibited[]の値が正である要素をinhibitする
		@sa inhibited[]
		@sa probInhibition[][]
	*/
	void Inhibit();
	/**
		下層のModuleを抑制する.
		1. suppressed[]の各要素から1を引く
		2. suppressed[]の値が-1であるものは，0に直し，
		3. probSuppression[][]に基づいてsuppressed[]を更新する
		4. suppressed[]の値が正である要素をsuppressする
		@sa suppressed[]
		@sa probSuppression[][]
	*/
	void Suppress();

	/**
		次にModuleに送られる信号
	*/
	float inbox[NUM_MODULES];
	/**
		Moduleから送られてきた信号
	*/
	float outbox[NUM_MODULES];

	/**
		Inhibitionの確率行列
								Inferior Layer
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0
						0.2, 0.0, 0.0, 0.0, 0.0, 0.0
		Superior Layer	0.0, 0.3, 0.0, 0.0, 0.0, 0.0
						0.0, 0.0, 0.5, 0.0, 0.0, 0.0
						0.0, 0.0, 0.0, 0.7, 0.0, 0.0
						0.0, 0.0, 0.0, 0.0, 0.2, 0.0
		普通のSubsumption Architectureなら，行列である必要はない．
		一つ下の階層をInhibitする確率を知ればよいから，配列で良いはず
		けれど，同じ階層のものを作ったりするときに，行列が必要
	*/
	float probIhibition[NUM_MODULES][NUM_MODULES];
	/**
		Suppressionの確率行列
								Inferior Layer
						0.0, 0.0, 0.0, 0.0, 0.0, 0.0
						0.2, 0.0, 0.0, 0.0, 0.0, 0.0
		Superior Layer	0.0, 0.3, 0.0, 0.0, 0.0, 0.0
						0.0, 0.0, 0.5, 0.0, 0.0, 0.0
						0.0, 0.0, 0.0, 0.7, 0.0, 0.0
						0.0, 0.0, 0.0, 0.0, 0.2, 0.0
		普通のSubsumption Architectureなら，行列である必要はない．
		一つ下の階層をSuppressionする確率を知ればよいから，配列で良いはず
		けれど，同じ階層のものを作ったりするときに，行列が必要
	*/
	float probSuppression[NUM_MODULES][NUM_MODULES];

	/**
		Inhibitされたままでいる残時間
	*/
	int inhibited[NUM_MODULES];
	/**
		Suppressされたままでいる残時間
	*/
	int suppressed[NUM_MODULES];
}

#endif