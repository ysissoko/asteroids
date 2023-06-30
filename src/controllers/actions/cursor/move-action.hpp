#ifndef MOVE_UP_ACTION_H
#define MOVE_UP_ACTION_H

#include <src/ui/cursor.hpp>
#include <src/controllers/actions/action.hpp>

namespace actions::cursor
{
    class MoveAction : public Action
    {
    public:
        explicit MoveAction(std::shared_ptr<Cursor>);
        void Execute() override;

    private:
        std::shared_ptr<Cursor> cursor_;
    };
}

#endif
