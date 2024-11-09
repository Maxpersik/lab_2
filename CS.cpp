#include "CS.h"
#include <iostream>
#include "Utils.h"

int CompressorStation::nextId = 1;
std::unordered_map<int, CompressorStation> CompressorStation::stations;

CompressorStation::CompressorStation(int id, const std::string& name, int workshopNumber, int workshopNumberInWork, double efficiency)
    : id(id), name(name), workshopNumber(workshopNumber), workshopNumberInWork(workshopNumberInWork), efficiency(efficiency) {}

void CompressorStation::readFromConsole() {
    std::cout << "Введите название станции: ";
    std::getline(std::cin, name);

    workshopNumber = inputInRange<int>("Введите количество цехов: ", 1, 1000);
    workshopNumberInWork = inputInRange<int>("Введите количество цехов в работе: ", 0, workshopNumber);
    efficiency = inputInRange<double>("Введите эффективность (в %): ", 0.01, 100);
}

void CompressorStation::writeToConsole() const {
    std::cout << "\nID станции: " << id << std::endl;
    std::cout << "Название станции: " << name << std::endl;
    std::cout << "Количество цехов: " << workshopNumber << std::endl;
    std::cout << "Количество цехов в работе: " << workshopNumberInWork << std::endl;
    std::cout << "Эффективность (в %): " << efficiency << std::endl << std::endl;
}

void CompressorStation::editWorkshop() {
    int command;
    std::cout << "1 - Запустить цех" << std::endl;
    std::cout << "2 - Остановить цех" << std::endl;

    command = inputInRange<int>("Выберите действие: ", 1, 2);

    if (command == 1) {
        if (workshopNumber > workshopNumberInWork) {
            workshopNumberInWork++;
            std::cout << "Еще один цех запущен. Теперь в работе " << workshopNumberInWork << " из " << workshopNumber << " цехов.\n";
        } else {
            std::cout << "Все цехи уже запущены.\n";
        }
    } else if (command == 2) {
        if (workshopNumberInWork > 0) {
            workshopNumberInWork--;
            std::cout << "Один цех остановлен. Теперь в работе " << workshopNumberInWork << " из " << workshopNumber << " цехов.\n";
        } else {
            std::cout << "Все цехи уже остановлены.\n";
        }
    } else {
        std::cout << "Неверный выбор, попробуйте снова.\n";
    }
}

void CompressorStation::addStation() {
    CompressorStation station;
    station.setId(nextId++);
    station.readFromConsole();
    stations[station.getId()] = station;
}

void CompressorStation::displayAll() {
    std::cout << "\n--- Показать все компрессорные станции ---\n";
    for (const auto& [id, station] : stations) {
        station.writeToConsole();
    }
}

void CompressorStation::editStationById(int id) {
    auto it = stations.find(id);
    if (it != stations.end()) {
        it->second.editWorkshop();
    } else {
        std::cout << "Станция с таким ID не найдена.\n";
    }
}

void CompressorStation::addNewStation() {
    CompressorStation station;
    station.setId(nextId++);
    station.readFromConsole();
    stations[station.getId()] = station;
    std::cout << "Станция успешно добавлена.\n";
}

void CompressorStation::editStation() {
    int stationId;
    std::cout << "Введите ID станции для редактирования: ";
    std::cin >> stationId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = stations.find(stationId);
    if (it != stations.end()) {
        it->second.editWorkshop();
        std::cout << "Станция с ID " << stationId << " успешно отредактирована.\n";
    } else {
        std::cout << "Станция с таким ID не найдена.\n";
    }
}

void CompressorStation::deleteStation() {
    int stationId;
    std::cout << "Введите ID станции для удаления: ";
    std::cin >> stationId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (stations.erase(stationId)) {
        std::cout << "Станция с ID " << stationId << " успешно удалена.\n";
    } else {
        std::cout << "Станция с таким ID не найдена.\n";
    }
}

void CompressorStation::displayStations(const std::vector<CompressorStation>& stationsToDisplay) {
    if (stationsToDisplay.empty()) {
        std::cout << "Нет станций, соответствующих критерию поиска.\n";
    } else {
        for (const auto& station : stationsToDisplay) {
            station.writeToConsole();
        }
    }
}

