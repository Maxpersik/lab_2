#ifndef CS_H
#define CS_H

#include <iostream>
#include <string>
#include <unordered_map>

class CompressorStation {
private:
    int id;
    std::string name;
    int workshopNumber;
    int workshopNumberInWork;
    double efficiency;

    static int nextId;
    static std::unordered_map<int, CompressorStation> stations;

public:
    CompressorStation() = default;
    CompressorStation(int id, const std::string& name, int workshopNumber, int workshopNumberInWork, double efficiency);
    
    void readFromConsole();
    void writeToConsole() const;
    void editWorkshop();

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    static void addStation();
    static void displayAll();
    
    // Метод для редактирования станции по ID
    static void editStationById(int id);
    friend class DataManager;
};

#endif // CS_H
