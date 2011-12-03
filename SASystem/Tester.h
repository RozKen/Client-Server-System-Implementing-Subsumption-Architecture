#ifndef _Tester_H_
#define _Tester_H_

//#define TEST_ROBOT

#ifdef TEST_ROBOT
#include "ModMultiple.hpp"
#include "Resetter.hpp"

void RobotTest();
#endif	//TEST_ROBOT

//#define TEST_LOGGER

#ifdef TEST_LOGGER
#include "Logger.h"
#include <math.h>

void LoggerTest();

#endif	//TEST_LOGGER

#endif	//_Tester_H_