void CompressorStation::searchStationsByUnusedWorkshopPercentage() {
    double unusedPercentage;
    std::cout << "Введите процент незадействованных цехов для поиска: ";
    std::cin >> unusedPercentage;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto results = findStationsByUnusedWorkshopPercentage(unusedPercentage);
    displayStations(results);
}

// Поиск по названию
std::vector<CompressorStation> CompressorStation::findStationsByName(const std::string& name) {
    std::vector<CompressorStation> results;
    for (const auto& [id, station] : stations) {
        if (station.name == name) {
            results.push_back(station);
        }
    }
    return results;
}

// Поиск по проценту незадействованных цехов
std::vector<CompressorStation> CompressorStation::findStationsByUnusedWorkshopPercentage(double unusedPercentage) {
    std::vector<CompressorStation> results;
    for (const auto& [id, station] : stations) {
        double actualUnusedPercentage = 100.0 * (station.workshopNumber - station.workshopNumberInWork) / station.workshopNumber;
        if (actualUnusedPercentage == unusedPercentage) {
            results.push_back(station);
        }
    }
    return results;
}

void CompressorStation::searchStationsMenu() {
    std::cout << "Выберите критерий поиска:\n";
    std::cout << "1 - Поиск по названию\n";
    std::cout << "2 - Поиск по проценту незадействованных цехов\n";
    int choice = inputInRange<int>("Введите номер действия: ", 1, 2);

    if (choice == 1) {
        std::string name;
        std::cout << "Введите название станции для поиска: ";
        std::getline(std::cin, name);
        auto results = findStationsByName(name);
        displayStations(results);
    } else if (choice == 2) {
        double unusedPercentage;
        std::cout << "Введите процент незадействованных цехов для поиска: ";
        std::cin >> unusedPercentage;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        auto results = findStationsByUnusedWorkshopPercentage(unusedPercentage);
        displayStations(results);
    }
}

void CompressorStation::batchEditOrDeleteMenu() {
    if (stations.empty()) {
        std::cout << "Нет доступных станций для пакетного редактирования.\n";
        return;
    }

    std::cout << "Введите ID станций, которые хотите выбрать для пакетного редактирования, через пробел: ";
    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    std::vector<int> selectedIds;
    int id;

    while (ss >> id) {
        if (stations.find(id) != stations.end()) {
            selectedIds.push_back(id);
        } else {
            std::cout << "Станция с ID " << id << " не найдена.\n";
        }
    }

    std::cout << "Выберите действие:\n";
    std::cout << "1 - Редактировать выбранные станции\n";
    std::cout << "2 - Удалить выбранные станции\n";
    int choice = inputInRange<int>("Введите номер действия: ", 1, 2);

    if (choice == 1) {
        for (int stationId : selectedIds) {
            stations[stationId].editWorkshop();  // Выполняем редактирование
        }
        std::cout << "Выбранные станции успешно отредактированы.\n";
    } else if (choice == 2) {
        for (int stationId : selectedIds) {
            stations.erase(stationId);  // Выполняем удаление
        }
        std::cout << "Выбранные станции успешно удалены.\n";
    }
}

void CompressorStation::stationSubMenu() {
    std::vector<std::string> getMenuOptionsCS = {
        "Выход",
        "Показать все станции",
        "Добавить станцию",
        "Редактировать станцию",
        "Удалить станцию",
        "Поиск станций",
        "Пакетное редактирование"
    };

    std::string command;
    long value;

    while (true) {
        displayMenu(getMenuOptionsCS);
        std::getline(std::cin, command);
        value = numberOrDefault(command);

        switch (value) {
            case 1:
                displayAll();
                break;
            case 2:
                addNewStation();
                break;
            case 3:
                editStation();
                break;
            case 4:
                deleteStation();
                break;
            case 5:
                searchStationsMenu();
                break;
            case 6:
                batchEditOrDeleteMenu();
                break;
            case 0:
                std::cout << "Выход из меню работы со станциями.\n";
                return;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    }
}
