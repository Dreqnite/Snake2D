// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "MainMenuItemModel.h"

namespace Snake2D
{
    CMainMenuItemModel::CMainMenuItemModel(const Snake2D::EMenuItem type,
                                           const sf::String& text,
                                           const Snake2D::EAction scene)
        : m_type{ type }
        , m_text{ text }
        , m_action{ scene }
    {}

    CMainMenuItemModel::~CMainMenuItemModel() {}
}
