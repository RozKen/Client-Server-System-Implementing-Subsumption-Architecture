#ifndef _EnvUpdater_H_
#define _EnvUpdater_H_

/**
	@class EnvUpdater
	@brief ロボットのアクチュエーターに応じて環境を更新する主体．
	PhysXなどの代わりにかんたんなものを仕込む．
	<b>現状では，一体一体にenvUpdaterを仕込むような想定である．</b>
	@date 23th September 2011
	@author Kenichi Yorozu
*/
class EnvUpdater {
public:
	/**
		@brief Constructor
		@param field Task Field
	*/
	EnvUpdater(int* field);
	/**
		@brief 環境変数の更新.
		@param progress どのくらい進んだか(戻ったか)．PositionUpdaterの出力を入れる．
		@sa PositionUpdator
	*/
	void update(int progress);

	int getPosition();
	int getBattery();
	int* getField();
	int getProgress();

protected:
	/**
		@brief 位置(position)の更新
		@param progress どのくらい進んだか(戻ったか)．PositionUpdaterの出力を入れる．
		@sa PositionUpdater
	*/
	void updatePosition(int progress);
	/**
		@brief バッテリーの状態の更新
		@param progress どのくらい進んだか(戻ったか)．PositionUpdaterの出力を入れる．
		@param onCharger 現在Battery Chargerのマスにいるか．
		@sa PositionUpdater
	*/
	void updateBatteryStatus(int progress, bool onCharger);

	///Field配列
	int* field;
	///現在位置
	int position;
	///現在バッテリー状態.単位は[%]
	int battery;
	///進んだ量
	int progress;
};

inline int* EnvUpdater::getField(){
	return field;
}

inline int EnvUpdater::getPosition(){
	return position;
}

inline int EnvUpdater::getBattery(){
	return battery;
}
inline int EnvUpdater::getProgress(){
	return progress;
}

#endif //_EnvUpdater_H_