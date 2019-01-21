// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <list>

#include "../common/Point2D.h"

namespace Snake2D
{
    class CSnakeModel
    {
    public:
                                CSnakeModel();
                                ~CSnakeModel();

        void                    move();
        bool                    hasCollided(const CPoint2D& point) const noexcept;
        bool                    ateFood(const CPoint2D& foodLocation) const noexcept;

        Snake2D::EDirection     getDirection() const noexcept;
        Snake2D::CPoint2D       getHead() const noexcept;
        const std::list<Snake2D::CPoint2D>& 
                                getLocation() const noexcept;
        std::size_t             getSize() const noexcept;

        void                    popBack();
        void                    setDirection(const Snake2D::EDirection direction) noexcept;
        void                    setLocation(std::list<Snake2D::CPoint2D>&& location) noexcept;
    private:
        Snake2D::EDirection     m_direction;
        std::list<Snake2D::CPoint2D>
                                m_location;
    };
}

#endif // !SNAKEMODEL_H
