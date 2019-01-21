// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <queue>
#include <mutex>
#include <atomic>

#include <SFML/Graphics.hpp>

namespace Snake2D
{

    class CInputHandler
    {
    public:
                                            CInputHandler();
                                            ~CInputHandler();
        inline std::size_t getSize() const noexcept
        {
            return m_pressedKeys.size();
        }
        sf::Keyboard::Key                   popKey();
        void                                run();
        void                                exit();
    private:
        std::vector<sf::Keyboard::Key>      m_allowedKeys;
        std::queue<sf::Keyboard::Key>       m_pressedKeys;
        std::mutex                          m_mutex;
        std::atomic_bool                    m_running;
    };

}

#endif // !INPUTHANDLER_H
