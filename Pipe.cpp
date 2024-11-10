#include "Pipe.h"
#include <iostream>
#include "Utils.h"
#include "Logger.h"


std::vector<std::string> getMenuOptionsPipe = {
        "Выход",
        "Показать все трубы",
        "Добавить трубу",
        "Редактировать трубу",
        "Удалить трубу",
        "Поиск труб",
        "Пакетное редактирование"
    };
std::ostream& operator<<(std::ostream& out, const Pipe& pipe) {
    out << "\nPipe ID : " << pipe.getId()
        << "\nPipe name: " << pipe.name
        << "\nPipe length: " << pipe.length
        << "\nPipe diameter: " << pipe.diameter
        << "\nRepair status: " << (pipe.repairStatus ? "Yes" : "No");
    return out;
}

void Pipe::printPipeInfo(std::ostream& out) {
    logger.log("Печать информации о всех трубах.");
    for (const auto& [id, pipe] : pipes) {
        out << pipe;  // Использует перегруженный оператор <<
    }
}


int Pipe::nextId = 1;
std::unordered_map<int, Pipe> Pipe::pipes;

Pipe::Pipe(int id, const std::string& name, double length, double diameter, bool repairStatus)
    : id(id), name(name), length(length), diameter(diameter), repairStatus(repairStatus) {
        logger.log("Создан новый объект Pipe с ID: " + std::to_string(id));
    }

void Pipe::readFromConsole() {
    logger.log("Вход в функцию readFromConsole()");
    std::cout << "Введите название трубы: ";
    std::getline(std::cin, name);
    length = inputInRange<int>("Введите длину трубы (в км): ", 0.1, 10000);
    diameter = inputInRange<int>("Введите диаметр трубы (в мм): ", 10, 10000);
    repairStatus = false;
    logger.log("Завершено чтение данных трубы из консоли.");

}

void Pipe::writeToConsole() const {
    logger.log("Вывод параметров трубы в консоль)");
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
    logger.log("Статус ремонта трубы изменен.");
}

void Pipe::addPipe() {
    Pipe pipe;
    pipe.setId(nextId++);
    pipe.readFromConsole();
    pipes[pipe.getId()] = pipe;
    logger.log("Добавлена новая труба с ID: " + std::to_string(pipe.getId()));

}

void Pipe::displayAll() {
    logger.log("Вывод всех труб");
    std::cout << "\n--- Показать все трубы ---\n";
    for (const auto& [id, pipe] : pipes) {
        pipe.writeToConsole();
    }
}


void Pipe::editPipeById() {
    int pipeId;
    std::cout << "Введите ID трубы для редактирования: ";
    std::cin >> pipeId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка буфера

    auto it = pipes.find(pipeId);
    if (it != pipes.end()) {
        it->second.editRepairStatus();  // Редактируем статус (или другое действие)
        std::cout << "Труба с ID " << pipeId << " успешно отредактирована.\n";
        logger.log("Отредактирована труба с ID: " + std::to_string(pipeId));
    } else {
        std::cout << "Труба с таким ID не найдена.\n";
        logger.log("Труба с ID " + std::to_string(pipeId) + " не найдена.");
    }
}

void Pipe::displayPipes(const std::vector<Pipe>& pipes) {
    if (pipes.empty()) {
        std::cout << "Нет труб, соответствующих критерию поиска.\n";
        logger.log("Нет труб, соответствующих критерию поиска.");
    } else {
        for (const auto& pipe : pipes) {
            pipe.writeToConsole();
        }
    }
}

std::vector<Pipe> Pipe::findPipes() {
    int command;
    std::cout << "Выберите критерий поиска:\n";
    std::cout << "1 - Поиск по названию\n";
    std::cout << "2 - Поиск по статусу ремонта\n";
    
    command = inputInRange<int>("Введите номер критерия: ", 1, 2);

    std::vector<Pipe> results;
    if (command == 1) {
        // Поиск по названию
        std::string name;
        std::cout << "Введите название трубы: ";
        std::getline(std::cin, name);
        for (const auto& [id, pipe] : pipes) {
            if (pipe.name == name) {
                results.push_back(pipe);
            }
        }
        logger.log("Поиск труб по названию завершен.");
    } else if (command == 2) {
        // Поиск по статусу ремонта
        bool inRepair;
        std::cout << "Введите 1, если хотите найти трубы в ремонте, 0 - если нет: ";
        std::cin >> inRepair;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (const auto& [id, pipe] : pipes) {
            if (pipe.repairStatus == inRepair) {
                results.push_back(pipe);
            }
        }
        logger.log("Поиск труб по статусу ремонта завершен.");
    }

    // Показать результаты поиска
    displayPipes(results);
    return results;
}

