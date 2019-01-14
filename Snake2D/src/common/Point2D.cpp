// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "Point2D.h"

#include "Parameters.h"

namespace Snake2D
{

CPoint2D::CPoint2D(const float x,
                   const float y)
    : sf::Vector2f(x, y)
{}

CPoint2D::~CPoint2D() {}

CPoint2D& CPoint2D::move(const EDirection direction) noexcept
{
    switch (direction)
    {
    case EDirection::Up:
        {
            this->y = (this->y == Snake2D::g_scoreboardSize_px.y)
                ? (Board::height_px + Snake2D::g_scoreboardSize_px.y - Board::cellSize_px)
                : (this->y - static_cast<float>(Board::cellSize_px));
        }
        break;
    case EDirection::Right:
        {
            this->x = (this->x == Board::width_px - Board::cellSize_px) 
                ? 0.0f 
                : (this->x + static_cast<float>(Board::cellSize_px));
        }
        break;
    case EDirection::Down:
        {
            this->y = (this->y == Board::height_px + 
                       Snake2D::g_scoreboardSize_px.y - Board::cellSize_px)
                ? Snake2D::g_scoreboardSize_px.y
                : (this->y + static_cast<float>(Board::cellSize_px));
        }
        break;
    case EDirection::Left:
        {
            this->x = (this->x == 0.0f) 
                ? (Board::width_px - Board::cellSize_px) 
                : (this->x - static_cast<float>(Board::cellSize_px));
        }
        break;
    }
    return *this;
}

}