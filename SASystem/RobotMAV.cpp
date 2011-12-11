#include "RobotMAV.h"
#include "World.h"

RobotMAV::RobotMAV(){
	Initialize();
}

RobotMAV::RobotMAV(std::string directoryPath, std::string fileName)
	:Robot(directoryPath, fileName){
	Initialize();
}

RobotMAV::~RobotMAV(){
	delete(geoMap);
	delete(radMap);
	delete(nearest);
	delete(color);
	delete(modColor);
}

void RobotMAV::Initialize(){
	///Member�̔z���������
	for(int i = 0; i < FIELD_SIZE; i++){
		for(int j = 0; j < FIELD_SIZE; j++){
			geoMap[i][j] = NO_DATA;
			radMap[i][j] = NO_DATA;
		}
	}
	
	for(int i = 0; i < 3; i++){
		color[i] = 1.0f;
		for(int j = 0; j < 3; j++){
			modColor[i][j] = 1.0f;
		}
	}

	this->nearest = new std::vector<RobotMAV *>();

	///Sensor��ǉ�
	///////Sensor�ɂ͏����l���^����K�v������.
	//Battery�Z���T��ǉ�
	SenseBattery* sB = new SenseBattery();
	this->addModule(sB);
	
	//�ʒu�Z���T��ǉ�
	SensePos* sP = new SensePos();
	this->addModule(sP);
	
	//�����Z���T��ǉ�
	SenseDirection* sD = new SenseDirection();
	this->addModule(sD);

	//�����Z���T��ǉ�
	SenseRange* sR = new SenseRange();
	this->addModule(sR);
	

	//���ː��ʃZ���T��ǉ�
	SenseRadiation* sRad = new SenseRadiation();
	this->addModule(sRad);

	//Network�ڑ��Z���T��ǉ�
	SenseNet* sN = new SenseNet();
	this->addModule(sN);

	///Controller��ǉ�
	///Avoid : Red
	ContAvoid* cAv = new ContAvoid();
	this->addModule(cAv);
	modColor[0][0] = 1.0f;
	modColor[0][1] = 0.0f;
	modColor[0][2] = 0.0f;
	///Alive : Yellow
	ContAlive* cAl = new ContAlive();
	this->addModule(cAl);	
	modColor[1][0] = 1.0f;
	modColor[1][1] = 1.0f;
	modColor[1][2] = 0.0f;
	///Wander : Gray
	ContWander* cW = new ContWander();
	this->addModule(cW);
	modColor[2][0] = 0.5f;
	modColor[2][1] = 0.5f;
	modColor[2][2] = 0.5f;

	//�b��I�ɓ���ւ��Ă݂�
	///ContConnect : White
	ContConnect* cC = new ContConnect();
	this->addModule(cC);
	modColor[3][0] = 1.0f;
	modColor[3][1] = 1.0f;
	modColor[3][2] = 1.0f;

	///ContExplore : Sky Blue
	ContExplore* cE = new ContExplore();
	this->addModule(cE);
	modColor[4][0] = 0.0f;
	modColor[4][1] = 1.0f;
	modColor[4][2] = 1.0f;

	/*

	///ContExplore : Sky Blue
	ContExplore* cE = new ContExplore();
	this->addModule(cE);
	modColor[3][0] = 0.0f;
	modColor[3][1] = 1.0f;
	modColor[3][2] = 1.0f;

	///ContConnect : White
	ContConnect* cC = new ContConnect();
	this->addModule(cC);
	modColor[4][0] = 1.0f;
	modColor[4][1] = 1.0f;
	modColor[4][2] = 1.0f;

	*/

	/////Actuator��ǉ�
	//�ʒuActuator��ǉ�
	ActPos* aP = new ActPos();
	this->addModule(aP);

	std::cout << "Number of Modules" << this->getNumOfModules() << std::endl;

	///Arbiter��ǉ�
	///���WireObjects
	
	///0 - 11 :�����Z���T->Avoid
	Arbiter* sRcAv[RANGE_DIV];
	for(int i = 0; i < RANGE_DIV; i++){
		sRcAv[i] = new Arbiter(sR, i, cAv, i, 2.0f);
		this->addArbiter(sRcAv[i]);
	}

	///12 : �����Z���T->Avoid
	Arbiter* sDcAv;
	sDcAv = new Arbiter(sD, 0, cAv, RANGE_DIV, 2.0f);
	this->addArbiter(sDcAv);
	
	///13 : Battery�Z���T->Alive
	Arbiter* sBcAl = new Arbiter(sB, 0, cAl, 0, 2.0f);
	this->addArbiter(sBcAl);
	
	///14, 15:�ʒu�Z���T->Alive
	Arbiter* sPcAl[2];
	for(int i = 0; i < 2; i++){
		sPcAl[i] = new Arbiter(sP, i , cAl, i + 1, 2.0f);
		this->addArbiter(sPcAl[i]);
	}
	
	///16, 17:�ʒu�Z���T->Wander
	Arbiter* sPcW[2];
	for(int i = 0; i < 2; i++){
		sPcW[i] = new Arbiter(sP, i, cW, i, 2.0f);
		this->addArbiter(sPcW[i]);
	}
	
	///18 - 27: Network�Z���T->Connect
	Arbiter* sNcC[WIFI_CONNECT * 2];
	for(int i = 0; i < WIFI_CONNECT * 2; i++){
		sNcC[i] = new Arbiter(sN, i, cC, i, 2.0f);
		this->addArbiter(sNcC[i]);
	}

	/////////�ȉ��̏��Ԃ͏d�v�D/////////
	/////////�K�w�̒Ⴂ�҂�����{���邽��////
	///28, 29:Avoid->�ʒuActuator	//Suppress���ꂽ�f�[�^�������Wire
	Arbiter* cAvaP[2];
	for(int i = 0; i < 2; i++){
		cAvaP[i] = new Arbiter(cAv, i, aP, i, 2.0f);
		this->addArbiter(cAvaP[i]);
	}
	
	///30, 31:Suppress Alive -> �ʒuActuator
	Arbiter* cAlaP[2];
	for(int i = 0; i < 2; i++){
		cAlaP[i] = new Arbiter(cAl, i, aP, i, 1.0f);
		this->addArbiter(cAlaP[i]);
	}
	
	///32, 33:Suppress Wander -> �ʒuActuator
	Arbiter* cWaP[2];
	for(int i = 0; i < 2; i++){
		cWaP[i] = new Arbiter(cW, i, aP, i, 1.0f);
		this->addArbiter(cWaP[i]);
	}
	//�b��I�ɓ���ւ��Ă݂�
	
	///34, 35:Suppress Connect -> �ʒuActuator
	Arbiter* cCaP[2];
	for(int i = 0; i < 2; i++){
		cCaP[i] = new Arbiter(cC, i, aP, i, 1.0f);
		this->addArbiter(cCaP[i]);
	}

	///36, 37:Suppress Explore -> �ʒuActuator
	Arbiter* cEaP[2];
	for(int i = 0; i < 2; i++){
		cEaP[i] = new Arbiter(cE, i, aP, i, 1.0f);
		this->addArbiter(cEaP[i]);
	}

	/*
	///34, 35:Suppress Explore -> �ʒuActuator
	Arbiter* cEaP[2];
	for(int i = 0; i < 2; i++){
		cEaP[i] = new Arbiter(cE, i, aP, i, 1.0f);
		this->addArbiter(cEaP[i]);
	}

	///36, 37:Suppress Connect -> �ʒuActuator
	Arbiter* cCaP[2];
	for(int i = 0; i < 2; i++){
		cCaP[i] = new Arbiter(cC, i, aP, i, 1.0f);
		this->addArbiter(cCaP[i]);
	}
	*/
	
	std::cout << "Number of Arbiters" << this->getNumOfArbiters() << std::endl;
}

