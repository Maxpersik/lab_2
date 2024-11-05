#include <iostream>
#include "Pipe.h"
#include "CS.h"
#include "DataManager.h"
#include "Utils.h"

int main() {
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, CompressorStation> stations;

    std::string command;
    long value;
    std::string filename = "data.txt";
    

    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1 - Добавить трубу\n";
        std::cout << "2 - Добавить компрессорную станцию\n";
        std::cout << "3 - Показать все трубы и станции\n";
        std::cout << "4 - Редактировать трубу\n";
        std::cout << "5 - Редактировать станцию\n";
        std::cout << "6 - Сохранить в файл\n";
        std::cout << "7 - Загрузить из файла\n";
        std::cout << "0 - Выход\n";
        std::cout << "Выберите команду: ";
        getline(std::cin, command);

        value = numberOrDefault(command);

        switch (value) {
            case 1:
                Pipe::addPipe();
                break;
            case 2:
                CompressorStation::addStation();
                break;
            case 3:
                CompressorStation::displayAll();
                Pipe::displayAll();
                break;
            case 4:
                int id;
                std::cout << "Введите ID трубы для редактирования: ";
                std::cin >> id;
                Pipe::editPipeById(id);
                break;
            case 5:
                int idd;
                std::cout << "Введите ID станции для редактирования: ";
                std::cin >> idd;
                CompressorStation::editStationById(idd);
                break;
            case 6:
                DataManager::saveToFile(pipes, stations, filename);
                break;
            case 7:
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
