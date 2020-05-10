#include "Client.hpp"

Client::Client(std::string _baseName)
{
    baseName = _baseName;
}

void Client::userInterface()
{

    char ans;

    std::cout << "Do you want to change name of data base (y/n)? ";
    std::cin >> ans; 
    
    if (ans == 'y') {
        std::cout << "Enter name of data base: "; 
        std::cin >> baseName;
    } else if (ans == 'n' && baseName == "") {
        std::cout << "No base name" << std::endl;;
        return;
    }
    std::cin.ignore(32767, '\n');
    printf("\e[1;1H\e[2J");

    Server base(baseName);

    do
    {
        std::string command;
        std::string fieldForUpdate;
        std::string filterKey;
        std::vector<Data> filtered;

        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        int bufferNum;
        std::string buffer;
        Data data;
        int id;
        const int showTime = 5;

        switch (commandMap[command])
        {
        case 1:

            std::cout << "Enter data : " << std::endl;
            std::cout << "Enter name :-----------------: ";
            std::getline(std::cin, buffer);
            data.setName(buffer);

            std::cout << "Enter author of production :-: ";
            std::getline(std::cin, buffer);
            data.setAuthor(buffer);

            std::cout << "Enter genre :----------------: ";
            std::getline(std::cin, buffer);
            data.setGenre(buffer);

            std::cout << "Enter extension :------------: ";
            std::getline(std::cin, buffer);
            data.setExtension(buffer);

            std::cout << "Enter size in kbytes :-------: ";
            std::cin >> bufferNum;
            data.setSize(bufferNum);

            std::cout << "Enter cost in $ :------------: ";
            std::cin >> bufferNum;
            data.setCost(bufferNum);

            base.create(data);
            break;
        case 2:
            std::cout << "Choose id of row: ";
            std::cin >> id;

            std::cout << "Chosen row: " << std::endl;
            base.writeHat(std::cout);
            std::cout << base.getId(id-1) << std::endl;

            std::cout << "Press enter for continue...";
            sleep(showTime);
            break;
        case 3:
            std::cout << "Enter id of position for update: ";
            std::cin >> id;
            std::cout << "Enter field for update: ";
            std::cin >> fieldForUpdate;
            std::cin.ignore(32767, '\n');

            data = base.getId(id-1);

            switch (updateMap[fieldForUpdate])
            {
            case 1:
                std::cout << "Enter new name: ";
                std::getline(std::cin, buffer);
                data.setName(buffer);
                break;
            case 2:
                std::cout << "Enter new author: ";
                std::getline(std::cin, buffer);
                data.setAuthor(buffer);
                break;
            case 3:
                std::cout << "Enter new genre: ";
                std::getline(std::cin, buffer);
                data.setGenre(buffer);
                break;
            case 4:
                std::cout << "Enter new extension: ";
                std::getline(std::cin, buffer);
                data.setExtension(buffer);
                break;
            case 5:
                std::cout << "Enter new size: ";
                std::cin >> bufferNum;
                data.setSize(bufferNum);
                break;
            case 6:
                std::cout << "Enter new cost: ";
                std::cin >> bufferNum;
                data.setCost(bufferNum);
                break;
            default:
                std::cout << "Such field doesn't exist" << std::endl;
                return;
                break;
            }
            base.update(id, data);
            break;
        case 4:
            std::cout << "Enter id of row for delete: ";
            std::cin >> id;

            base.del(id);
            break;
        case 5:
            std::cout << "Enter name of production for search: ";
            std::getline(std::cin, buffer);

            base.search(buffer);
            sleep(showTime);
            break;
        case 6:
            std::cout << "Enter filter key: ";
            std::cin >> filterKey;

            std::cout << "Enter filter edge: ";
            std::cin >> bufferNum;
            std::cin.ignore(32767, '\n');

            switch (filterKeyMap[filterKey])
            {
            case 1:
                filtered = base.filter(bufferNum, [](int lhs, int rhs) -> bool { return lhs < rhs; });
                break;
            case 2:
                filtered = base.filter(bufferNum, [](int lhs, int rhs) -> bool { return lhs == rhs; });
                break;
            case 3:
                filtered = base.filter(bufferNum, [](int lhs, int rhs) -> bool { return lhs > rhs; });
                break;
            default:
                std::cout << "Such filter key doesn't exist" << std::endl;
                break;
            }

            if (filtered.empty())
            {
                std::cout << "No items matching the condition" << std::endl;
            }
            else
            {
                base.writeHat(std::cout);
                for (const auto &item : filtered)
                {
                    std::cout << item;
                }
            }
            sleep(showTime+2);
            break;
        case 7:
            std::cout << "Enter number of positions for report: ";
            std::cin >> bufferNum;

            std::cout << "Report with" << ' ' << bufferNum << ' ' << "max costed items in base" << std::endl;
            base.reportMaxCost(bufferNum);
            sleep(showTime+2);
            break;
        case 8:
            std::cout << "Enter number of positions for report: ";
            std::cin >> bufferNum;
            
            std::cout << "Report with" << ' ' << bufferNum << ' ' << "min sized items in base" << std::endl;
            base.reportMinSize(bufferNum);
            sleep(showTime+2);
            break;
        case 9:
            std::cout << "Choose genre for report: ";
            getline(std::cin, buffer);

            base.reportChosenGenre(buffer);
            sleep(showTime+2);
            break;
        case 10:
            return; 
            break;
        default:
            std::cout << "Such command doesn't exist" << std::endl;
            sleep(3);
            break;
        }
        printf("\e[1;1H\e[2J");
    } while (true);
}