void RobotMAV::Run(){
	//Robot�ւ�Input����������
	ProcessInputs();
	//Robot�̊eModule�𓮂���
	RunModules();
	//Arbiter���쓮������
	ProcessArbiters();
	//Robot�����Output����������
	ProcessOutputs();
	//�����̏����X�V����
	Update();
	//Log�����
	Log();
}

void RobotMAV::Update(){
	updateInnerGeoMap();
	updateInnerRadMap();
}

float RobotMAV::getDX() const {
	return this->getOutput(0);
}

float RobotMAV::getDY() const {
	return this->getOutput(1);
}

float RobotMAV::getBattery() const{
	return this->getInput(0);
}
void RobotMAV::setBattery(float value){
	this->setInput(0, value);
}
float RobotMAV::getPosX() const{
	return this->getInput(1);
}
void  RobotMAV::setPosX(float value){
	this->setInput(1, value);
}
float RobotMAV::getPosY() const{
	return this->getInput(2);
}
void RobotMAV::setPosY(float value){
	this->setInput(2, value);
}

float RobotMAV::getDirection() const{
	return this->getInput(3);
}
void RobotMAV::setDirection(float value){
	this->setInput(3, value);
}

float RobotMAV::getRange(int index) const{
	return this->getInput(4 + index);
}

