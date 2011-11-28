#ifndef _World_H_
#define _World_H_

#include "RobotMAV.h"

/**
	@brief 位置を表す構造体
	x, yの2次元
 */
typedef struct {
	int x;
	int y;
} position;

class World : public Robot{
public:
	World();

	/**
		@brief 世界を1clock進める
		<ol>
			<li>黒板にSensor値をセット</li>
			<li>各ロボットを実行</li>
			<li>各ロボットの黒板からSensor値を入手</li>
			<li>新たなSensor値を記録</li>
		</ol>
	 */
	virtual void Run();
	virtual void RunRobots();
	/**
		@brief WorldにRobotを追加する
	 */
	virtual void addRobot(RobotMAV* robot);
	//void moveRobot(int deltaX, int deltaY);
	//std::vector<int>* getRobotMap(int x, int y);
	/**
		@brief 放射線量Mapに値を記入する
		@param x Robotのx座標
		@param y Robotのy座標
		@param data Robotの放射線量に関するSensor Data
	 */
	//void setRadiationMap(int x, int y, std::vector<float>* data);
	/**
		@brief 二酸化炭素量Mapに値を記入する
		@param x Robotのx座標
		@param y Robotのy座標
		@param data Robotの二酸化炭素量に関するSensor Data
	 */
	//void setCOOMap(int x, int y, std::vector<float>* data);
	//std::vector<float>* getRadiationMap(int x, int y);
	//std::vector<float>* getCOOMap(int x, int y);
	/**
		@brief indexが指し示すx, y座標を得るためのhash[x/y][index]
	 */
	int hash[2][HASH_MAX];
protected:
	/**
		@brief各ロボットの位置を保持する配列．
		@sa position
	 */
	//std::vector<position> *robotPos;
	///世界全体の放射線量Map
	//float radiationMap[FIELD_SIZE][FIELD_SIZE];
	///世界全体の二酸化炭素量Map
	//float cooMap[FIELD_SIZE][FIELD_SIZE];
	
};

inline World::World(){
	//robotPos = new std::vector<position>();
	int tmp[2][HASH_MAX] = {
		{0,0,1,0,-1,0,1,2,1,0,-1,-2,-1,0,1,2,3,2,1,0,-1,-2,-3,-2,-1},
		{0,1,0,-1,0,2,1,0,-1,-2,-1,0,1,3,2,1,0,-1,-2,-3,-2,-1,0,1,2}
	};
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < HASH_MAX; j++){
			hash[i][j] = tmp[i][j];
		}
	}
}

inline void World::addRobot(RobotMAV* robot){
	//Robotで定義されているaddModuleを実行
	this->addModule(robot);
}
/*
inline void World::setRadiationMap(int x, int y, std::vector<float>* data){
	for(int i; i < MAX_AREA; i++){
		radiationMap[ x + hash[0][i] ][ y + hash[1][i] ] = data->at(i);
	}
}

inline void World::setCOOMap(int x, int y, std::vector<float>* data){
	for(int i; i < MAX_AREA; i++){
		cooMap[ x + hash[0][i] ][ y + hash[1][i] ] = data->at(i);
	}
}

inline std::vector<float>* World::getRadiationMap(int x, int y){
	std::vector<float>* data = new std::vector<float>();
	for(int i; i < MAX_AREA; i++){
		data->push_back(radiationMap[ x + hash[0][i] ][ y + hash[1][i] ]);
	}
	return data;
}

inline std::vector<float>* World::getCOOMap(int x, int y){
	std::vector<float>* data = new std::vector<float>();
	for(int i; i < MAX_AREA; i++){
		data->push_back(cooMap[ x + hash[0][i] ][ y + hash[1][i] ]);
	}
	return data;
}
*/
#endif	//_World_H_