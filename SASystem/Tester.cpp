#include "main.h"

#ifdef TEST_ROBOT
void RobotTest(){
	std::string logPath;
	std::string option = "test.csv";
	logPath = logPathGenerator();

	Robot* robo;
	robo = new Robot();
	std::cout << logPath << "," << option << std::endl;
	robo->setLogDirectoryPath(logPath, option);

	std::vector<SAModule* > mod;
	std::vector<Arbiter* > arb;
	Resetter* reset = new Resetter(2.0f);
	ModMultiple* a = new ModMultiple();
	ModMultiple* b = new ModMultiple();
	ModMultiple* c = new ModMultiple();
	ModMultiple* d = new ModMultiple();
	ModMultiple* e = new ModMultiple();
	ModMultiple* f = new ModMultiple();
	ModMultiple* g = new ModMultiple();

	mod.push_back(reset);
	mod.push_back(a);
	mod.push_back(b);
	mod.push_back(c);
	mod.push_back(d);
	mod.push_back(e);
	mod.push_back(f);
	mod.push_back(g);

	for(int i = 0; i < mod.size(); i++){
		robo->addModule(mod.at(i));

	}
	for(int i = 0; i < mod.size(); i++){
		for(int j = 0; j < mod.at(i)->getNumOfInputPorts(); j++){
			robo->addArbiter(new Arbiter(reset, 0, mod.at(i), j, -2.0));
		}
	}
	//Wire
	Arbiter* ae = new Arbiter(a, 0, e, 0, -2.0);
	//Inhibitor
	Arbiter* be = new Arbiter(b, 0, e, 1, -1.0);
	//Suppressor
	Arbiter* cf = new Arbiter(c, 0, f, 0, 1.0);
	//factor = -0.5
	Arbiter* df = new Arbiter(d, 0, f, 1, -0.5);
	//factor = 0.6
	Arbiter* eg = new Arbiter(e, 0, g, 0, 0.6);
	//factor = 0.8
	Arbiter* fg = new Arbiter(f, 0, g, 1, 0.85);

	arb.push_back(ae);
	arb.push_back(be);
	arb.push_back(cf);
	arb.push_back(df);
	arb.push_back(eg);
	arb.push_back(fg);

	for(int i = 0; i < arb.size(); i++){
		robo->addArbiter(arb.at(i));
	}

	for(int i = 0; i < 100; i++){
		robo->Run();
	}
}
#endif

#ifdef TEST_LOGGER
void LoggerTest(){
	std::cout << "Logger Test Started" << std::endl;
	//Œ»ÝŽž
	time_t now;
	///Œ»ÝŽž‚ðŽæ“¾
	time(&now);
	///LogDirectoryPath‚ðÝ’è
	std::string testLogDirectoryPath = "../../../../analysis/";
	testLogDirectoryPath.append(ctime(&now));
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 12, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 9, 1);
	testLogDirectoryPath.erase(testLogDirectoryPath.size() - 1, 1);
	std::string testLogFileName = "_logTest.csv";
	std::cout << "Log File Path: " << testLogDirectoryPath << testLogFileName << std::endl;

	Logger logger(testLogDirectoryPath, testLogFileName);
	int step = 0;
	float factor = 0.0f;
	float magnitude = 1.0f;
	float signal = 0.0f;
	logger.add("step", &step);
	logger.add("factor", &factor);
	logger.add("magnitude", &magnitude);
	logger.add("signal", &signal);
	std::vector<float>* data = new std::vector<float>();
	
	for(int i = 0; i < 10; i++){
		data->push_back(0.0f);
		std::string title = "data";
		logger.add(title, data, i);
	}

	std::cout << "Logger has set up." << std::endl;

	int MAX_STEP = 100;
	double delta = 1.0 / (double)MAX_STEP;
	for(int i = 0; i < MAX_STEP; i++){
		step = i;
		factor = delta * (double)i;
		signal = (float)0.5 * ( cos(0.5 * PI * (cos((double)factor * PI) + 1.0)) + 1.0 );
		for(int j = 0; j < 10; j++){
			data->at(j) = (float)pow(signal, j);
		}
		logger.Log();
	}

	std::cout << "Logger test has done!" << std::endl;
}
#endif	//TEST_LOGGER
