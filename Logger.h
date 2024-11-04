#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

class Logger {
public:
    // Конструктор с указанием файла для логирования
    explicit Logger(const std::string &filename);
    
    // Деструктор закрывает файл, если он открыт
    ~Logger();

    // Метод для записи лога
    void log(const std::string &action);

private:
    std::ofstream logFile;

    // Метод для получения текущего времени в формате строки
    std::string getCurrentTime();
};

#endif // LOGGER_H
