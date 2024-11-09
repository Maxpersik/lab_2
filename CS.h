#ifndef CS_H
#define CS_H

#include <iostream>
#include <string>
#include <unordered_map>

class DataManager;

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
    
    friend class DataManager;
    
    void readFromConsole();
    void writeToConsole() const;
    void editWorkshop();

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    static void addStation();
    static void displayAll();
    
    // Метод для редактирования станции по ID
    static void editStationById(int id);
    static std::vector<CompressorStation> findStationsByUnusedWorkshopPercentage(double unusedPercentage);
    static std::vector<CompressorStation> findStationsByName(const std::string& name);
    static void displayStations(const std::vector<CompressorStation>& stationsToDisplay);
    static void searchStationsByUnusedWorkshopPercentage();
    static void addNewStation();
    static void editStation();
    static void deleteStation();
    static void searchStationsMenu();
    static void batchEditOrDeleteMenu();

    // Меню для работы со станциями
    static void stationSubMenu();
    
};

#endif // CS_H
