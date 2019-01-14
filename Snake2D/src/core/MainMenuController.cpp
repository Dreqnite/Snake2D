// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "MainMenuController.h"

namespace Snake2D
{
    CMainMenuController::CMainMenuController()
        : CController(Snake2D::Window::width_px,
                      Snake2D::Window::height_px)
        , m_fontManager{}
        , m_mainMenu{}
        , m_selectedItem_n{ 1 }
    {
        m_textureManager.load(
            Snake2D::ETextureId::MenuBackground,
            Snake2D::g_imgDirPath + SNAKE2D_BACKGROUND_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::MenuBackgroundSnake,
            Snake2D::g_imgDirPath + SNAKE2D_SNAKEBGD_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::MenuLogo,
            Snake2D::g_imgDirPath + SNAKE2D_LOGO_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::MenuItemBackground,
            Snake2D::g_imgDirPath + SNAKE2D_MENUITEM_FILE_NAME,
            sf::IntRect()
        );
        m_fontManager.load(
            Snake2D::EFontId::Consola,
            Snake2D::g_fontsDirPath + "consola.ttf"
        );
        initMenuItems();
    }

    CMainMenuController::~CMainMenuController()
    {}

    bool CMainMenuController::handleInput(const sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Up:
            {
                if (m_selectedItem_n > static_cast<std::size_t>(!Snake2D::g_inGame))
                {
                    --m_selectedItem_n;
                }
            }
            break;
        case sf::Keyboard::Down:
            {
                if (m_selectedItem_n < m_mainMenu.getSize() - 1)
                {
                    ++m_selectedItem_n;
                }
            }
            break;
        case sf::Keyboard::Escape:
            {
                m_selectedItem_n = m_mainMenu.findMenuItem(
                    Snake2D::EMenuItem::Exit
                );
            }
            break;
        case sf::Keyboard::Return:
            {
                g_currentAction = 
                    m_mainMenu.getMenuItem(m_selectedItem_n).get()->getAction();
            }
            break;
        default:
            return false;
        }
        return true;
    }

    sf::Sprite CMainMenuController::execute(void* args)
    {
        m_rendered.clear(sf::Color::Blue);

        renderBackground();
        renderMenu(static_cast<std::size_t>(!Snake2D::g_inGame));
    
        return sf::Sprite(m_rendered.getTexture());
    }

    void CMainMenuController::initMenuItems()
    {
        m_mainMenu.addMenuItem(
            Snake2D::EMenuItem::ResumeGame, 
            "Resume Game", Snake2D::EAction::ResumeGame
        );
        m_mainMenu.addMenuItem(
            Snake2D::EMenuItem::StartNewGame, 
            "Start New Game", Snake2D::EAction::StartNewGame
        );
        m_mainMenu.addMenuItem(
            Snake2D::EMenuItem::Options,
            "Options", Snake2D::EAction::LoadOptionsScreen
        );
        m_mainMenu.addMenuItem(
            Snake2D::EMenuItem::About,
            "About", Snake2D::EAction::LoadAboutScreen
        );
        m_mainMenu.addMenuItem(
            Snake2D::EMenuItem::Exit,
            "Exit", Snake2D::EAction::ExitGame
        );
    }

    void CMainMenuController::renderBackground()
    {
        sf::Sprite sprite{};

        sprite.setTexture(
            *m_textureManager.get(Snake2D::ETextureId::MenuBackground)
        );
        m_rendered.draw(sprite);

        sprite.setTexture(
            *m_textureManager.get(Snake2D::ETextureId::MenuBackgroundSnake)
        );
        sprite.setPosition(0, 64);
        m_rendered.draw(sprite);

        sprite.setTexture(
            *m_textureManager.get(Snake2D::ETextureId::MenuLogo)
        );

        float x = (static_cast<float>(Snake2D::Window::width_px) -
                   static_cast<float>(Snake2D::g_logoSize_px.x)) / 2;

        sprite.setPosition(x, Snake2D::Menu::margin);

        m_rendered.draw(sprite);
        m_rendered.display();
    }

    void CMainMenuController::renderMenu(const std::size_t startItem_n)
    {
        float itemBackgroundX{ Snake2D::Menu::margin };

        float itemBackgroundY{ Snake2D::Menu::margin * 2
            + static_cast<float>(Snake2D::g_logoSize_px.y)
            + Snake2D::Menu::itemGap
        };

        std::size_t i = startItem_n;
        while (i < m_mainMenu.getSize())
        {
            sf::Sprite menuItemBackground(
                *m_textureManager.get(Snake2D::ETextureId::MenuItemBackground)
            );
            
            auto& item = m_mainMenu.getMenuItem(i);

            sf::Text menuItemText(
                item->getText(),
                *m_fontManager.get(Snake2D::EFontId::Consola), 56 
            );
            sf::FloatRect menuItemTextRect{
                menuItemText.getLocalBounds()
            };

            float itemTextX{ itemBackgroundX + 
                (Snake2D::g_menuItemSize_px.x - menuItemTextRect.width) / 2.0f
            };
            float itemTextY{ itemBackgroundY + 
                (Snake2D::g_menuItemSize_px.y - menuItemTextRect.height) / 2.0f - 16
            };

            if (i == m_selectedItem_n)
            {
                menuItemBackground.setColor(sf::Color(100, 100, 255, 100));
                menuItemText.setFillColor(sf::Color::Yellow);
            }
            else
            {
                menuItemText.setFillColor(sf::Color::Green);
            }
            
            menuItemBackground.setPosition(
                sf::Vector2f(itemBackgroundX, itemBackgroundY)
            );
            menuItemText.setPosition(
                sf::Vector2f(itemTextX, itemTextY)
            );

            m_rendered.draw(menuItemBackground);
            m_rendered.draw(menuItemText);

            itemBackgroundY += Menu::itemHeight + Menu::itemGap;
            ++i;
        }

        m_rendered.display();
    }
}