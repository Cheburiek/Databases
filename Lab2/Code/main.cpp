#include <iostream>
#include "baseController.h"

int main()
{
    std::string username = "postgres";
    std::string password = "0";
    std::string databasename = "computerclub";

    Model::baseModel mdl(username, password, databasename);
    View::baseView vw;
    Controller::baseController ctrl(&mdl, &vw);

    ctrl.stepEstablishConnection();

    while (1)
    {
        ctrl.stepMenu();
        ctrl.stepDBOperations();
    }

    return 0;
}