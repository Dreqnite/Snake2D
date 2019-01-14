// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef RECT2D_H
#define RECT2D_H

#include "Point2D.h"

namespace Snake2D
{
    class CRect2D
    {
    public:
                            
                            CRect2D(const CPoint2D& location,
                                    const int width,
                                    const int height);
                            ~CRect2D();
        inline CPoint2D     getLocation() const noexcept { return m_location; }
        inline sf::Vector2f getSize() const noexcept { return m_size; }
    private:
        CPoint2D            m_location;
        sf::Vector2f        m_size;
    };

}

#endif // !RECT2D_H
