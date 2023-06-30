#ifndef CONFIRM_ACTION__H
#define CONFIRM_ACTION__H

#include <src/ui/cursor.hpp>
#include <src/controllers/actions/action.hpp>

namespace actions::cursor
{
    class ConfirmAction : public Action
    {
    public:
        explicit ConfirmAction(std::shared_ptr<Cursor>);
        void Execute() override;

    private:
        std::shared_ptr<Cursor> cursor_;
    };
}

#endif
