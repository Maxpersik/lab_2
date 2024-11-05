#include <iostream>
#include "Pipe.h"
#include "CS.h"
#include "DataManager.h"
#include "Utils.h"

// Функция для получения пунктов меню без использования внешнего файла
std::vector<std::string> getMenuOptions = {
        "Выход",
        "Добавить трубу",
        "Добавить компрессорную станцию",
        "Показать все трубы и станции",
        "Редактировать трубу",
        "Редактировать станцию",
        "Сохранить в файл",
        "Загрузить из файла"
    };


void displayMenu(const std::vector<std::string>& options) {
    std::cout << "\nМеню:\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i << " - " << options[i] << '\n';
    }
    std::cout << "Выберите команду: ";
}

int main() {
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, CompressorStation> stations;
    std::string command;
    long value;
    std::string filename = "data.txt";
    

    while (true) {
        displayMenu(getMenuOptions);
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
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
                Pipe::editPipeById(id);
                break;
            case 5:
                int idd;
                std::cout << "Введите ID станции для редактирования: ";
                std::cin >> idd;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера

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
