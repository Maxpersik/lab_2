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
double inputDoubleInRange(const string& prompt, double minValue, double maxValue);
bool isNumber(const std::string& s);
long numberOrDefault(const string& command);
long numberInRange(const string& prompt, long minValue, long maxValue);

#endif
