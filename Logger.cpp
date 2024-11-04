#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

class Logger {
public:
    // Конструктор с указанием файла для логирования
    Logger(const std::string &filename) : logFile(filename, std::ios::app) {
        if (!logFile.is_open()) {
            std::cerr << "Не удалось открыть файл логирования!" << std::endl;
        }
    }
    
    // Деструктор закрывает файл, если он открыт
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    void log(const string &action) {
        ofstream logFile("logging.txt", ios::app);
        if (logFile.is_open()) {
            time_t N = time(0);
            char *dt = ctime(&N);
            logFile << dt << " -- " << action << endl;
            logFile.close();
        } else {
            cerr << "Не удалось открыть файл логирования!" << endl;
        }
    }
    
private:
    std::ofstream logFile;

    // Метод для получения текущего времени в формате строки
    std::string getCurrentTime() {
        time_t now = time(0);
        char buf[80];
        strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", localtime(&now));
        return std::string(buf);
    }
};
