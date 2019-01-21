// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "Random.h"

namespace Snake2D
{
    CRandomGenerator& CRandomGenerator::getInstance() noexcept
    {
        static CRandomGenerator instance{};
        return instance;
    }

    CRandomGenerator::CRandomGenerator()
        : m_randomDeviceEngine{}
        , m_generator{ m_randomDeviceEngine() }
    {}

    int CRandomGenerator::getRandomInt(const int min,
                                             const int max) noexcept
    {
        std::uniform_int_distribution<int> uid{min, max};
        return uid(m_generator);
    }

    int generateRandomInt(const int min,
                          const int max) noexcept
    {
        CRandomGenerator& gen = CRandomGenerator::getInstance();
        return gen.getRandomInt(min, max);
    }

    Snake2D::CPoint2D generateRandomPoint()
    {
        CRandomGenerator& gen = CRandomGenerator::getInstance();

        int x = gen.getRandomInt(0, Snake2D::Board::width_n - 1)
            * Snake2D::Board::cellSize_px;
        int y = gen.getRandomInt(0, Snake2D::Board::height_n - 1)
            * Snake2D::Board::cellSize_px 
            + static_cast<int>(Snake2D::g_scoreboardSize_px.y);

        return { static_cast<float>(x), static_cast<float>(y) };
    }

    EDirection generateRandomDirection(const Snake2D::EDirection prevDirection)
    {
        Snake2D::EDirection direction = static_cast<Snake2D::EDirection>(
            CRandomGenerator::getInstance().getRandomInt(1, 4)
        );

        if (prevDirection == Snake2D::EDirection::None)
        {
            return direction;
        }

        // Turn180 is forbidden
        while ((prevDirection + direction) % 2 == 0)
        {
            direction = static_cast<Snake2D::EDirection>(
                CRandomGenerator::getInstance().getRandomInt(1, 4)
            );
        }

        return direction;
    }

    Snake2D::EDirection oppositeDirection(const Snake2D::EDirection direction)
    {
        switch (direction)
        {
        case Snake2D::EDirection::Up:
            return Snake2D::EDirection::Down;
        case Snake2D::EDirection::Right:
            return Snake2D::EDirection::Left;
        case Snake2D::EDirection::Down:
            return Snake2D::EDirection::Up;
        case Snake2D::EDirection::Left:
            return Snake2D::EDirection::Right;
        default:
            return Snake2D::EDirection::Up;
        }
    }

}