#pragma once 

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

class Data
{
private:
    int id; 
    std::string name;
    std::string author;
    std::string genre;
    std::string extension; 
    size_t size; 
    int cost;

public:
    Data(
        int _id = 0,
        std::string _name = "",
        std::string _author = "",
        std::string _genre = "",
        std::string _extension = "",
        int _size = 1,
        int _cost = 0);

    Data &operator=(const Data&);

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getAuthor() const { return author; }
    std::string getGenre() const { return genre; }
    std::string getExtension() const { return extension; }
    int getSize() const { return size; }
    int getCost() const { return cost; }


    void setId(const int& _id) { id = _id; }
    void setName(const std::string& _name) { name = _name; }
    void setAuthor(const std::string& _author) { author = _author; }
    void setGenre(const std::string& _genre) { genre = _genre; }
    void setExtension(const std::string& _extension) { extension = _extension; }
    void setSize(const int& _size) { size = _size; }
    void setCost(const int& _cost) { cost = _cost; }

    friend std::ostream &operator<<(std::ostream &, const Data &);
    friend std::istream &operator>>(std::istream &, Data &);
};

