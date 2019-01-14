// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "GameManager.h"

#include <thread>

namespace Snake2D
{
    CGameManager::CGameManager()
        : m_gameWindow{ 
            std::make_unique<Snake2D::CGameWindow>(
                Snake2D::Window::width_px,
                Snake2D::Window::height_px
            ) 
          }
        , m_scenes{
              { 
                  Snake2D::EAction::LoadMenuScreen,
                  std::bind(&CGameManager::loadMenuScreen, this) 
              },
              { 
                  Snake2D::EAction::ResumeGame,
                  std::bind(&CGameManager::resumeGame, this) 
              },
              {
                  Snake2D::EAction::StartNewGame,
                  std::bind(&CGameManager::startNewGame, this)
              },
              {
                  Snake2D::EAction::LoadAboutScreen,
                  std::bind(&CGameManager::loadAboutScreen, this)
              },
              {
                  Snake2D::EAction::LoadEndGameScreen,
                  std::bind(&CGameManager::loadEndgameScreen, this)
              },
              { 
                  Snake2D::EAction::ExitGame, 
                  std::bind(&CGameManager::exitGame, this) 
              }
          }
        , m_mainMenuController{}
        , m_gameController{}
        , m_endgameController{}
        , m_aboutController{}
        , m_inputHandler{}
    {}

    CGameManager::~CGameManager() {}

    void CGameManager::run()
    {
        std::thread inputHandler{
            &CInputHandler::run, std::ref(m_inputHandler)
        };

        while (m_gameWindow->isOpen())
        {
            sf::Event e{};
            while (m_gameWindow->pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                {
                    m_inputHandler.exit();
                    if (inputHandler.joinable())
                    {
                        inputHandler.join();
                    }
                    m_gameWindow->close();
                }
            }

            m_gameWindow->clear(sf::Color::Black);

            sf::Sprite renderedScene = 
                m_scenes.at(Snake2D::g_currentAction)();

            if (Snake2D::g_currentAction == Snake2D::EAction::ExitGame)
            {
                m_inputHandler.exit();
                if (inputHandler.joinable())
                {
                    inputHandler.join();
                }
                m_gameWindow->close();
                break;
            }

            m_gameWindow->draw(renderedScene);
            m_gameWindow->display();
        }
    }

    sf::Sprite CGameManager::startNewGame()
    {
        m_gameController.endGame();
        return resumeGame();
    }

    sf::Sprite CGameManager::loadMenuScreen()
    {
        handleInput<CMainMenuController>(m_mainMenuController);
        return m_mainMenuController.execute(nullptr);
    }

    sf::Sprite CGameManager::resumeGame()
    {
        handleInput<CGameController>(m_gameController);
        return m_gameController.execute(nullptr);
    }

    sf::Sprite CGameManager::loadAboutScreen()
    {
        handleInput<CAboutController>(m_aboutController);
        return m_aboutController.execute(nullptr);
    }

    /*
    sf::Sprite CGameManager::loadOptionsScreen()
    {

    }
    */

    sf::Sprite CGameManager::loadEndgameScreen()
    {
        handleInput<CEndgameController>(m_endgameController);
        return m_endgameController.execute(
            reinterpret_cast<void*>(m_gameController.getScore())
        );
    }

    sf::Sprite CGameManager::exitGame()
    {
        m_gameWindow->close();
        return sf::Sprite();
    }
}
