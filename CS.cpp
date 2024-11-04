//#include "CS.h"
//#include "Utils.h"
//#include <vector>
//#include <iostream>
//#include <map>
//
//extern std::map<int, CompressorStation> S;
//using namespace std;
//
//
//void CompressorStation::readFromConsole() {
//        cout << "Введите название станции: ";
//        getline(cin, name);
//        
//        workshopNumber = inputIntInRange("Введите количество цехов: ", 1, 1000);
//        workshopNumberInWork = inputIntInRange("Введите количество цехов в работе: ", 0, workshopNumber);
//        efficiency = inputIntInRange("Введите эффективность (в %): ", 0.01, 100);
//    }
//    
//void CompressorStation::writeToConsole() {
//    if (name.empty()) {
//        cout << "КС не создана" << endl << endl;
//    }
//    else {
//        cout << "Название станции: " << name << endl;
//        cout << "Количество цехов:" << workshopNumber << endl;
//        cout << "Количество цехов в работе: " << workshopNumberInWork << endl;
//        cout << "Эффективность(в %)" << efficiency << endl << endl;
//    }
//}
//    
//void CompressorStation::editWorkshop() {
//    int command;
//    cout << " 1 - Запустить цех  " << endl;
//    cout << " 2 - Остановить цех " << endl;
//
//    command = inputIntInRange("Выберете действие:", 1, 2);
//    
//    switch (command) {
//        case 1:
//            if (workshopNumber > workshopNumberInWork) {
//                workshopNumberInWork++;
//                cout << "Еще один цех запущен" << endl;
//                cout << "Теперь в работе " << workshopNumberInWork << " из " << workshopNumber << " цехов " << endl;
//            }
//            else {
//                cout << "Все цехи запущены" << endl;
//            }
//            break;
//        case 2:
//            if (0 < workshopNumberInWork) {
//                workshopNumberInWork--;
//                cout << "Цех остановлен" << endl;
//                cout << "Теперь в работе " << workshopNumberInWork << " из " << workshopNumber << " цехов" << endl;
//            }
//            else {
//                cout << "Все цехи остановлены" << endl;
//            }
//            break;
//        default: // -1
//            cout << "Неверный выбор, попробуйте снова." << endl;
//    }
//}
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

    workshopNumber = inputIntInRange("Введите количество цехов: ", 1, 1000);
    workshopNumberInWork = inputIntInRange("Введите количество цехов в работе: ", 0, workshopNumber);
    efficiency = inputIntInRange("Введите эффективность (в %): ", 0.01, 100);
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

    command = inputIntInRange("Выберите действие: ", 1, 2);

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
