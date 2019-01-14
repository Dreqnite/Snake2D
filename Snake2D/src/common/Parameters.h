// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef PARAMETERS_H
#define PARAMETERS_H

#define SNAKE2D_V_MAJOR                 1
#define SNAKE2D_V_MINOR                 0
#define SNAKE2D_V_PATCH                 0

#define SNAKE2D_IMG_FOLDER              "img\\"
#define SNAKE2D_FONTS_FOLDER            "fonts\\"

#define SNAKE2D_LOGO_FILE_NAME          "logo.png"
#define SNAKE2D_BACKGROUND_FILE_NAME    "background.png"
#define SNAKE2D_SNAKEBGD_FILE_NAME      "snake-background.png"
#define SNAKE2D_MENUITEM_FILE_NAME      "menu-item.png"
#define SNAKE2D_FOOD1_FILE_NAME         "food-1.png"
#define SNAKE2D_FOOD2_FILE_NAME         "food-2.png"
#define SNAKE2D_FOOD3_FILE_NAME         "food-3.png"
#define SNAKE2D_BOARDCELL_FILE_NAME     "cell.png"
#define SNAKE2D_SCOREBOARD_FILE_NAME    "scoreboard.png"
#define SNAKE2D_SNAKEBODYV_FILE_NAME    "snake-body-v.png"
#define SNAKE2D_SNAKEBODYTURN_FILE_NAME "snake-body-turn-left.png"
#define SNAKE2D_SNAKEHEAD_FILE_NAME     "snake-head-up.png"
#define SNAKE2D_SNAKETAIL_FILE_NAME     "snake-tail.png"

#include <atomic>

#include <SFML\Graphics.hpp>

namespace Snake2D
{
    enum class ETextureId
    {
        MenuBackground,
        MenuBackgroundSnake,
        MenuLogo,
        MenuItemBackground,
        SnakeBodyTurn,
        SnakeBodyV,
        SnakeHead,
        SnakeTail,
        Food1,
        Food2,
        Food3,
        Cell,
        Scoreboard
    };

    enum class EInterSprite
    {
        BackgroundLogo,
        Scoreboard,
        Board,
        Food
    };

    enum class EInterTexture
    {
        Background,
        Scoreboard
    };

    enum class EFontId
    {
        Consola
    };

    enum EDirection : int
    {
        None = 0,
        Up,
        Right,
        Down,
        Left
    };

    enum class EAction
    {
        ResumeGame,
        StartNewGame,
        LoadMenuScreen,
        LoadOptionsScreen,
        LoadAboutScreen,
        LoadEndGameScreen,
        ExitGame
    };

    enum class EMenuItem
    {
        ResumeGame,
        StartNewGame,
        Options,
        About,
        Exit
    };

    extern EAction      g_currentAction;
    extern bool         g_inGame;          
    extern std::string  g_baseDirPath;
    extern std::string  g_imgDirPath;
    extern std::string  g_fontsDirPath;
    extern sf::Vector2f g_logoSize_px;
    extern sf::Vector2f g_menuItemSize_px;
    extern sf::Vector2f g_scoreboardSize_px;

    namespace Window
    {
        constexpr int width_px{ 928 };
        constexpr int height_px{ 928 };
    }

    namespace Board
    {
        constexpr int cellSize_px{ 32 };
        constexpr int width_n{ Window::width_px / cellSize_px };
        constexpr int height_n{ 25 }; // 800 / 32 = 25
        constexpr int width_px{ width_n * cellSize_px };
        constexpr int height_px{ height_n * cellSize_px };
    }

    namespace Menu
    {
        // With margins from left/right sides
        constexpr int margin{ 64 };
        constexpr int itemWidth{ Window::width_px - 2 * margin };
        constexpr int itemHeight{ 64 };
        constexpr int itemGap{ 32 };
    }
}

#endif // !PARAMETERS_H
