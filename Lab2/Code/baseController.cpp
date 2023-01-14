#include "baseController.h"
using namespace Controller;

baseController::baseController(void)
{
}

baseController::baseController(Model::baseModel *_mdl, View::baseView *_vw)
{
    viewObj = _vw;
    modObj = _mdl;
}

baseController::~baseController(void)
{
}

int baseController::menuChoiceHandler(void)
{
    while (1)
    {
        int input = viewObj->inputIntMenu();
        switch (input)
        {
        case optionsMenu::MENU_INSERT:
        case optionsMenu::MENU_REMOVE:
        case optionsMenu::MENU_EDIT:
        case optionsMenu::MENU_RAND:
        case optionsMenu::MENU_SEARCH:
        case optionsMenu::MENU_SHOWTABLE:
        case optionsMenu::MENU_TERMINATE:
            return input;
            break;
        default:
            std::cout << " Wrong action. Try again." << std::endl;
            break;
        }
    }

    return optionsMenu::MENU_DEFAULT;
}

int baseController::tableChoiceHandler(void)
{
    std::vector<std::string> lst = modObj->getListTables();
    while (1)
    {
        int input = viewObj->inputInt();
        if (input >= 0 && input < lst.size())
        {
            return input;
        }
    }
}

void baseController::concatVarTypes(std::string *_str, int _iter)
{
    switch (modObj->returnDataType(_iter))
    {
    case 23:
        *_str += "::integer";
        break;
    case 1043:
        *_str += "::character varying";
        break;
    case 1082:
        *_str += "::date";
        break;
    case 1114:
        *_str += "::timestamp without time zone";
        break;
    case 16:
        *_str += "::bool";
        break;
    default:
        break;
    }
}

void baseController::stepEstablishConnection(void)
{
    std::cout << std::endl
              << "\t\t MAISTRENKO OLGA KV-02 LAB2\n"
              << std::endl
              << std::endl;
    modObj->baseConnect();
}

void baseController::stepMenu(void)
{
    modObj->setMenuChoice(menuChoiceHandler());
}

void baseController::stepDBOperations(void)
{
    /* Показати на екрані те, що вибрав користувач */
    viewObj->viewMenubaseOperations(modObj->returnMenuChoice());

    /* Виконати дію на вибір користувача */
    switch (modObj->returnMenuChoice())
    {
    case optionsMenu::MENU_INSERT:
        /* Початок вставки */
        performDataInsert();
        break;
    case optionsMenu::MENU_REMOVE:
        /* Початок видалення */
        performDataDelete();
        break;
    case optionsMenu::MENU_EDIT:
        /* Початок редагування */
        performDataEdit();
        break;
    case optionsMenu::MENU_RAND:
        /* Початок рандомної вставки */
        performDataInsertRandom();
        break;
    case optionsMenu::MENU_SEARCH:
        /* Початок пошуку */
        performDataSearch();
        break;
    case optionsMenu::MENU_SHOWTABLE:
        /* Початок виводу таблиці*/
        performDataShow();
        break;
    case optionsMenu::MENU_TERMINATE:
        /* Перервати з'єднання */
        performTerminateConnection();
        break;

    default:
        break;
    }
}

void baseController::performDataInsert(void)
{
    /* Показати список доступних таблиць */
    viewObj->viewList(modObj->getListTables());

    /* Вибір між таблицями */
    modObj->setTableChoice(tableChoiceHandler());

    /* Показати список доступних стовпців */
    viewObj->viewList(modObj->getListColums());

    std::string comSQL = "INSERT INTO public.\"" + modObj->returnTable(modObj->returnTableChoice()) + "\" (";

    /* Збірка команди */
    for (int i = 1; i < modObj->returnSizeOfListColumn(); i++)
    {
        comSQL += "\"";
        comSQL += modObj->returnColumn(i);
        if (i != modObj->returnSizeOfListColumn() - 1)
        {
            comSQL += "\", ";
        }
        else
        {
            comSQL += "\") ";
        }
    }

    comSQL += "VALUES (";

    for (int i = 1; i < modObj->returnSizeOfListColumn(); i++)
    {
        std::cout << "Enter value for " << modObj->returnColumn(i) << " column" << std::endl;
        std::string inp = viewObj->getString();
        comSQL += "'" + inp + "'";

        concatVarTypes(&comSQL, i);

        if (i != modObj->returnSizeOfListColumn() - 1)
        {
            comSQL += ", ";
        }
        else
        {
            comSQL += ")";
        }
    }

    /* Показати складену команду */
    std::cout << " (##) Result command: ";
    viewObj->viewString(comSQL);

    /* Встановити рядок запиту */
    modObj->setQuery(comSQL);

    /* Надіслати запит до бази даних */
    modObj->baseQuerySend();
}

