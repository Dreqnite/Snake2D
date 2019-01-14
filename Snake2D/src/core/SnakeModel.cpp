// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "SnakeModel.h"

namespace Snake2D
{
    CSnakeModel::CSnakeModel()
        : m_direction{}
        , m_location{}
    {}

    CSnakeModel::~CSnakeModel()
    {}

    Snake2D::EDirection CSnakeModel::getDirection() const noexcept
    {
        return m_direction;
    }

    Snake2D::CPoint2D CSnakeModel::getHead() const noexcept
    {
        return m_location.front();
    }

    const std::list<Snake2D::CPoint2D>& 
        CSnakeModel::getLocation() const noexcept
    {
        return m_location;
    }

    std::size_t CSnakeModel::getSize() const noexcept
    {
        return m_location.size();
    }

    void CSnakeModel::setDirection(const Snake2D::EDirection direction) noexcept
    {
        if (m_direction == direction) { return; }

        if (m_direction == Snake2D::EDirection::None
            || (m_direction + direction) % 2 != 0)
        {
            m_direction = direction;
        }
    }

    void CSnakeModel::setLocation(std::list<Snake2D::CPoint2D>&& location) noexcept
    {
        m_location = std::move(location);
    }

    void CSnakeModel::popBack()
    {
        if (m_location.size() > 0)
        {
            m_location.pop_back();
        }
    }

    bool CSnakeModel::hasCollided(const CPoint2D& point) const noexcept
    {
        std::list<CPoint2D>::const_iterator it{ m_location.cbegin() };
        ++it; // Skips head, because it can not collide with itself
        return std::find(it, m_location.cend(), point) != m_location.end();
    }

    void CSnakeModel::move()
    {
        CPoint2D head = getHead();
        CPoint2D nextHead = head.move(m_direction);
        m_location.push_front(std::move(nextHead));
    }

    bool CSnakeModel::ateFood(const CPoint2D& foodLocation) const noexcept
    {
        return foodLocation == getHead();
    }
}
