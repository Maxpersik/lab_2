#include "Utils.h"

using namespace std;

int inputIntInRange(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            if (value >= minValue && value <= maxValue) {
                return value;
            } else {
                cout << "Ошибка: введите число от " << minValue << " до " << maxValue << "." << endl;
            }
        } else {
            cout << "Ошибка: введите корректное целое число." << endl;
        }
    }
}

double inputDoubleInRange(const string& prompt, double minValue, double maxValue) {
    double value;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            if (value >= minValue && value <= maxValue) {
                return value;
            } else {
                cout << "Ошибка: введите число от " << minValue << " до " << maxValue << "." << endl;
            }
        } else {
            cout << "Ошибка: введите корректное число." << endl;
        }
    }
}

bool isNumber(const std::string& s)
{
    return  s.length() < 2 and !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

long numberOrDefault(const string& command){
    if (isNumber(command)) {
        return strtol(command.c_str(), NULL, 10);
    }
    return -1;
}

long numberInRange(const string& prompt, long minValue, long maxValue) {
    long value;
    while (true) {
        value = numberOrDefault(prompt);
        if (value >= minValue && value <= maxValue) {
            return value;
        } else {
            std::cout << "Ошибка: введите число от " << minValue << " до " << maxValue << ". Попробуйте снова." << std::endl;
        }
    }
}
