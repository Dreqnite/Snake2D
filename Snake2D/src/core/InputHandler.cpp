// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "InputHandler.h"

#include <chrono>

#include "..\common\Parameters.h"

namespace Snake2D
{

    CInputHandler::CInputHandler()
        : m_allowedKeys{ 
              sf::Keyboard::Up,
              sf::Keyboard::Right,
              sf::Keyboard::Down,
              sf::Keyboard::Left,
              sf::Keyboard::Escape,
              sf::Keyboard::Return // Enter
          }
        , m_pressedKeys{}
        , m_mutex{}
        , m_running{ false }
    {}

    CInputHandler::~CInputHandler() {}

    void CInputHandler::run()
    {
        m_running.store(true);

        while (m_running.load())
        {
            for (const auto& key : m_allowedKeys)
            {
                if (sf::Keyboard::isKeyPressed(key))
                {
                    std::lock_guard<std::mutex> locker(m_mutex);
                    m_pressedKeys.push(key);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    sf::Keyboard::Key CInputHandler::popKey()
    {
        if (m_pressedKeys.size() == 0)
        {
            return sf::Keyboard::Key::Unknown;
        }

        sf::Keyboard::Key key = m_pressedKeys.front();

        std::lock_guard<std::mutex> locker(m_mutex);
        m_pressedKeys.pop();

        return key;
    }

    void CInputHandler::exit()
    {
        m_running.store(false);
    }
}
