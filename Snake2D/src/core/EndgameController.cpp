// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "EndgameController.h"

#include <array>

#include "../common/Common.h"

namespace Snake2D
{
    CEndgameController::CEndgameController()
        : CController(Snake2D::Window::width_px,
                      Snake2D::Window::height_px)
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
    }

    CEndgameController::~CEndgameController()
    {}

    sf::Sprite CEndgameController::execute(void* args)
    {
        int score = *reinterpret_cast<int*>(args);

        m_rendered.clear(sf::Color::Black);

        sf::Sprite background{
            *m_textureManager.get(Snake2D::ETextureId::MenuBackground)
        };
        m_rendered.draw(background);

        constexpr int linesAmount{ 2 };
        std::array<std::string, linesAmount> lines{
            "Game Over!",
            "Score: " + std::to_string(score)
        };

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
            "Press <enter> or <escape> to return",
            *m_fontManager.get(Snake2D::EFontId::Consola), fontSize
        };
        returnText.setFillColor(sf::Color::Yellow);

        sf::Vector2f pos{
            (Snake2D::Window::width_px - returnText.getLocalBounds().width) / 2.0f,
            Snake2D::Window::height_px - returnText.getLocalBounds().height - 64
        };
        returnText.setPosition(pos);

        m_rendered.draw(returnText);
        m_rendered.display();

        return sf::Sprite(m_rendered.getTexture());
    }

    bool CEndgameController::handleInput(const sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Escape:
        case sf::Keyboard::Return:
            {
                Snake2D::g_inGame = false;
                Snake2D::g_currentAction = Snake2D::EAction::LoadMenuScreen;
            }
            break;
        default:
            return false;
        }
        return true;
    }
}
