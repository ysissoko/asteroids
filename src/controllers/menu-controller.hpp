#ifndef MENU_CTRL_H
#define MENU_CTRL_H

#include "src/ui/cursor.hpp"
#include "src/controllers/controller.hpp"
#include "src/controllers/ievent-handler.hpp"

class MenuController : public Controller
{
    public:
        MenuController(std::shared_ptr<Cursor> cursor);
    private:
        void InitActions(std::shared_ptr<Cursor> cursor);
};

#endif
