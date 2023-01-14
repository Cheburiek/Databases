#ifndef _BASE_CONTROLLER_H_
#define _BASE_CONTROLLER_H_

#include <iostream>
#include <unordered_map>
#include "baseModel.h"
#include "baseView.h"

namespace optionsMenu
{
    enum userChoice : int
    {
        MENU_INSERT = 1,
        MENU_REMOVE,
        MENU_EDIT,
        MENU_RAND,
        MENU_SEARCH,
        MENU_SHOWTABLE,
        MENU_TERMINATE = 0,
        MENU_DEFAULT = 10
    };
};

namespace Controller
{
    class baseController
    {
    private:
        /* Перегляд вказівника об’єкта */
        View::baseView *viewObj;
        /* Вказівник об’єкта моделі */
        Model::baseModel *modObj;

    public:
        baseController(void);
        baseController(Model::baseModel *_mdl, View::baseView *_vw);
        ~baseController();

        /* Функція вибору меню */
        int menuChoiceHandler(void);
        /* Функція вибору таблиці */
        int tableChoiceHandler(void);
        /* Визначення типів даних, отриманих для бази даних */
        void concatVarTypes(std::string *_str, int _iter);

        /* Логічні кроки */

        /* На цьому кроці ви встановлюєте з’єднання з базою даних */
        void stepEstablishConnection(void);
        /* На цьому кроці ви вибираєте, яка операція буде виконана з базою даних */
        void stepMenu(void);
        /* На цьому кроці вибрана операція буде виконана з базою даних*/
        void stepDBOperations(void);

        /* Операції з базою даних */

        /* Виконати вставку даних в базу даних */
        void performDataInsert(void);
        /* Виконати видалення даних в базі даних */
        void performDataDelete(void);
        /* Виконати довільну вставку даних у базу даних*/
        void performDataInsertRandom(void);
        /* Виконати редагування даних у базі даних */
        void performDataEdit(void);
        /* Виконати пошук даних у базі даних */
        void performDataSearch(void);
        /* Відображення даних у базі даних */
        void performDataShow(void);
        /* Виконати від'єднання від бази даних */
        void performTerminateConnection(void);
    };

};

#endif //_BASE_CONTROLLER_H_