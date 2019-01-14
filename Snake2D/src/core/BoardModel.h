// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef BOARDMODEL_H
#define BOARDMODEL_H

namespace Snake2D
{
    class CBoardModel
    {
    public:
                            CBoardModel();
                            ~CBoardModel();
        inline int          getWidth() const noexcept { return m_width_n; }
        inline int          getHeight() const noexcept { return m_height_n; }
    private:
        int                 m_width_n;
        int                 m_height_n;
    };
}

#endif // !BOARDMODEL_H
