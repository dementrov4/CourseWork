#include "Data.hpp"

Data::Data(
            int _id,
            std::string _name,
            std::string _author,
            std::string _genre,
            std::string _extension,
            int _size, 
            int _cost
        )
{
    id = _id;
    name = _name; 
    author = _author;
    genre = _genre; 
    extension = _extension;
    size = _size;
    cost = _cost;
}

Data &Data::operator=(const Data &data) 
{
    if (this == &data) 
        return *this;

    setId(data.getId());
    setName(data.getName());
    setAuthor(data.getAuthor());
    setGenre(data.getGenre());
    setExtension(data.getExtension());
    setSize(data.getSize());
    setCost(data.getCost());

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Data &sample)
{
    out << '|' << std::setw(5) << sample.getId() << '|'
        << std::setw(15) << sample.getName() << '|'
        << std::setw(15) << sample.getAuthor() << '|'
        << std::setw(15) << sample.getGenre() << '|'
        << std::setw(15) << sample.getExtension() << '|'
        << std::setw(15) << sample.getSize() << '|'
        << std::setw(15) << sample.getCost() << '|' << std::endl; 
    return out;
}

std::istream &operator>>(std::istream &in, Data &sample)
{
    std::vector<std::string> parced;
    std::string parce; 

    getline(in, parce);

    if (parce == "")
        return in;

    std::string newItem = "";
    int stickCounter = 1;

    for (int i = 1; i < parce.size(); ++i) {

        if ((newItem != "" && stickCounter == 2) || i == parce.size()-1) {
            parced.push_back(newItem);
            newItem = "";
            stickCounter = 1;
        } else if ((parce[i] != '|' && parce[i] != ' ') || 
                    ((parce[i-1] != '|' && parce[i-1] != ' ') &&
                    (parce[i+1] != '|' && parce[i+1] != ' '))) {
            newItem += parce[i];
        } else if (parce[i] == '|') {
            ++stickCounter;
        }
    }

    sample.setId(std::stoi(parced[0]));
    sample.setName(parced[1]);
    sample.setAuthor(parced[2]);
    sample.setGenre(parced[3]);
    sample.setExtension(parced[4]);
    sample.setSize(std::stoi(parced[5]));
    sample.setCost(std::stoi(parced[6]));

    return in;
}

