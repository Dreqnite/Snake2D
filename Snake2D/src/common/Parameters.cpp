// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "Parameters.h"

namespace Snake2D
{
    EAction         g_currentAction{ Snake2D::EAction::LoadMenuScreen };
    bool            g_inGame{ false };
    std::string     g_baseDirPath{};
    std::string     g_imgDirPath{};
    std::string     g_fontsDirPath{};
    sf::Vector2f    g_logoSize_px{};
    sf::Vector2f    g_menuItemSize_px{};
    sf::Vector2f    g_scoreboardSize_px{};
}