// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "BoardModel.h"

#include "../common/Parameters.h"

namespace Snake2D
{
    CBoardModel::CBoardModel()
        : m_width_n{
              Snake2D::Window::width_px / Snake2D::Board::cellSize_px
          }
        , m_height_n{
              static_cast<int>(
                  (Snake2D::Window::height_px - Snake2D::g_scoreboardSize_px.y) 
                   / Snake2D::Board::cellSize_px
              )
          }
    {}

    CBoardModel::~CBoardModel()
    {}
}
