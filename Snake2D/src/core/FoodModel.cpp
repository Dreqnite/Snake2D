// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "FoodModel.h"

namespace Snake2D
{
    CFoodModel::CFoodModel()
        : m_location{}
    {}

    CFoodModel::~CFoodModel() {}

    Snake2D::CPoint2D CFoodModel::getLocation() const noexcept
    {
        return m_location;
    }

    void CFoodModel::setLocation(Snake2D::CPoint2D&& location) noexcept
    {
        m_location = std::move(location);
    }
}