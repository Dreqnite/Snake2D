// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef ENDGAMECONTROLLER_H
#define ENDGAMECONTROLLER_H

#include "Controller.h"

namespace Snake2D
{
    class CEndgameController
        : public Snake2D::CController
    {
    public:
                                    CEndgameController();
                                    ~CEndgameController();
        sf::Sprite                  execute(void* args) override;
        bool                        handleInput(const sf::Keyboard::Key key) override;
    private:
        Snake2D::FontManager        m_fontManager;
    };
}

#endif // !ENDGAMECONTROLLER_H



