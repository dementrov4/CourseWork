#pragma once 
#include "Data.hpp"
#include <vector>
#include <algorithm>
#include <map>
#include <unistd.h>

class Server
{
private:
    std::string baseName;
    int currentId;
    std::vector <Data> base;

public:
    Server(std::string _baseName = ""); // +
    ~Server();                          // +

    void loadBase(std::string); // +
    void printBase(std::ostream &); // +

    void create(Data); // +
    Data read(int); // +
    void update(int, Data); // +
    Data del(int); // +


    Data search(std::string); // + 
    std::vector<Data> filter(int, bool (*compareFunction)(int, int)); // +

    void writeHat(std::ostream &); // +

    void reportMaxCost(int);
    void reportMinSize(int);
    void reportChosenGenre(std::string);  

    Data getId(int id) { return base[id]; }

    void userInterface();  
};

