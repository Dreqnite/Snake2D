// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>
#include <memory>

#include "MainMenuItemModel.h"

namespace Snake2D
{
    using MainMenuItemPtr = std::unique_ptr<Snake2D::CMainMenuItemModel>;
    class CMainMenuModel
    {
    public:
                                            CMainMenuModel();
                                            ~CMainMenuModel();
        inline const std::size_t getSize() const noexcept
        {
            return m_menu.size();
        }
        inline const Snake2D::MainMenuItemPtr& 
            getMenuItem(const std::size_t item_n)  const noexcept
        {
            return m_menu.at(item_n);
        }
        void addMenuItem(const Snake2D::EMenuItem itemType,
                         sf::String&& title,
                         const Snake2D::EAction scene);
        std::size_t                         findMenuItem(const Snake2D::EMenuItem type) const;
    private:
        std::vector<MainMenuItemPtr>        m_menu;
    };
}

#endif // !MAINMENU_H
