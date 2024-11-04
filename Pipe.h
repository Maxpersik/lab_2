//#ifndef PIPE_H
//#define PIPE_H
//
//#include <iostream>
//#include <string>
//#include <iomanip>
//
//using namespace std;
//
//class PipeManager;
//
//class Pipe {
//private:
//    int nextId = 1;
//    int id;
//    string name;
//    double length = 0;
//    double diameter = 0;
//    bool repairStatus = false;
//public:
//    void readFromConsole();
//    void writeToConsole();
//    void leditRepairStatus();
//    friend class DataManager;
//    Pipe(const string& name = "", double length = 0, double diameter = 0, bool repairStatus = false)
//           : id(nextId++), name(name), length(length), diameter(diameter), repairStatus(repairStatus) {}
//
//};
//
//#endif

#ifndef PIPE_H
#define PIPE_H

#include <iostream>
#include <string>
#include <unordered_map>

class Pipe {
private:
    int id;
    std::string name;
    double length = 0;
    double diameter = 0;
    bool repairStatus = false;

    static int nextId;
    static std::unordered_map<int, Pipe> pipes;

public:
    Pipe() = default;
    Pipe(int id, const std::string& name, double length, double diameter, bool repairStatus);

    void readFromConsole();
    void writeToConsole() const;
    void editRepairStatus();

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    static void addPipe();
    static void displayAll();
    
    // Метод для редактирования статуса трубы по ID
    static void editPipeById(int id);
    friend class DataManager;
};

#endif // PIPE_H
