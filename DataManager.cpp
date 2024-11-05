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

//#include "DataManager.h"
//#include <fstream>
//#include <iostream>
//
//void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (inFile.is_open()) {
//        std::string line;
//        while (std::getline(inFile, line)) {
//            if (line == "PIPE") {
//                Pipe pipe;
//                int id;
//
//                inFile >> id;
//                inFile.ignore(); // Пропускаем перевод строки после ID
//
//                std::getline(inFile, pipe.name); // Читаем имя трубы
//                inFile >> pipe.length;           // Читаем длину трубы
//                inFile >> pipe.diameter;         // Читаем диаметр трубы
//                inFile >> pipe.repairStatus;     // Читаем статус ремонта (0 или 1)
//                inFile.ignore(); // Пропускаем перевод строки после последнего значения
//
//                pipe.setId(id);                  // Устанавливаем ID
//                pipes[id] = pipe;                // Добавляем в контейнер pipes
//                std::cout << "Загружена труба с ID " << id << ": " << pipe.name << "\n"; // Отладка
//
//            } else if (line == "CS") {
//                CompressorStation station;
//                int id;
//
//                inFile >> id;
//                inFile.ignore(); // Пропускаем перевод строки после ID
//
//                std::getline(inFile, station.name);          // Читаем имя станции
//                inFile >> station.workshopNumber;            // Читаем общее количество цехов
//                inFile >> station.workshopNumberInWork;      // Читаем количество рабочих цехов
//                inFile >> station.efficiency;               // Читаем эффективность
//                inFile.ignore(); // Пропускаем перевод строки после последнего значения
//
//                station.setId(id);                          // Устанавливаем ID
//                stations[id] = station;                     // Добавляем в контейнер stations
//                std::cout << "Загружена станция с ID " << id << ": " << station.name << "\n"; // Отладка
//            }
//        }
//        std::cout << "Данные успешно загружены из файла " << filename << "\n";
//    } else {
//        std::cerr << "Ошибка при открытии файла для чтения: " << filename << "\n";
//    }
//}
//#include "DataManager.h"
//#include <fstream>
//#include <iostream>
//#include <stdexcept>
//
//void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
//    std::ifstream inFile(filename);
//    if (inFile.is_open()) {
//        std::string line;
//        while (std::getline(inFile, line)) {
//            try {
//                if (line == "PIPE") {
//                    Pipe pipe;
//                    int id;
//
//                    // Чтение ID
//                    std::getline(inFile, line);
//                    id = std::stoi(line);
//
//                    // Чтение имени трубы
//                    std::getline(inFile, pipe.name);
//
//                    // Чтение длины трубы
//                    std::getline(inFile, line);
//                    pipe.length = std::stod(line);
//                    if (pipe.length < 0.1 || pipe.length > 10000) {
//                        throw std::out_of_range("Длина трубы некорректна.");
//                    }
//
//                    // Чтение диаметра трубы
//                    std::getline(inFile, line);
//                    pipe.diameter = std::stod(line);
//                    if (pipe.diameter < 10 || pipe.diameter > 10000) {
//                        throw std::out_of_range("Диаметр трубы некорректен.");
//                    }
//
//                    // Чтение статуса ремонта трубы
//                    std::getline(inFile, line);
//                    pipe.repairStatus = (line == "1");
//
//                    // Сохранение трубы в контейнер
//                    pipe.setId(id);
//                    pipes[id] = pipe;
//
//                } else if (line == "CS") {
//                    CompressorStation station;
//                    int id;
//
//                    // Чтение ID
//                    std::getline(inFile, line);
//                    id = std::stoi(line);
//
//                    // Чтение имени станции
//                    std::getline(inFile, station.name);
//
//                    // Чтение общего количества цехов
//                    std::getline(inFile, line);
//                    station.workshopNumber = std::stoi(line);
//                    if (station.workshopNumber < 1 || station.workshopNumber > 1000) {
//                        throw std::out_of_range("Количество цехов некорректно.");
//                    }
//
//                    // Чтение количества рабочих цехов
//                    std::getline(inFile, line);
//                    station.workshopNumberInWork = std::stoi(line);
//                    if (station.workshopNumberInWork < 1 || station.workshopNumberInWork > station.workshopNumber) {
//                        throw std::out_of_range("Количество рабочих цехов некорректно.");
//                    }
//
//                    // Чтение эффективности
//                    std::getline(inFile, line);
//                    station.efficiency = std::stod(line);
//                    if (station.efficiency < 0.1 || station.efficiency > 100) {
//                        throw std::out_of_range("Эффективность некорректна.");
//                    }
//
//                    // Сохранение станции в контейнер
//                    station.setId(id);
//                    stations[id] = station;
//                }
//            } catch (const std::invalid_argument& e) {
//                std::cerr << "Ошибка: некорректный формат данных в файле." << std::endl;
//                pipes.clear();
//                stations.clear();
//                inFile.close();
//                return;
//            } catch (const std::out_of_range& e) {
//                std::cerr << "Ошибка: " << e.what() << std::endl;
//                pipes.clear();
//                stations.clear();
//                inFile.close();
//                return;
//            }
//        }
//        inFile.close();
//        std::cout << "Данные успешно загружены из файла " << filename << std::endl;
//    } else {
//        std::cerr << "Не удалось открыть файл для чтения: " << filename << std::endl;
//    }
//}

