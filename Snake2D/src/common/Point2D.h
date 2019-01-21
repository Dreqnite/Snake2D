// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef POINT2D_H
#define POINT2D_H

#include "Parameters.h"

#include <SFML/System/Vector2.hpp>

namespace Snake2D
{

class CPoint2D : public sf::Vector2f
{
public:
                CPoint2D(const float x = 0.0f,
                         const float y = 0.0f);
                ~CPoint2D();
    CPoint2D&   move(const EDirection direction) noexcept;
};

}

#endif // !POINT2D_H
