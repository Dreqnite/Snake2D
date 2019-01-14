// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef SCOREBOARDMODEL_H
#define SCOREBOARDMODEL_H

namespace Snake2D
{
    class CScoreboardModel
    {
    public:
                                    CScoreboardModel();
                                    ~CScoreboardModel();
        inline const int            getScore() const noexcept { return m_score; }
        inline void                 upScore() noexcept { ++m_score; }
    private:
        int                         m_score;
    };
}

#endif // !SCOREBOARDMODEL_H