// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "GameWindow.h"

namespace Snake2D
{
    CGameWindow::CGameWindow(const unsigned int width,
                             const unsigned int height)
        : RenderWindow{ sf::VideoMode(width, height), "Snake2D" }
    {
        setFramerateLimit(10);
    }
}
