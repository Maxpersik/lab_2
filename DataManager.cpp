#include "DataManager.h"
#include <fstream>
#include <iostream>
#include "Pipe.h"       
#include "CS.h"

void DataManager::saveToFile(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << "\n";
        return;
    }

    // Сохранение труб
    outFile << pipes.size() << "\n";
    std::cout << "Сохранение труб (" << pipes.size() << " шт.)...\n";
    for (const auto& [id, pipe] : pipes) {
        outFile << "PIPE\n";
        outFile << pipe.id << "\n"
                << pipe.name << "\n"
                << pipe.length << "\n"
                << pipe.diameter << "\n"
                << pipe.repairStatus << "\n";
    }

    // Сохранение станций
    outFile << stations.size() << "\n";
    std::cout << "Сохранение станций (" << stations.size() << " шт.)...\n";
    for (const auto& [id, station] : stations) {
        outFile << "CS\n";
        outFile << station.id << "\n"
                << station.name << "\n"
                << station.workshopNumber << "\n"
                << station.workshopNumberInWork << "\n"
                << station.efficiency << "\n";
    }

    outFile.close();
    std::cout << "Данные успешно сохранены в файл: " << filename << "\n";
}

void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка при открытии файла для чтения: " << filename << "\n";
        return;
    }

    pipes.clear();
    stations.clear();

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "PIPE") {
            Pipe pipe;
            int id;

            inFile >> id;
            inFile.ignore();

            std::getline(inFile, pipe.name);
            inFile >> pipe.length;
            inFile >> pipe.diameter;
            inFile >> pipe.repairStatus;
            inFile.ignore();

            pipe.id = id;
            pipes[id] = pipe;
        } else if (line == "CS") {
            CompressorStation station;
            int id;

            inFile >> id;
            inFile.ignore();

            std::getline(inFile, station.name);
            inFile >> station.workshopNumber;
            inFile >> station.workshopNumberInWork;
            inFile >> station.efficiency;
            inFile.ignore();

            station.id = id;
            stations[id] = station;
        }
    }

    inFile.close();
    std::cout << "Данные успешно загружены из файла: " << filename << "\n";
}
