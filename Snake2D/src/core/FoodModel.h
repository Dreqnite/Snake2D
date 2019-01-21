// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef FOODMODEL_H
#define FOODMODEL_H

#include "../common/Point2D.h"

namespace Snake2D
{
    class CFoodModel
    {
    public:
                                    CFoodModel();
                                    ~CFoodModel();
        Snake2D::CPoint2D           getLocation() const noexcept;
        void                        setLocation(Snake2D::CPoint2D&& location) noexcept;
    private:
        Snake2D::CPoint2D           m_location;
    };
}

#endif // !FOODMODEL_H