void baseController::performDataDelete(void)
{
    /* Показати список доступних таблиць */
    viewObj->viewList(modObj->getListTables());

    /* Вибір між таблицями */
    modObj->setTableChoice(tableChoiceHandler());

    /* Отримати вміст таблиці з бази даних */
    modObj->baseGetTableContents();

    viewObj->viewTableContents(modObj->getListTableContents(), modObj->getListColums());

    std::cout << "Choose ID to delete" << std::endl;
    std::string comSQL = "DELETE FROM public.\"" + modObj->returnTable(modObj->returnTableChoice());
    comSQL += "\" WHERE \"" + modObj->returnColumn(0) + "\"";
    comSQL += " IN (" + viewObj->getString() + ")";

    /* Показати складену команду */
    std::cout << " (##) Result command: ";
    viewObj->viewString(comSQL);

    /* Встановити рядок запиту */
    modObj->setQuery(comSQL);

    /* Надіслати запит до бази даних */
    modObj->baseQuerySend();
}

void baseController::performDataInsertRandom(void)
{
    /* Показати список доступних таблиць */
    viewObj->viewList(modObj->getListTables());

    /* Вибір між таблицями */
    modObj->setTableChoice(tableChoiceHandler());

    /* Отримати вміст таблиці з бази даних */
    modObj->baseGetTableContents();

    std::string comSQL = "INSERT INTO public.\"" + modObj->returnTable(modObj->returnTableChoice()) + "\" (";

    for (int i = 1; i < modObj->returnSizeOfListColumn(); i++)
    {
        comSQL += "\"";
        comSQL += modObj->returnColumn(i);
        if (i != modObj->returnSizeOfListColumn() - 1)
        {
            comSQL += "\", ";
        }
        else
        {
            comSQL += "\") ";
        }
    }

    comSQL += "VALUES (";

    for (int i = 1; i < modObj->returnSizeOfListColumn(); i++)
    {
        switch (modObj->returnDataType(i))
        {
        case 23:
            comSQL += "random()* (100-1 + 1) + 1";
            break;
        case 1043:
            comSQL += "substr(md5(random()::text), 0, 10)";
            break;
        default:
            break;
        }

        if (i != modObj->returnSizeOfListColumn() - 1)
        {
            comSQL += ", ";
        }
        else
        {
            comSQL += ")";
        }
    }

    /* Показати складену команду */
    std::cout << " (##) Result command: ";
    viewObj->viewString(comSQL);

    /* Встановити рядок запиту */
    modObj->setQuery(comSQL);

    std::cout << " Choose how many rows of random data will be generated: ";
    int _quantity = viewObj->inputInt();
    for (int i = 0; i < _quantity; i++)
    {
        /* Надіслати запит до бази даних */
        modObj->baseQuerySend();
    }
}

void baseController::performDataEdit(void)
{
    /* Показати список доступних таблиць */
    viewObj->viewList(modObj->getListTables());
    /* Вибір між таблицями */
    modObj->setTableChoice(tableChoiceHandler());
    /* Отримати вміст таблиці з бази даних */
    modObj->baseGetTableContents();

    viewObj->viewTableContents(modObj->getListTableContents(), modObj->getListColums());

    std::string comSQL = "UPDATE public.\"" + modObj->returnTable(modObj->returnTableChoice()) + "\" SET ";
    std::cout << "Choose ID to edit" << std::endl;
    /* Виберіть елемент для редагування */
    std::string strID = viewObj->getString();
    std::cout << "Choose column to edit" << std::endl;
    /* Показати список доступних стовпців */
    viewObj->viewList(modObj->getListColums());

    /* Виберіть стовпець для редагування */
    modObj->setColumnChoice(viewObj->inputInt());

    comSQL += "\"" + modObj->returnColumn(modObj->returnColumnChoice()) + "\" = ";
    std::cout << "Set value: " << std::endl;
    comSQL += "'" + viewObj->getString() + "'";

    /* Визначити тип даних */
    concatVarTypes(&comSQL, modObj->returnColumnChoice());

    comSQL += " WHERE \"" + modObj->returnColumn(0) + "\" = " + strID;

    /* Показати складену команду */
    std::cout << " (##) Result command: ";
    viewObj->viewString(comSQL);

    /* Встановити рядок запиту */
    modObj->setQuery(comSQL);

    /* Надіслати запит до бази даних */
    modObj->baseQuerySend();
}

