// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef ABOUTCONTROLLER_H
#define ABOUTCONTROLLER_H

#include "Controller.h"

namespace Snake2D
{
    class CAboutController
        : public Snake2D::CController
    {
    public:
                                    CAboutController();
                                    ~CAboutController();
        bool                        handleInput(const sf::Keyboard::Key key) override;
    private:
        Snake2D::FontManager        m_fontManager;
    private:
        void                        initializaAboutScreen();
    };
}

#endif // !ABOUTCONTROLLER_H
