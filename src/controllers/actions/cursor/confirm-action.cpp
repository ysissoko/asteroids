#include "src/controllers/actions/cursor/confirm-action.hpp"

namespace actions::cursor
{
    ConfirmAction::ConfirmAction(std::shared_ptr<Cursor> cursor) : cursor_{cursor}
    {
    }

    void ConfirmAction::Execute()
    {
        spdlog::debug("executing confirm action");
        cursor_->Confirm();
    }
}
