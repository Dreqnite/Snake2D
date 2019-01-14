// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SFML\Graphics.hpp"

#include "..\common\Parameters.h"
#include "GameWindow.h"
#include "InputHandler.h"
#include "MainMenuController.h"
#include "GameController.h"
#include "AboutController.h"
#include "EndgameController.h"

namespace Snake2D
{
    class CGameManager
    {
    public:
                                            CGameManager();
                                            ~CGameManager();
        void                                run();
    private:
        std::unique_ptr<CGameWindow>        m_gameWindow;
        std::map<Snake2D::EAction, std::function<sf::Sprite(void)>>     
                                            m_scenes;
        Snake2D::CMainMenuController        m_mainMenuController;
        Snake2D::CGameController            m_gameController;
        Snake2D::CEndgameController         m_endgameController;
        Snake2D::CAboutController           m_aboutController;
        Snake2D::CInputHandler              m_inputHandler;
    private:
        sf::Sprite                          startNewGame();
        sf::Sprite                          loadMenuScreen();
        sf::Sprite                          resumeGame();
        sf::Sprite                          loadAboutScreen();
        sf::Sprite                          loadEndgameScreen();
        sf::Sprite                          exitGame();

        template <typename T>
        void handleInput(T& controller)
        {
            sf::Keyboard::Key key{ m_inputHandler.popKey() };
            while (!controller.handleInput(key))
            {
                if (key == sf::Keyboard::Key::Unknown)
                {
                    break;
                }
                key = m_inputHandler.popKey();
            }
        }
    };

}

#endif // !GAMEMANAGER_H

