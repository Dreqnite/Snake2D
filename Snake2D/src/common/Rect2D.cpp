// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "Rect2D.h"

namespace Snake2D
{
    CRect2D::CRect2D(const CPoint2D& location,
                     const int width,
                     const int height)
        : m_location{ location }
        , m_size{
            static_cast<float>(width),
            static_cast<float>(height)
        }
    {}

    CRect2D::~CRect2D() {}
}