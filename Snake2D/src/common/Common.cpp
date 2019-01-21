// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#include "Common.h"

#include <sstream>

#if defined(_WIN32)
#include <Windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <linux/limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#include "Version.h"

namespace Snake2D
{
#if defined(_WIN32)
    std::string getExePath()
    {
        char pathBuffer[MAX_PATH];

        HMODULE hModule{ GetModuleHandle(NULL) };
        if (hModule == NULL)
        {
            throw std::runtime_error("GetModuleHandle() returned NULL");
        }

        GetModuleFileName(hModule, pathBuffer, sizeof(pathBuffer));

        return pathBuffer;
    }
#elif defined(__linux__)
    std::string getExePath()
    {
        char pathBuffer[PATH_MAX];

        ssize_t bytes_n{
            readlink("/proc/self/exe", pathBuffer, PATH_MAX)
        };
        if (bytes_n == -1)
        {
            throw std::runtime_error("readlink() returned -1");
        }
        return pathBuffer;
    }
#elif defined(__APPLE__)
    std::string getExePath()
    {
        char pathBuffer[MAXPATHLEN];

        uint32_t bufsize = sizeof(pathBuffer);
        if (_NSGetExecutablePath(pathBuffer, &bufSize) != 0)
        {
            throw std::runtime_error("GetModuleHandle() returned NULL");
        }
        return pathBuffer;
    }
#endif

    std::string getAppVersion()
    {
        std::stringstream ss{};
        ss << SNAKE2D_VERSION_MAJOR << '.'
           << SNAKE2D_VERSION_MINOR << '.'
           << SNAKE2D_VERSION_PATCH;
        return ss.str();
    }

    // Solves flipping problem (tmp solution)
    // This issue was resolved in the new release of SFML
    sf::Sprite flipVertically(const sf::Sprite& sprite)
    {
        sf::Sprite flipped{ sprite };
        flipped.setTextureRect(sf::IntRect(0,
            Snake2D::Window::height_px,
            Snake2D::Window::width_px,
            -Snake2D::Window::height_px
        ));
        return flipped;
    }

    // curr - point, closer to the head
    // next - next point after curr (closer to the tail)
    Snake2D::EDirection defineDirection(const Snake2D::CPoint2D& curr,
                                        const Snake2D::CPoint2D& next)
    {
        int xDiff{ static_cast<int>(curr.x - next.x) };
        if (xDiff < 0) 
        {
            // Tail is on the right (body splitted) -> moving right
            // Tail is on the right -> moving left
            return (xDiff == -Snake2D::Board::width_px + Snake2D::Board::cellSize_px)
                ? Snake2D::EDirection::Right
                : Snake2D::EDirection::Left;             
        }
        else if (xDiff > 0)
        {
            // Tail is on the left (body splitted) -> moving left
            // Tail is on the left -> moving right
            return (xDiff == Snake2D::Board::width_px - Snake2D::Board::cellSize_px)
                ? Snake2D::EDirection::Left
                : Snake2D::EDirection::Right;
        }
        else
        {
            int yDiff{ static_cast<int>(curr.y - next.y) };
            if (yDiff < 0) 
            {
                // Tail is lower (body splitted) -> moving down
                // Tail is lower -> moving up
                return (yDiff == -Snake2D::Board::height_px + Snake2D::Board::cellSize_px)
                    ? Snake2D::EDirection::Down
                    : Snake2D::EDirection::Up;
            }
            else if (yDiff > 0)
            {
                // Tail is upper (body splitted) -> moving up
                // Tail is upper -> moving down
                return (yDiff == Snake2D::Board::height_px - Snake2D::Board::cellSize_px)
                    ? Snake2D::EDirection::Up
                    : Snake2D::EDirection::Down;
            }
        }
        return Snake2D::EDirection::None;
    }

    float calcRotationAngle(const Snake2D::ETextureId textureId,
                            const Snake2D::EDirection prevDirection,
                            const Snake2D::EDirection currDirection)
    {
        switch (textureId)
        {
        case Snake2D::ETextureId::SnakeBodyTurn:
            {
                if ((currDirection == EDirection::Right 
                     && prevDirection == EDirection::Down) ||
                    (currDirection == EDirection::Up 
                     && prevDirection == EDirection::Left))
                {
                    return 0.0f;
                }
                else if ((currDirection == EDirection::Left
                          && prevDirection == EDirection::Up) ||
                         (currDirection == EDirection::Down 
                          && prevDirection == EDirection::Right))
                {
                    return 180.0f;
                }
                else if ((currDirection == EDirection::Right
                          && prevDirection == EDirection::Up) ||
                         (currDirection == EDirection::Down
                          && prevDirection == EDirection::Left))
                {
                    return 90.0f;
                }
                else
                {
                    return -90.0f;
                }
            }
            break;
        case Snake2D::ETextureId::SnakeBodyV:
        case Snake2D::ETextureId::SnakeHead:
        case Snake2D::ETextureId::SnakeTail:
        default:
            switch (currDirection)
            {
            case Snake2D::EDirection::Right:
                return 90.0f;
            case Snake2D::EDirection::Down:
                return 180.0f;
            case Snake2D::EDirection::Left:
                return -90.0f;
            case Snake2D::EDirection::Up:
            default:
                return 0.0f;
            }
        }
    }

    float getCenterTextH(const sf::Text& text)
    {
        return (Snake2D::Window::width_px - text.getLocalBounds().width) / 2.0f;
    }

    float getCenterTextV(const sf::Text& text)
    {
        return (Snake2D::Window::height_px - text.getLocalBounds().height) / 2.0f;
    }
}