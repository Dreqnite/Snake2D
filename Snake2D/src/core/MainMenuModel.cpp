// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "MainMenuModel.h"

#include <iostream>

#include "../common/Parameters.h"
#include "../common/Common.h"

namespace Snake2D
{
    CMainMenuModel::CMainMenuModel()
        : m_menu{}
    {}

    CMainMenuModel::~CMainMenuModel() {}

    void CMainMenuModel::addMenuItem(const Snake2D::EMenuItem type,
                                     sf::String&& title,
                                     const Snake2D::EAction scene)
    {
        m_menu.push_back(
            std::make_unique<Snake2D::CMainMenuItemModel>(
                type, std::move(title), scene
            )
        );
    }

    std::size_t CMainMenuModel::findMenuItem(const Snake2D::EMenuItem type) const
    {
        for (std::vector<MainMenuItemPtr>::const_iterator it = m_menu.cbegin();
             it != m_menu.cend(); 
             ++it)
        {
            if (it->get()->getType() == type)
            {
                return std::distance(m_menu.cbegin(), it);
            }
        }
        return 0;
    }
}


