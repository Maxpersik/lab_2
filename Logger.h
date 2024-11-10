#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <mutex>  // Для std::mutex

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
    std::mutex logMutex;  // Мьютекс для синхронизации записи

    // Метод для получения текущего времени в формате строки
    std::string getCurrentTime();
};

extern Logger logger;

#endif // LOGGER_H