void Pipe::deletePipeMenu() {
    int pipeId;
    std::cout << "Введите ID трубы для удаления: ";
    std::cin >> pipeId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = pipes.find(pipeId);  // Ищем трубу по ID
    if (it != pipes.end()) {
        pipes.erase(it);  // Удаляем трубу, если найдена
        std::cout << "Труба с ID " << pipeId << " успешно удалена.\n";
        logger.log("Удалена труба с ID: " + std::to_string(pipeId));
    } else {
        std::cout << "Труба с таким ID не найдена.\n";
        logger.log("Труба с ID " + std::to_string(pipeId) + " не найдена.");
            
    }
}

void Pipe::selectPipesForBatchEditOrDelete() {
    if (pipes.empty()) {
        std::cout << "Нет доступных труб для выбора.\n";
        logger.log("Нет доступных труб для выбора.");
        return;
    }

    std::cout << "Существующие трубы:\n";
    for (const auto& [id, pipe] : pipes) {
        std::cout << "ID: " << id << " - ";
        pipe.writeToConsole();
    }

    std::cout << "Введите ID труб, которые хотите выбрать для редактирования или удаления, через пробел: ";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<int> selectedIds;
    int id;

    // Чтение введенных ID и проверка их существования
    while (ss >> id) {
        if (pipes.find(id) != pipes.end()) {
            selectedIds.push_back(id);
        } else {
            std::cout << "Труба с ID " << id << " не найдена.\n";
            logger.log("Труба с ID " + std::to_string(id) + " не найдена.");
        }
    }

    // Если выбранные ID найдены, формируем список труб
    std::vector<Pipe> selectedPipes;
    for (int id : selectedIds) {
        selectedPipes.push_back(pipes[id]);
    }

    if (!selectedPipes.empty()) {
        batchEditOrDeleteMenu(selectedPipes);  // Переходим к редактированию или удалению выбранных труб
    } else {
        std::cout << "Ни одной трубы не выбрано для обработки.\n";
        logger.log("Ни одной трубы не выбрано для обработки.");
    }
}

void Pipe::batchEditOrDeleteMenu(const std::vector<Pipe>& pipesToEdit) {
    if (pipesToEdit.empty()) {
        std::cout << "Нет труб для редактирования или удаления.\n";
        return;
    }

    std::cout << "Выберите действие:\n";
    std::cout << "1 - Редактировать все выбранные трубы\n";
    std::cout << "2 - Удалить все выбранные трубы\n";

    int choice = inputInRange<int>("Введите номер действия: ", 1, 2);

    if (choice == 1) {
        for (auto& pipe : pipesToEdit) {
            pipes[pipe.getId()].editRepairStatus();  // Редактируем статус (или другое действие)
        }
        std::cout << "Все выбранные трубы успешно отредактированы.\n";
    } else if (choice == 2) {
        for (const auto& pipe : pipesToEdit) {
            pipes.erase(pipe.getId());  // Удаляем по ID
        }
        std::cout << "Все выбранные трубы успешно удалены.\n";
    }
}

int Pipe::pipeSubMenu() {
    logger.log("Вход в подменю трубы.");
    std::string command;
    long value;
    while (true) {
        displayMenu(getMenuOptionsPipe);
        getline(std::cin, command);

        value = numberOrDefault(command);

        switch (value) {
            case 1:
                logger.log("Показ всех труб.");
                displayAll();
                printPipeInfo(std::cout);
                break;
            case 2:
                logger.log("Добавление новой трубы.");
                addPipe();
                break;
            case 3: {
                logger.log("Редактирование трубы по ID.");
                editPipeById();
                break;
            }
            case 4: {
                logger.log("Удаление трубы по ID.");
                deletePipeMenu();
                break;
            }
            case 5: {
                logger.log("Поиск труб.");
                findPipes();
                break;
            }
            case 6: {
                logger.log("Выбор труб для пакетного редактирования или удаления.");
                selectPipesForBatchEditOrDelete();
                break;
            case 0:
                logger.log("Выход из подменю трубы.");
                std::cout << "Выход из программы.\n";
                return 0;
            }
            default:
                logger.log("Неверная команда: " + command);
                std::cout << "Неверная команда. Попробуйте снова.\n";
                break;
        }
    }
}
