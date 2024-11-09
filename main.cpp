#include <iostream>
#include "Pipe.h"
#include "CS.h"
#include "DataManager.h"
#include "Utils.h"
#include "Logger.h"


// Функция для получения пунктов меню без использования внешнего файла
std::vector<std::string> getMenuOptions = {
        "Выход",
        "Меню трубы",
        "Меню станции",
        "Показать все трубы и станции",
        "Сохранить в файл",
        "Загрузить из файла"
    };


int main() {
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, CompressorStation> stations;
    std::string command;
    long value;
    std::string filename = "data.txt";
    //Logger logger("log.txt");

    while (true) {
        displayMenu(getMenuOptions);
        getline(std::cin, command);

        value = numberOrDefault(command);

        switch (value) {
            case 1:
                Pipe::pipeSubMenu();
                break;
            case 2:
                CompressorStation::stationSubMenu();
                break;
            case 3:
                CompressorStation::displayAll();
                Pipe::displayAll();
                break;
            case 4:
                DataManager::saveToFile(pipes, stations, filename);
                break;
            case 5:
                DataManager::loadFromFile(pipes, stations, filename);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                return 0;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    }
}
