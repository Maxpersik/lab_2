#include "Pipe.h"
#include <iostream>
#include "Utils.h"

int Pipe::nextId = 1;
std::unordered_map<int, Pipe> Pipe::pipes;

Pipe::Pipe(int id, const std::string& name, double length, double diameter, bool repairStatus)
    : id(id), name(name), length(length), diameter(diameter), repairStatus(repairStatus) {}

void Pipe::readFromConsole() {
    std::cout << "Введите название трубы: ";
    std::getline(std::cin, name);
    length = inputIntInRange("Введите длину трубы (в км): ", 0.1, 10000);
    diameter = inputIntInRange("Введите диаметр трубы (в мм): ", 10, 10000);
    repairStatus = false;
}

void Pipe::writeToConsole() const {
    if (!name.empty()) {
        std::cout << "\nID трубы: " << id << std::endl;
        std::cout << "Название трубы: " << name << std::endl;
        std::cout << "Длина трубы (в км): " << length << std::endl;
        std::cout << "Диаметр трубы (в мм): " << diameter << std::endl;
        std::cout << "Ремонтный статус: " << (repairStatus ? "Да" : "Нет") << std::endl;
    } else {
        std::cout << "Труба не создана." << std::endl;
    }
}

void Pipe::editRepairStatus() {
    repairStatus = !repairStatus;
    std::cout << "Ремонтный статус изменен на: " << (repairStatus ? "Да" : "Нет") << std::endl;
}

void Pipe::addPipe() {
    Pipe pipe;
    pipe.setId(nextId++);
    pipe.readFromConsole();
    pipes[pipe.getId()] = pipe;
}

void Pipe::displayAll() {
    std::cout << "\n--- Показать все трубы ---\n";
    for (const auto& [id, pipe] : pipes) {
        pipe.writeToConsole();
    }
}

void Pipe::editPipeById(int id) {
    auto it = pipes.find(id);
    if (it != pipes.end()) {
        it->second.editRepairStatus();
    } else {
        std::cout << "Труба с таким ID не найдена.\n";
    }
}

void Pipe::pipeSubMenu() {
    int choice;
    while (true) {
        std::cout << "\nМеню Труб:\n";
        std::cout << "1 - Добавить трубу\n";
        std::cout << "2 - Поиск труб по названию\n";
        std::cout << "3 - Поиск труб по признаку «в ремонте»\n";
        std::cout << "4 - Редактировать трубу\n";
        std::cout << "0 - Назад в главное меню\n";
        std::cout << "Выберите команду: ";
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1: {
                addPipe();
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Введите название трубы: ";
                std::getline(std::cin, name);
                //auto results = findPipesByName(name);
                //displayPipes(results);
                break;
            }
            case 3: {
                bool inRepair;
                std::cout << "Введите 1, если хотите найти трубы в ремонте, 0 - если нет: ";
                std::cin >> inRepair;
                //auto results =findPipesByRepairStatus(inRepair);
                //displayPipes(results);
                break;
            }
            case 4: {
                int pipeId;
                std::cout << "Введите ID трубы для редактирования: ";
                std::cin >> pipeId;
//                if (editPipe(pipeId)) {
//                    std::cout << "Труба успешно отредактирована.\n";
//                } else {
//                    std::cout << "Труба с таким ID не найдена.\n";
//                }
//                break;
            }
            default:
                std::cout << "Неверная команда. Попробуйте снова.\n";
                break;
        }
    }
}
