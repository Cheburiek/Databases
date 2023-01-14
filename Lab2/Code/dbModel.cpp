#include "baseModel.h"

using namespace Model;

baseModel::baseModel(/* args */)
{
}

baseModel::baseModel(const std::string usr, const std::string pswd, const std::string db)
{
    baseUsername = usr;
    basePassword = pswd;
    baseName = db;

    baseConnection = nullptr;
}

baseModel::~baseModel(void)
{
}

void baseModel::setMenuChoice(int _ch)
{
    valMenuChoice = _ch;
}

void baseModel::setTableChoice(int _ch)
{
    valTableChoice = _ch;
    baseModel::baseGetColumnsFromChoice();
}

void baseModel::setColumnChoice(int _ch)
{
    valColumnChoice = _ch;
}

void baseModel::setSearchChoice(int _ch)
{
    valSearchChoice = _ch;
}

void baseModel::setQuery(std::string _str)
{
    query = _str;
}

int baseModel::returnTableChoice(void)
{
    return valTableChoice;
}

int baseModel::returnMenuChoice(void)
{
    return valMenuChoice;
}

int baseModel::returnColumnChoice(void)
{
    return valColumnChoice;
}

int baseModel::returnSearchChoice(void)
{
    return valSearchChoice;
}

std::string baseModel::returnQuery(void)
{
    return query;
}

std::vector<std::string> baseModel::getListTables(void)
{
    baseModel::baseGetTablesFromChoice();
    return vertorTableNames;
}

std::vector<std::string> baseModel::getListColums(void)
{
    return vectorColumnsNames;
}

std::vector<std::vector<std::string>> baseModel::getListTableContents(void)
{
    return vectorTableData;
}

std::string baseModel::returnColumn(int _ind)
{
    return vectorColumnsNames.at(_ind);
}

std::string baseModel::returnTable(int _ind)
{
    return vertorTableNames.at(_ind);
}

int baseModel::returnDataType(int _ind)
{
    return vectorColumnVarTypes.at(_ind);
}

int baseModel::returnSizeOfListColumn(void)
{
    return vectorColumnsNames.size();
}

baseSQLlink baseModel::baseConnect(void)
{
    std::string result = "user=" + baseUsername;
    if (basePassword != "0")
    {
        result = result + " password=" + basePassword;
    }

    result = result + " dbname=" + baseName;

    std::cout << " > Connecting with params: " << result << std::endl;

    baseConnection = PQconnectdb(result.c_str());

    if (PQstatus(baseConnection) == CONNECTION_BAD)
    {
        std::cout << "(!) Connection failed!" << std::endl;
        
        
    }

    std::cout << "(*) Connection successfull!" << std::endl;
    std::cout << std::endl; 
}

baseSQLlink baseModel::baseTerminate(void)
{
    PQfinish(baseConnection);
    std::cout << "(*) Connection terminated!" << std::endl;
    exit(0); 
}

baseSQLlink baseModel::baseGetTablesFromChoice(void)
{
    vertorTableNames.clear();
    PGresult *res = PQexec(baseConnection, "SELECT table_name FROM information_schema.tables "
                                         "WHERE table_schema = 'public'");

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << PQresultErrorMessage(res) << std::endl;
        PQclear(res);     
    }

    int rows = PQntuples(res);

    for (int i = 0; i < PQntuples(res); i++)
    {
        vertorTableNames.push_back(PQgetvalue(res, i, 0));
    }  
}

baseSQLlink baseModel::baseGetColumnsFromChoice(void)
{
    vectorColumnsNames.clear();
    vectorColumnVarTypes.clear();
    std::string path = "SELECT * FROM public.\"" + vertorTableNames.at(valTableChoice) + "\"";
    PGresult *res = PQexec(baseConnection, path.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << std::endl
                  << " >> No data retrieved from " << baseName << ". Abort function << " << std::endl;
        PQclear(res);
        
        
    }

    for (int i = 0; i < PQnfields(res); i++)
    {
        vectorColumnsNames.push_back(PQfname(res, i));
        vectorColumnVarTypes.push_back(PQftype(res, i));
    }

    PQclear(res);
}

int baseModel::baseGetColumnsFromQuery(void)
{
    vectorColumnsNames.clear();
    vectorColumnVarTypes.clear();
    PGresult *res = PQexec(baseConnection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << PQresultErrorMessage(res) << std::endl;
        PQclear(res);
        return 0;
    }

    for (int i = 0; i < PQnfields(res); i++)
    {
        vectorColumnsNames.push_back(PQfname(res, i));
        vectorColumnVarTypes.push_back(PQftype(res, i));
    }

    PQclear(res);
    return 1;
}

baseSQLlink baseModel::baseQuerySend(void)
{
    PGresult *res = PQexec(baseConnection, "BEGIN");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("BEGIN command failed\n");
        PQclear(res);  
    }

    res = PQexec(baseConnection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << std::endl
                  << PQerrorMessage(baseConnection) << std::endl;
        PQclear(res);
    }

    res = PQexec(baseConnection, "COMMIT");

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("COMMIT command failed\n");
        PQclear(res);    
    } 
}

baseSQLlink baseModel::baseGetTableContents(void)
{
    vectorTableData.clear();
    baseGetTablesFromChoice();
    baseGetColumnsFromChoice();
    std::string path = "SELECT * FROM public.\"" + vertorTableNames.at(valTableChoice) + "\"";
    path += " ORDER BY \"" + vectorColumnsNames.at(0) + "\"";
    PGresult *res = PQexec(baseConnection, path.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << "No data retrieved. Abort function" << std::endl;
        PQclear(res); 
    }

    valCountRow = PQntuples(res);
    valCountColumn = PQnfields(res);

    std::vector<std::string> lsttmp;
    for (uint16_t i = 0; i < valCountRow; i++)
    {
        for (uint16_t j = 0; j < valCountColumn; j++)
        {
            lsttmp.push_back(PQgetvalue(res, i, j));
        }
        vectorTableData.push_back(lsttmp);
        lsttmp.clear();
    }

    PQclear(res);
}

int baseModel::baseGetResultFromQuery(void)
{
    vectorTableData.clear();
    baseGetColumnsFromQuery();


    PGresult *res = PQexec(baseConnection, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        std::cout << std::endl
                  << PQerrorMessage(baseConnection) << std::endl;
        PQclear(res);
        return 0;
    }

    valCountRow = PQntuples(res);
    valCountColumn = PQnfields(res);

    std::vector<std::string> lsttmp;
    for (uint16_t i = 0; i < valCountRow; i++)
    {
        for (uint16_t j = 0; j < valCountColumn; j++)
        {
            lsttmp.push_back(PQgetvalue(res, i, j));
        }
        vectorTableData.push_back(lsttmp);
        lsttmp.clear();
    }

    return 1;
}