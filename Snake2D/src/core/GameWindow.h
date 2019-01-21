// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "SFML/Graphics.hpp"

namespace Snake2D
{
    class CGameWindow : public sf::RenderWindow
    {
    public:
        CGameWindow(const unsigned int width,
                    const unsigned int height);
    };

}

#endif // !GAMEWINDOW_H

