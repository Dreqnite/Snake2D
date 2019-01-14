// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef MAINMENUCONTROLLER_H
#define MAINMENUCONTROLLER_H

#include "Controller.h"
#include "MainMenuModel.h"

namespace Snake2D
{
    class CMainMenuController
        : public Snake2D::CController
    {
    public:
                                    CMainMenuController();
                                    ~CMainMenuController();

        sf::Sprite                  execute(void* args) override;
        bool                        handleInput(const sf::Keyboard::Key key) override;
        
        void                        renderBackground();
        void                        renderMenu(const std::size_t startItem_n);
        void                        initMenuItems();
    private:
        Snake2D::FontManager        m_fontManager;
        Snake2D::CMainMenuModel     m_mainMenu;
        std::size_t                 m_selectedItem_n;
    };
}

#endif // !MAINMENUCONTROLLER_H
