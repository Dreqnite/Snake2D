// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML\Graphics.hpp>

#include "ResourceManager.h"

namespace Snake2D
{
    class CController
    {
    public:
        CController(const int rtWidth,
                    const int rtHeight)
            : m_textureManager{}
            , m_rendered{}
        {
            m_rendered.create(rtWidth, rtHeight);
        }

        virtual                     ~CController() {}

        virtual sf::Sprite          execute(void* args)
        {
            return sf::Sprite(m_rendered.getTexture());
        }

        virtual bool                handleInput(const sf::Keyboard::Key key) = 0;
    protected:
        Snake2D::TextureManager     m_textureManager;
        sf::RenderTexture           m_rendered;
    };
}

#endif // !CONTROLLER_H

