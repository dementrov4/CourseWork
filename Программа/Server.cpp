#include "Server.hpp"

Server::Server(std::string _baseName)
{
    baseName = _baseName;
    loadBase(baseName);
}

Server::~Server()
{
    base.clear();
}

void Server::loadBase(std::string _baseName)
{
    currentId = 1;
    std::ifstream fin(_baseName);
    std::string strForParce; 

    getline(fin, strForParce);
    getline(fin, strForParce);

    
    while (fin.good()) {
        Data newRecord;
        fin >> newRecord;

        currentId = base.size()+1;
        if (newRecord.getId() == 0)
            return;

        base.push_back(newRecord);
    }
}

void Server::printBase(std::ostream &out)
{
    writeHat(out);

    for (const auto &item : base) {
        out << item;
    }
    out << std::endl;
}

void Server::create(Data data)
{
    data.setId(currentId);
    base.push_back(data);

    std::ofstream fin(baseName, std::ios::app);
    fin << data; 

    ++currentId;    
}

Data Server::read(int id)
{
    return base[id-1];
}

void Server::update(int id, Data data)
{
    if (id < 1 || id > base.size()) {
        std::cout << "Such id doesn't exist" << std::endl;
        return;
    }

    data.setId(id);
    base[id-1] = data;

    std::ofstream fout(baseName);
    printBase(fout);
}

Data Server::del(int id)
{
    Data data;
    if (id < 1 || id > base.size()) {
        std::cout << "Such id doesn't exist" << std::endl;
        return data;
    }
    data = base[id];

    for (int i = id-1; i < base.size()-1; ++i) {
        base[i+1].setId(i+1);
        base[i] = base[i+1];
    }
    base.pop_back();

    std::ofstream fout(baseName);
    printBase(fout);

    return data; 
}

Data Server::search(std::string name)
{
    for (const auto& item: base) {
        if (name == item.getName()){
            std::cout << "Element with name" << ' ' 
                    << item.getName() << ' '
                    << "is founded. id:" << ' ' 
                    << item.getId() << std::endl;
            return item;
        }
    }
    std::cout << "Element with name" << ' '
              << name << ' '
              << "isn't founded in base" << std::endl;
    return *(new Data);
}

std::vector<Data> Server::filter(int cost, bool (*compareFunction)(int, int))
{
    std::vector<Data> filtered; 

    for (const auto& item: base) {
        if (compareFunction(cost, item.getCost())) {
            filtered.push_back(item);
        }
    }
    return filtered;
}

void Server::reportMaxCost(int value)
{
    std::vector<Data> report = base;

    sort(report.begin(), report.end(), [](Data lhs, Data rhs) -> bool { return lhs.getCost() > rhs.getCost(); });
    
    if (report.size() < value) {
        std::cout << "Unfortunately, only " << report.size() << " records in base" << std::endl;
    }

    writeHat(std::cout);

    for (int i = 0; i < value; ++i) {
        if (i == report.size())
            return;
        std::cout << report[i];
    }
}
void Server::reportMinSize(int value)
{
    std::vector<Data> report = base;

    sort(report.begin(), report.end(), [](Data lhs, Data rhs) -> bool { return lhs.getSize() < rhs.getSize(); });

    if (report.size() < value) {
        std::cout << "Unfortunately, only " << report.size() << " records in base" << std::endl;
    }

    writeHat(std::cout);

    for (int i = 0; i < value; ++i) {
        if (i == report.size())
            return;
        std::cout << report[i];
    }
}
void Server::reportChosenGenre(std::string key)
{
    std::vector<Data> report;

    for (auto iter = base.begin(); iter != base.end(); ++iter) {
        if (iter->getGenre() == key) {
            report.push_back(*iter);
        }
    }
    
    if (report.empty()) {
        std::cout << "No such genre in base" << std::endl;
        return;
    }
    writeHat(std::cout);

    for (int i = 0; i < report.size(); ++i)
    {
        std::cout << report[i];
    }
}

void Server::writeHat(std::ostream &out)
{
    for (int i = 0; i < 103; ++i) {
        out << '_';
    }
    out << std::endl;
    out << '|' << std::setw(5) << "Id" << '|'
        << std::setw(15) << "Name" << '|'
        << std::setw(15) << "Author" << '|'
        << std::setw(15) << "Genre" << '|'
        << std::setw(15) << "Extension" << '|'
        << std::setw(15) << "Size(Kbyte)" << '|'
        << std::setw(15) << "Cost($)" << '|' << std::endl;
}
