// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include <SFML\Graphics.hpp>

#include "core\GameManager.h"
#include "common\Parameters.h"
#include "common\Common.h"
#include "common\Point2D.h"
#include "common\Random.h"

sf::Vector2u getImgSize(const std::string imgName)
{
    sf::Image image{};
    image.loadFromFile(Snake2D::g_imgDirPath + imgName);

    return image.getSize();
}

template <typename T>
sf::Vector2<T> getImgSize(const std::string imgName)
{
    sf::Image image{};
    image.loadFromFile(Snake2D::g_imgDirPath + imgName);

    auto size = image.getSize();
    return { static_cast<T>(size.x), 
             static_cast<T>(size.y) };
}

void init()
{
    std::string exePath{ Snake2D::getExePath() };
#if defined(_DEBUG)
    std::size_t basePos{ exePath.find("bin") };
    std::string basePath{ exePath.substr(0, basePos) };
    Snake2D::g_imgDirPath = basePath + SNAKE2D_IMG_FOLDER;
    Snake2D::g_fontsDirPath = basePath + SNAKE2D_FONTS_FOLDER;
#else
    Snake2D::g_imgDirPath = exePath + SNAKE2D_IMG_FOLDER;
    Snake2D::g_fontsDirPath = exePath + SNAKE2D_FONTS_FOLDER;
#endif
    Snake2D::g_logoSize_px = getImgSize<float>(SNAKE2D_LOGO_FILE_NAME);
    Snake2D::g_menuItemSize_px = getImgSize<float>(SNAKE2D_MENUITEM_FILE_NAME);
    Snake2D::g_scoreboardSize_px = getImgSize<float>(SNAKE2D_SCOREBOARD_FILE_NAME);
}

int main()
{
    init();

    Snake2D::CGameManager manager{};
    manager.run();

    return 0;
}
