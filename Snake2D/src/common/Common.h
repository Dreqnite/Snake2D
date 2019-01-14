// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef COMMON_H
#define COMMON_H

#include "SFML\Graphics.hpp"

#include "Parameters.h"
#include "Point2D.h"

namespace Snake2D
{
    sf::Sprite          flipVertically(const sf::Sprite& sprite);
    std::string         getExePath();
    std::string         getAppVersion();
    Snake2D::EDirection defineDirection(const Snake2D::CPoint2D& curr,
                                        const Snake2D::CPoint2D& next);
    float               calcRotationAngle(const Snake2D::ETextureId textureId,
                                          const Snake2D::EDirection prevDirection,
                                          const Snake2D::EDirection currDirection);
    float               getCenterTextH(const sf::Text& text);
    float               getCenterTextV(const sf::Text& text);
}

#endif // !COMMON_H