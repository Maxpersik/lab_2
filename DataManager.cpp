//#include "DataManager.h"
//#include <fstream>
//#include <iostream>
//
//void DataManager::saveToFile(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& csStations, const std::string& filename) {
//    std::ofstream outFile(filename);
//    if (outFile.is_open()) {
//        // Сохраняем все объекты Pipe
//        for (const auto& [id, pipe] : pipes) {
//            if (!pipe.name.empty()) {
//                outFile << "PIPE" << std::endl;
//                outFile << id << std::endl;
//                outFile << pipe.name << std::endl;
//                outFile << pipe.length << std::endl;
//                outFile << pipe.diameter << std::endl;
//                outFile << (pipe.repairStatus ? "1" : "0") << std::endl;
//            }
//        }
//
//        // Сохраняем все объекты CS
//        for (const auto& [id, cs] : csStations) {
//            if (!cs.name.empty()) {
//                outFile << "CS" << std::endl;
//                outFile << id << std::endl;
//                outFile << cs.name << std::endl;
//                outFile << cs.workshopNumber << std::endl;
//                outFile << cs.workshopNumberInWork << std::endl;
//                outFile << cs.efficiency << std::endl;
//            }
//        }
//
//        outFile.close();
//        std::cout << "Данные сохранены в файл " << filename << std::endl;
//    } else {
//        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
//    }
//}
//
//void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& csStations, const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (inFile.is_open()) {
//        std::string line;
//        while (std::getline(inFile, line)) {
//            try {
//                if (line == "PIPE") {
//                    int id;
//                    Pipe pipe;
//
//                    // Чтение идентификатора и данных Pipe
//                    std::getline(inFile, line);
//                    id = std::stoi(line);
//
//                    std::getline(inFile, pipe.name);
//                    std::getline(inFile, line);
//                    pipe.length = std::stod(line);
//                    std::getline(inFile, line);
//                    pipe.diameter = std::stod(line);
//                    std::getline(inFile, line);
//                    pipe.repairStatus = (line == "1");
//
//                    // Валидация данных
//                    if (pipe.length < 0.1 || pipe.length > 10000) {
//                        std::cerr << "Ошибка: длина трубы некорректна для id " << id << std::endl;
//                        continue;
//                    }
//                    if (pipe.diameter < 10 || pipe.diameter > 10000) {
//                        std::cerr << "Ошибка: диаметр трубы некорректен для id " << id << std::endl;
//                        continue;
//                    }
//
//                    pipes[id] = pipe;
//
//                } else if (line == "CS") {
//                    int id;
//                    CompressorStation cs;
//
//                    // Чтение идентификатора и данных CS
//                    std::getline(inFile, line);
//                    id = std::stoi(line);
//
//                    std::getline(inFile, cs.name);
//                    std::getline(inFile, line);
//                    cs.workshopNumber = std::stoi(line);
//                    std::getline(inFile, line);
//                    cs.workshopNumberInWork = std::stoi(line);
//                    std::getline(inFile, line);
//                    cs.efficiency = std::stod(line);
//
//                    // Валидация данных
//                    if (cs.workshopNumber < 1 || cs.workshopNumber > 1000) {
//                        std::cerr << "Ошибка: количество цехов некорректно для id " << id << std::endl;
//                        continue;
//                    }
//                    if (cs.workshopNumberInWork < 1 || cs.workshopNumberInWork > cs.workshopNumber) {
//                        std::cerr << "Ошибка: количество рабочих цехов некорректно для id " << id << std::endl;
//                        continue;
//                    }
//                    if (cs.efficiency < 0.1 || cs.efficiency > 100) {
//                        std::cerr << "Ошибка: эффективность некорректна для id " << id << std::endl;
//                        continue;
//                    }
//
//                    csStations[id] = cs;
//                }
//            } catch (const std::invalid_argument& e) {
//                std::cerr << "Ошибка: некорректный формат данных в файле." << std::endl;
//                continue;
//            } catch (const std::out_of_range& e) {
//                std::cerr << "Ошибка: значение из файла выходит за пределы допустимого диапазона." << std::endl;
//                continue;
//            }
//        }
//        inFile.close();
//        std::cout << "Данные загружены из файла " << filename << std::endl;
//    } else {
//        std::cerr << "Не удалось открыть файл для чтения: " << filename << std::endl;
//    }
//}

#include "DataManager.h"
#include <fstream>
#include <iostream>

void DataManager::saveToFile(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        // Сохраняем все трубы
        for (const auto& [id, pipe] : pipes) {
            outFile << "PIPE" << std::endl;
            outFile << id << std::endl;
            outFile << pipe.name << std::endl;
            outFile << pipe.length << std::endl;
            outFile << pipe.diameter << std::endl;
            outFile << (pipe.repairStatus ? "1" : "0") << std::endl;
        }

        // Сохраняем все компрессорные станции
        for (const auto& [id, station] : stations) {
            outFile << "CS" << std::endl;
            outFile << id << std::endl;
            outFile << station.name << std::endl;
            outFile << station.workshopNumber << std::endl;
            outFile << station.workshopNumberInWork << std::endl;
            outFile << station.efficiency << std::endl;
        }

        std::cout << "Данные успешно сохранены в файл " << filename << "\n";
    } else {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << "\n";
    }
}

void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            if (line == "PIPE") {
                Pipe pipe;
                int id;
                inFile >> id;
                inFile.ignore(); // Игнорируем перевод строки

                std::getline(inFile, pipe.name);
                inFile >> pipe.length >> pipe.diameter >> pipe.repairStatus;
                inFile.ignore();

                pipe.setId(id);
                pipes[id] = pipe;

            } else if (line == "CS") {
                CompressorStation station;
                int id;
                inFile >> id;
                inFile.ignore(); // Игнорируем перевод строки

                std::getline(inFile, station.name);
                inFile >> station.workshopNumber >> station.workshopNumberInWork >> station.efficiency;
                inFile.ignore();

                station.setId(id);
                stations[id] = station;
            }
        }
        std::cout << "Данные успешно загружены из файла " << filename << "\n";
    } else {
        std::cerr << "Ошибка при открытии файла для чтения: " << filename << "\n";
    }
}