#include "DataManager.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>


void listFilesInCurrentDirectory() {
    std::cout << "Содержимое текущего каталога:\n";
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        std::cout << entry.path().filename() << std::endl;
    }
}

std::string filename = "/Users/maximgvozdev/Gubkin_main/Gubkin_3_term/Algoritmic languages/lab_2/Lab_2/data.txt";

void DataManager::loadFromFile(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, CompressorStation>& stations, const std::string& filename) {
   
    // Выводим текущий рабочий каталог и содержимое каталога для диагностики
    std::cout << "Текущий рабочий каталог: " << std::filesystem::current_path() << std::endl;
    listFilesInCurrentDirectory();

    // Проверка существования файла
    if (!std::filesystem::exists(filename)) {
        std::cerr << "Ошибка: файл " << filename << " не найден." << std::endl;
        return;
    }

    std::ifstream inFile(filename);

    // Проверка, открылся ли файл для чтения
    if (!inFile) {
        std::cerr << "Ошибка: файл " << filename << " не может быть открыт для чтения." << std::endl;
        return;
    }

    std::cout << "Файл " << filename << " успешно открыт для чтения." << std::endl;

    // Очищаем текущие данные перед загрузкой новых
    pipes.clear();
    stations.clear();

    std::string line;
    while (std::getline(inFile, line)) {
        try {
            if (line == "PIPE") {
                Pipe pipe;
                int id;

                std::getline(inFile, line);
                id = std::stoi(line);

                std::getline(inFile, pipe.name);
                std::getline(inFile, line);
                pipe.length = std::stod(line);
                std::getline(inFile, line);
                pipe.diameter = std::stod(line);
                std::getline(inFile, line);
                pipe.repairStatus = (line == "1");

                pipe.setId(id);
                pipes[id] = pipe;

                std::cout << "Труба с ID " << id << " загружена: " << pipe.name << std::endl;

            } else if (line == "CS") {
                CompressorStation station;
                int id;

                std::getline(inFile, line);
                id = std::stoi(line);

                std::getline(inFile, station.name);
                std::getline(inFile, line);
                station.workshopNumber = std::stoi(line);
                std::getline(inFile, line);
                station.workshopNumberInWork = std::stoi(line);
                std::getline(inFile, line);
                station.efficiency = std::stod(line);

                station.setId(id);
                stations[id] = station;

                std::cout << "Станция с ID " << id << " загружена: " << station.name << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: некорректный формат данных в файле." << std::endl;
            pipes.clear();
            stations.clear();
            inFile.close();
            return;
        } catch (const std::out_of_range& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            pipes.clear();
            stations.clear();
            inFile.close();
            return;
        }
    }

    // Проверка на ошибки чтения
    if (inFile.fail() && !inFile.eof()) {
        std::cerr << "Ошибка: произошла ошибка при чтении файла " << filename << std::endl;
        pipes.clear();
        stations.clear();
    } else {
        std::cout << "Данные успешно загружены из файла " << filename << std::endl;
    }

    // Закрываем файл
    inFile.close();
}
