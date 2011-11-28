#ifndef _World_H_
#define _World_H_

#include "RobotMAV.h"

/**
	@brief �ʒu��\���\����
	x, y��2����
 */
typedef struct {
	int x;
	int y;
} position;

class World : public Robot{
public:
	World();

	/**
		@brief ���E��1clock�i�߂�
		<ol>
			<li>����Sensor�l���Z�b�g</li>
			<li>�e���{�b�g�����s</li>
			<li>�e���{�b�g�̍�����Sensor�l�����</li>
			<li>�V����Sensor�l���L�^</li>
		</ol>
	 */
	virtual void Run();
	virtual void RunRobots();
	/**
		@brief World��Robot��ǉ�����
	 */
	virtual void addRobot(RobotMAV* robot);
	//void moveRobot(int deltaX, int deltaY);
	//std::vector<int>* getRobotMap(int x, int y);
	/**
		@brief ���ː���Map�ɒl���L������
		@param x Robot��x���W
		@param y Robot��y���W
		@param data Robot�̕��ː��ʂɊւ���Sensor Data
	 */
	//void setRadiationMap(int x, int y, std::vector<float>* data);
	/**
		@brief ��_���Y�f��Map�ɒl���L������
		@param x Robot��x���W
		@param y Robot��y���W
		@param data Robot�̓�_���Y�f�ʂɊւ���Sensor Data
	 */
	//void setCOOMap(int x, int y, std::vector<float>* data);
	//std::vector<float>* getRadiationMap(int x, int y);
	//std::vector<float>* getCOOMap(int x, int y);
	/**
		@brief index���w������x, y���W�𓾂邽�߂�hash[x/y][index]
	 */
	int hash[2][HASH_MAX];
protected:
	/**
		@brief�e���{�b�g�̈ʒu��ێ�����z��D
		@sa position
	 */
	//std::vector<position> *robotPos;
	///���E�S�̂̕��ː���Map
	//float radiationMap[FIELD_SIZE][FIELD_SIZE];
	///���E�S�̂̓�_���Y�f��Map
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
	//Robot�Œ�`����Ă���addModule�����s
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