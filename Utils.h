#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void log(const string &action);
long numberOrDefault(const string &input);
int inputIntInRange(const string &prompt, int minValue, int maxValue);

#endif
