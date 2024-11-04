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
