#include "Server.hpp"

class Client
{
private:
    std::map<std::string, int> commandMap = {{"CREATE", 1},
                                             {"READ", 2},
                                             {"UPDATE", 3},
                                             {"DELETE", 4},
                                             {"SEARCH", 5},
                                             {"FILTER", 6},
                                             {"MAX COST", 7},
                                             {"MIN SIZE", 8},
                                             {"CHOSEN GENRE", 9},
                                             {"EXIT", 10}};

    std::map<std::string, int> updateMap = {{"NAME", 1},
                                            {"AUTHOR", 2},
                                            {"GENRE", 3},
                                            {"EXTENSION", 4},
                                            {"SIZE", 5},
                                            {"COST", 6}};

    std::map<std::string, int> filterKeyMap = {{"MORE", 1},
                                               {"EQUAL", 2},
                                               {"LESS", 3}};

    std::string baseName;

public:
    Client(std::string _baseName="");

    void userInterface();
};