void RobotMAV::setRange(int index, float value){
	this->setInput(4 + index, value);
}

float RobotMAV::getRad(int index) const{
	return this->getInput(4 + RANGE_DIV + index);
}

void RobotMAV::setRad(int index, float value){
	this->setInput(4 + RANGE_DIV + index, value);
}

float RobotMAV::getRobot(int index, bool x){
	int odd = 1;
	if(x){
		odd = 0;
	}
	return this->getInput(4 + RANGE_DIV + MAX_AREA + index * 2 + odd);
}

void RobotMAV::setRobot(int index, float value, bool x){
	int odd = 1;
	if(x){
		odd = 0;
	}
	this->setInput(4 + RANGE_DIV + MAX_AREA + index * 2 + odd, value);
}

float RobotMAV::getColorR() const{
	return this->color[0];
}

float RobotMAV::getColorG() const{
	return this->color[1];
}
float RobotMAV::getColorB() const{
	return this->color[2];
}

void RobotMAV::ProcessArbiters(){
	float ratios[NUM_OF_LAYERS - 1];
	for(int i = 0; i < arbiters->size(); i++){
		arbiters->at(i)->Run();
		switch(i){
		case 30:	//Alive Suppress Avoid and ActPos
			ratios[0] = arbiters->at(i)->getCurrentRatio();
			break;
		case 32:	//Wander Suppress Alive, Avoid and ActPos
			ratios[1] = arbiters->at(i)->getCurrentRatio();
			break;
		case 33:	//Explore Suppress Wander, Alive, Avoid and ActPos
			ratios[2] = arbiters->at(i)->getCurrentRatio();
			break;
		case 36:	//Connect Suppress Explore, Wander, Alive, Avoid and ActPos
			ratios[3] = arbiters->at(i)->getCurrentRatio();
			break;
		default:
			break;
		}
	}

	///Set RobotColor According to Suppress
	for(int j = 0; j < 3; j++){
		color[j] = modColor[NUM_OF_LAYERS - 1][j] * ratios[NUM_OF_LAYERS - 2] 
		+ modColor[NUM_OF_LAYERS - 2][j] * (1.0f - ratios[NUM_OF_LAYERS - 2]);
	}
	for(int i = NUM_OF_LAYERS - 3; i >= 0; i--){
		for(int j= 0; j < 3; j++){
			color[j] = color[j] * ratios[i] + modColor[i][j] * (1.0f - ratios[i]);
		}
	}
	/*
	std::cout << "colors: ";
	for(int j = 0; j < 3; j++){
		std::cout << color[j] << ",";
	}
	std::cout << std::endl;
	*/
}

void RobotMAV::updateInnerGeoMap(){
	for(int i = 0; i < RANGE_DIV; i++){
		float range = this->getRange(i);
		if(range < RANGE_DANGER){
			float dx = range * cos( (double)i * PI * RANGE_DEG / 180.0);
			float dy = range * sin( (double)i * PI * RANGE_DEG / 180.0);
			int x = round(this->getPosX() + dx);
			int y = round(this->getPosY() + dy);
			geoMap[x][y] = OUTOFAREA;
		}
	}
}

void RobotMAV::updateInnerRadMap(){
	for(int i = 0; i < MAX_AREA; i++){
		int x = round(this->getPosX()) + ((World *)(this->parent))->getHash(0, i);
		int y = round(this->getPosY()) + ((World *)(this->parent))->getHash(1, i);
		radMap[x][y] = this->getRad(i);
	}
}

SenseNet* RobotMAV::getSenseNet(){
	///���݂�SenseNet��Module��index == 3�̂Ƃ���œo�^����Ă���D
	///�����CModule��o�^���鏇�ԂɕύX������΁C�������ύX����K�v������D
	return (SenseNet*)(this->modules->at(3));
}

void RobotMAV::pushNearest(RobotMAV * robot){
	this->nearest->push_back(robot);
	numOfNearestRobots = nearest->size();
}

RobotMAV* RobotMAV::getNearestAt(int index){
	return this->nearest->at(index);
}

std::vector<RobotMAV *>* RobotMAV::getNearest(){
	return this->nearest;
}

void RobotMAV::clearNearest(){
	this->nearest->clear();
	numOfNearestRobots = 0;
}

int RobotMAV::getNumOfNearestRobots() const{
	return numOfNearestRobots;
}