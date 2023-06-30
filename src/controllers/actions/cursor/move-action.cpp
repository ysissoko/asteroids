#include "src/controllers/actions/cursor/move-action.hpp"

namespace actions::cursor
{
    MoveAction::MoveAction(std::shared_ptr<Cursor> cursor) : cursor_{cursor}
    {
    }

    void MoveAction::Execute()
    {
        spdlog::debug("executing move action");
        cursor_->Move();
    }
}