void baseController::performDataSearch(void)
{
    /* Виберіть варіант пошуку */
    viewObj->viewSearchOptions();

    /* Встановити опцію пошуку в моделі */
    modObj->setSearchChoice(viewObj->inputInt());

    std::string comSQL;
    switch (modObj->returnSearchChoice())
    {
    case 1:
        comSQL += "SELECT * ";
        comSQL += "FROM public.\"Group\" ";
        comSQL += "WHERE \"capacity\" > ";
        std::cout << "Set start range: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " AND \"capacity\" < ";
        std::cout << "Set end range: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " ORDER BY \"capacity\"";
        break;
    case 2:
        comSQL += "SELECT \"student_id\", \"name\", \"surname\", \"code\", \"number\" ";
        comSQL += "FROM public.\"Student\" ";
        comSQL += "JOIN public.\"Group\" ON \"Student\".\"group_id\" = \"Group\".\"group_id\" ";
        comSQL += "WHERE \"code\" = ";
        std::cout << "Set group code: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " ORDER BY \"code\"";
        break;
    case 3:
        comSQL += "SELECT \"Subject\".\"name\", \"Lector\".\"name\", \"surname\", \"code\", \"Group\".\"number\", \"Classroom\".\"number\" ";
        comSQL += "FROM public.\"Student_Base\" ";
        comSQL += "JOIN public.\"Group\" ON \"Student_Base\".\"group_id\" = \"Group\".\"group_id\" ";
        comSQL += "JOIN public.\"Lector\" ON \"Student_Base\".\"lector_id\" = \"Lector\".\"lector_id\" ";
        comSQL += "JOIN public.\"Subject\" ON \"Student_Base\".\"subject_id\" = \"Subject\".\"subject_id\" ";
        comSQL += "JOIN public.\"Classroom\" ON \"Student_Base\".\"class_id\" = \"Classroom\".\"class_id\" ";
        comSQL += "WHERE \"code\" = ";
        std::cout << "Set group code: ";
        comSQL += "'" + viewObj->getString() + "'";
        comSQL += " ORDER BY \"Group\".\"number\"";
        break;
    default:
        break;
    }

    /* Показати складену команду */
    std::cout << " (##) Result command: ";
    viewObj->viewString(comSQL);

    /* Встановити рядок запиту */
    modObj->setQuery(comSQL);

    /* Надіслати запит і записати результати до векторів у моделі */
    if (modObj->baseGetResultFromQuery() != 0)
    {
        /* Показати дані з векторної таблиці в моделі */
        viewObj->viewTableContents(modObj->getListTableContents(), modObj->getListColums());
    }
}

void baseController::performDataShow(void)
{
    /* Показати список доступних таблиць */
    viewObj->viewList(modObj->getListTables());

    /* Вибір між таблицями */
    modObj->setTableChoice(tableChoiceHandler());

    /* Початок створення запиту */
    std::string comSQL = "SELECT * FROM public.\"" + modObj->returnTable(modObj->returnTableChoice()) + "\"";
    std::cout << "Set LIMIT: (0 to show everything): " << std::endl;

    /* Встановити обмеження для рядків */
    int LIMIT = viewObj->inputInt();

    switch (LIMIT)
    {
    case 0:

        break;

    default:
        comSQL += " LIMIT " + std::to_string(LIMIT);
        break;
    }

    /* Показати складену команду */
    std::cout << " (##) Result command: ";
    viewObj->viewString(comSQL);

    /* Встановити рядок запиту */
    modObj->setQuery(comSQL);

    /* Надіслати запит і записати результати до векторів у моделі */
    if (modObj->baseGetResultFromQuery() != 0)
    {
        /* Показати дані з векторної таблиці в моделі */
        viewObj->viewTableContents(modObj->getListTableContents(), modObj->getListColums());
    }
}

void baseController::performTerminateConnection(void)
{
    modObj->baseTerminate();
}