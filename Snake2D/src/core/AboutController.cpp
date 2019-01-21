// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "AboutController.h"

#include <array>

#include "../common/Common.h"

namespace Snake2D
{
    CAboutController::CAboutController()
        : CController(Snake2D::Window::width_px,
                      Snake2D::Window::height_px)
        , m_fontManager{}
    {
        m_textureManager.load(
            Snake2D::ETextureId::MenuBackground,
            Snake2D::g_imgDirPath + SNAKE2D_BACKGROUND_FILE_NAME,
            sf::IntRect()
        );
        m_fontManager.load(
            Snake2D::EFontId::Consola,
            Snake2D::g_fontsDirPath + "consola.ttf"
        );
        initializaAboutScreen();
    }

    CAboutController::~CAboutController()
    {}

    void CAboutController::initializaAboutScreen()
    {
        m_rendered.clear(sf::Color::Black);

        constexpr int linesAmount{ 3 };
        std::array<std::string, linesAmount> lines{
            std::string("Snake2D v") + Snake2D::getAppVersion(),
            "GitHub: Dreqnite/Snake2D",
            "License: AGPLv3"
        };

        sf::Sprite background{
            *m_textureManager.get(Snake2D::ETextureId::MenuBackground)
        };

        m_rendered.draw(background);

        int i{ 0 };
        constexpr unsigned fontSize{ 32 };
        while (i < linesAmount)
        {
            sf::Text mainText{
                lines[i], *m_fontManager.get(Snake2D::EFontId::Consola), fontSize
            };
            mainText.setFillColor(sf::Color::Yellow);

            sf::Vector2f pos{
                Snake2D::getCenterTextH(mainText),
                static_cast<float>(Snake2D::Window::height_px - linesAmount * fontSize)
                / 2 + 32.0f * i
            };
            mainText.setPosition(pos);

            m_rendered.draw(mainText);

            ++i;
        }

        sf::Text returnText{
            "Press <enter> to return",
            *m_fontManager.get(Snake2D::EFontId::Consola), fontSize
        };
        returnText.setFillColor(sf::Color::Yellow);

        sf::Vector2f pos{
            Snake2D::getCenterTextH(returnText),
            Snake2D::Window::height_px - returnText.getLocalBounds().height - 64
        };
        returnText.setPosition(pos);

        m_rendered.draw(returnText);
        m_rendered.display();
    }

    bool CAboutController::handleInput(const sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Return:
            {
                g_currentAction = Snake2D::EAction::LoadMenuScreen;
            }
            break;
        default:
            return false;
        }
        return true;
    }
}