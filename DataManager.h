#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <unordered_map>
#include <string>
#include "Pipe.h"
#include "CS.h"

class DataManager {
public:
    // Сохранение данных труб и компрессорных станций в файл
    static void saveToFile(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations, const std::string& filename);

    // Загрузка данных труб и компрессорных станций из файла
    static void loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename);
};

#endif // DATAMANAGER_H
