// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

#include "Parameters.h"
#include "Point2D.h"

namespace Snake2D
{

    class CRandomGenerator
    {
    public:
                                    
        static CRandomGenerator& getInstance() noexcept;
        int                      getRandomInt(const int min,
                                              const int max) noexcept;
    private:
        std::random_device       m_randomDeviceEngine;
        std::mt19937             m_generator;
    private:
                                 CRandomGenerator();
                                 ~CRandomGenerator() = default;

                                 CRandomGenerator(const CRandomGenerator&) = delete;
        CRandomGenerator&        operator=(const CRandomGenerator&) = delete;

                                 CRandomGenerator(CRandomGenerator&&) = delete;
        CRandomGenerator&        operator=(CRandomGenerator&&) = delete;
    };
    int                          generateRandomInt(const int min,
                                                   const int max) noexcept;
    Snake2D::CPoint2D            generateRandomPoint();
    Snake2D::EDirection          generateRandomDirection(const Snake2D::EDirection prevDirection =
                                                         Snake2D::EDirection::None);
    Snake2D::EDirection          oppositeDirection(const Snake2D::EDirection direction);
}

#endif // !RANDOM_H
