#include "baseView.h"
#include "baseController.h"

using namespace View;

baseView::baseView(void)
{
}

baseView::~baseView(void)
{
}

void baseView::viewString(const std::string _str)
{
    std::cout << _str << std::endl;
}

void baseView::viewMenuMain(void)
{
    std::cout << std::endl;
    std::cout << " Welcome to your database! What do you want to do?" << std::endl;
    std::cout << " >> 1. Insert data in table" << std::endl;
    std::cout << " >> 2. Delete data from table" << std::endl;
    std::cout << " >> 3. Edit data in table" << std::endl;
    std::cout << " >> 4. Insert N rows of random data in table" << std::endl;
    std::cout << " >> 5. Search data in tables" << std::endl;
    std::cout << " >> 6. Show N table" << std::endl;
    std::cout << std::endl
              << " >> 0. Stop connection and exit the program" << std::endl;
}

void baseView::viewList(const std::vector<std::string> _lst)
{
    for (int i = 0; i < _lst.size(); i++)
    {
        std::cout << " >> " << i << ". " << _lst.at(i) << std::endl;
    }
}

std::string baseView::getString(void)
{
    std::string str;
    std::cout << " <INPUT>: ";
    std::getline(std::cin >> std::ws, str);
    return str;
}

int baseView::inputInt(void)
{
    int inp = 0;
    std::cout << " <INPUT>: ";
    std::cin >> inp;
    return inp;
}

int baseView::inputIntMenu(void)
{
    viewMenuMain();
    return inputInt();
}

void baseView::viewMenubaseOperations(const int _ch)
{
    switch (_ch)
    {
    case optionsMenu::MENU_INSERT:
        std::cout << " [You chose to insert data in table]" << std::endl;
        std::cout << "  Choose table:" << std::endl;
        break;
    case optionsMenu::MENU_REMOVE:
        std::cout << " [You chose to delete data in table]" << std::endl;
        std::cout << "  Choose table:" << std::endl;
        break;
    case optionsMenu::MENU_EDIT:
        std::cout << " [You chose to edit data in table]" << std::endl;
        std::cout << "  Choose table:" << std::endl;
        break;
    case optionsMenu::MENU_RAND:
        std::cout << " [You chose to insert N rows of random data in table]" << std::endl;
        std::cout << "  Choose table:" << std::endl;
        break;
    case optionsMenu::MENU_SEARCH:
        std::cout << " [You chose to search data in tables]" << std::endl;
        std::cout << "  Choose option:" << std::endl;
        break;
    case optionsMenu::MENU_SHOWTABLE:
        std::cout << " [You chose to Show N table]" << std::endl;
        std::cout << "  Choose table:" << std::endl;
        break;
    case optionsMenu::MENU_TERMINATE:
        std::cout << "  [You chose to top connection and exit the program]" << std::endl;
        break;

    default:
        std::cout << " There is no such option. Try again!" << std::endl;
        break;
    }
}

void baseView::viewSearchOptions(void)
{
    std::cout << std::endl;
    std::cout << "[1] Search Groups by max Students N > X; N < Y capacity" << std::endl;
    std::cout << "[2] Search Students by Group name" << std::endl;
    std::cout << "[3] Search Subjects by Group name" << std::endl;
}

void baseView::viewTableContents(const std::vector<std::vector<std::string>> _lst1, const std::vector<std::string> _lst2)
{
    int spaces = 30;

    for (int i = 0; i < _lst2.size(); i++)
    {
        std::cout << std::setw(spaces) << _lst2.at(i);
    }
    std::cout << std::endl
              << std::endl;
    for (int i = 0; i < _lst1.size(); i++)
    {
        for (int j = 0; j < _lst1[i].size(); j++)
        {
            std::cout << std::setw(spaces) << _lst1[i][j];
        }
        std::cout << std::endl;
        for (int k = 0; k < _lst2.size() * spaces; k++)
        {
            if (k > 8)
            {
                std::cout << "-";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}