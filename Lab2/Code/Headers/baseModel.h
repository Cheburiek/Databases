#pragma once
#include <iostream>
#include <vector>
#include "libpq-fe.h"

typedef void baseSQLlink;

namespace Model
{
    class baseModel
    {
    private:
        /* ---------- Variables that contain data about PG ---------- */

        PGconn *baseConnection;

        std::string baseUsername;
        std::string basePassword;
        std::string baseName;

        std::string query;

        /* ----- Saved values for use in functions ----- */

        int valMenuChoice;
        int valTableChoice;
        int valColumnChoice;
        int valSearchChoice;

        int valCountRow;
        int valCountColumn;

        /* --- Vectors for containing data from database --- */

        std::vector<std::string> vertorTableNames;
        std::vector<std::string> vectorColumnsNames;
        std::vector<std::vector<std::string>> vectorTableData;
        std::vector<int> vectorColumnVarTypes;
        
    public:
        baseModel(/* args */);
        baseModel(const std::string usr, const std::string pswd, const std::string db);
        ~baseModel();

        /* ----- Database info setters and getters ----- */

        std::vector<std::string> getListTables(void);
        std::vector<std::string> getListColums(void);
        std::vector<std::vector<std::string>> getListTableContents(void);

        /* -------- Setters and Getters -------- */

        std::string returnTable(int _ind);
        std::string returnColumn(int _ind);

        int returnDataType(int _ind);
        int returnSizeOfListColumn(void);

        void setMenuChoice(int _ch);
        int returnMenuChoice(void);

        void setTableChoice(int _ch);
        int returnTableChoice(void);

        void setColumnChoice(int _ch);
        int returnColumnChoice(void);

        void setSearchChoice(int _ch);
        int returnSearchChoice(void);

        void setQuery(std::string _str);
        std::string returnQuery(void);

        /* -------- SQL specific -------- */

        /* Connect to database */
        baseSQLlink baseConnect(void);
        /* Terminate connection to database */
        baseSQLlink baseTerminate(void);

        /* Get list of tables from database */
        baseSQLlink baseGetTablesFromChoice(void);
        /* Get list of columns from database. Depends on user choice of table */
        baseSQLlink baseGetColumnsFromChoice(void);

        /* Send query to database */
        baseSQLlink baseQuerySend(void);
        /* Get list of columns from database. Depends on query string */
        int baseGetColumnsFromQuery(void);
        /* Get table data from database. Depends on query string */
        int baseGetResultFromQuery(void);
        /* Get table data from database. Depends on user choice */
        baseSQLlink baseGetTableContents(void);
    };
};