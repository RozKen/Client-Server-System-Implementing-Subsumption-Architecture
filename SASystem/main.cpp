#include "main.h"

#include <string>
#include <GL/glut.h>
#include <iostream>

#include <Windows.h>
#include <time.h>
#include "Utilities.h"

///////For OpenGL Manipulation///////
float zoom = 15.0f;
//X-axis Rotation [degree]
float rotx = 30.0f;
//Y-axis Rotation [degree]
float roty = 0.0f;
float tx = 0;
/////////////////////////何でマイナスなの？
float ty = -30.0f;
int lastx=0;
int lasty=0;
unsigned char Buttons[3] = {0};

void Init();
void glIdle();
void glDisplay();
void glReshape(int w, int h);
void glMotion(int x,int y);
void glMouse(int b,int s,int x,int y);
void glKeyboard(unsigned char key , int x, int y);

World* world;
clock_t start, end;

int main(int argc, char** argv){	

#ifdef TEST_ROBOT
	RobotTest();
#endif	//TEST_ROBOT

#ifdef TEST_LOGGER
	LoggerTest();
#endif	//TEST_LOGGER

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Radiation Mapping Agents");

	glutDisplayFunc(glDisplay);
	glutReshapeFunc(glReshape);
	glutMouseFunc(glMouse);
	glutMotionFunc(glMotion);
	glutIdleFunc(glIdle);

	Init();

	/*for(int i = 0; i < 100; i++){
		world->Run();
	}*/

	glutMainLoop();
	//std::cout << "Enter any character and Press 'Enter Key'" << std::endl;
	
	//std::string input;
	//std::cin >> input;
	return 0;
}

void Init(){
	glEnable(GL_DEPTH_TEST);

	std::string directory = logPathGenerator();
	world = new World(directory, "world.csv");
	std::cout << "world:Directory: " << world->getLogFilePath() << std::endl;
	RobotMAV* mav1 = new RobotMAV(directory, "mav1.csv");
	RobotMAV* mav2 = new RobotMAV(directory, "mav2.csv");
	world->addRobot(mav1);
	world->addRobot(mav2);
	//初期値を設定
	RobotMAV* tmp;
	//最初の位置のX座標をランダムにずらす
	Random<boost::uniform_int<> > _numBatGen(-15, 15);

	for(int i = 0; i < world->getNumOfModules(); i++){
		tmp = world->getRobot(i);
		tmp->setInput(0, 100.0f);
		tmp->setInput(1, START_X + (float)_numBatGen());
		tmp->setInput(2, START_Y + (float)_numBatGen());
	}
	start = clock();
}

void glIdle(){
	end = clock();
	if((double)(end - start) > TIME_STEP){
		world->Run();
		start = clock();
	}
	glutPostRedisplay();
	//Sleep( 500 );
}


void glDisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0,0,-zoom);
	glTranslatef(tx,ty,0);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);	

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	//Draw Robots as Spheres
	RobotMAV* robot;

	double offset = -50.0;		//FIELD_SIZEの半分
	glTranslatef(offset, 0, offset);
		//ここ手作業で更新 insideX[world->getNumOfModules()]
		bool insideX[2];
		//Draw Barriers as Boxes
		for(int i = 0; i < FIELD_SIZE; i++){
			for(int iRobot = 0; iRobot < world->getNumOfModules(); iRobot++){
				insideX[iRobot] = false;
				robot = world->getRobot(iRobot);
				if(i > robot->getPosX() - RANGE && i < robot->getPosX() + RANGE){
					insideX[iRobot] = true;
				}
			}
			for(int j = 0; j < FIELD_SIZE; j++){
				if(world->geoField[i][j] == OUTOFAREA){
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
					for(int iRobot = 0; iRobot < world->getNumOfModules(); iRobot++){
						if(insideX[iRobot]){
							robot = world->getRobot(iRobot);
							if(j > robot->getPosY() - RANGE && j < robot->getPosY() + RANGE){
								glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
							}
						}
					}
					glTranslatef((GLfloat)i, 0, (GLfloat)j);
					glutSolidCube(1.0);
					glTranslatef((GLfloat)-i, 0, (GLfloat)-j);
				}else{
					glColor4f(0.0f, 0.2f, 0.0f, 1.0f);
					for(int iRobot = 0; iRobot < world->getNumOfModules(); iRobot++){
						if(insideX[iRobot]){
							robot = world->getRobot(iRobot);
							if(j > robot->getPosY() - RANGE && j < robot->getPosY() + RANGE){
								glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
							}
						}
					}
					glTranslatef((GLfloat)i, -1.0f, (GLfloat)j);
					glutSolidCube(1.0);
					glTranslatef((GLfloat)-i, +1.0f, (GLfloat)-j);
				}
			}
		}

		for(int index = 0; index < world->getNumOfModules(); index++){
			robot = world->getRobot(index);
			//std::cout << "color " << robot->getColorR() << ", " << robot->getColorG();
			//std::cout << ", " << robot->getColorB() << std::endl;
			glColor4f(robot->getColorR(), robot->getColorG()
				, robot->getColorB(), 1.0f);
			float x = robot->getPosX();
			float y = robot->getPosY();
			glTranslatef(x, 0, y);
			glutSolidSphere(0.5, 12, 12);
			glTranslatef(-x, -0, -y);
		}

	glTranslatef(-offset, 0, -offset);

	glColor4f(0.0f, 0.8f, 0.0f, 0.8f);

	// draw grid
	glBegin(GL_LINES);
	//glTranslatef(-0.5, -0.5, -0.5);
	for(int i=-50;i<=50;++i) {
		glVertex3f(i - 0.5,-0.5,-50 - 0.5);
		glVertex3f(i - 0.5,-0.5,50 -0.5);

		glVertex3f(50 - 0.5,-0.5,i - 0.5);
		glVertex3f(-50 - 0.5,-0.5,i - 0.5);
	}
	//glTranslatef(0.5, 0.5, 0.5);
	glEnd();

	glutSwapBuffers();
}

void glReshape(int w, int h)
{
	// prevent divide by 0 error when minimised
	if(w==0) 
		h = 1;

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,0.1,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glMotion(int x, int y){
	int diffx=x-lastx;
	int diffy=y-lasty;
	lastx=x;
	lasty=y;

	if( Buttons[0] && Buttons[2] )
	{
		zoom -= (float) 0.05f * diffy;
	}else if( Buttons[0] ){
		rotx += (float) 0.5f * diffy;
		roty += (float) 0.5f * diffx;		
	}else if( Buttons[2] ){
		tx += (float) 0.05f * diffx;
		ty -= (float) 0.05f * diffy;
	}
	glutPostRedisplay();
}

void glMouse(int b,int s,int x,int y)
{
	lastx=x;
	lasty=y;
	switch(b)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = ((GLUT_DOWN==s)?1:0);
		break;
	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = ((GLUT_DOWN==s)?1:0);
		break;
	case GLUT_RIGHT_BUTTON:
		Buttons[2] = ((GLUT_DOWN==s)?1:0);
		break;
	default:
		break;		
	}
	glutPostRedisplay();
}

void glKeyboard(unsigned char key , int x, int y){
	switch(key){
	case 't':
		std::cout << " 't' pushed !" << std::endl;
		break;
	case 27:	//ESC
		exit(0);
		break;
	default:
		break;
	}
}