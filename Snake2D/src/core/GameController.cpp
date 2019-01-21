#include "GameController.h"

#include <queue>

#include "../common/Random.h"
#include "../common/Common.h"

namespace Snake2D
{
    CGameController::CGameController()
        : CController(Snake2D::Window::width_px,
                      Snake2D::Window::height_px)
        , m_fontManager{}
        , m_interSprites{}
        , m_interTextures{}
        , m_boardModel{
              std::make_unique<Snake2D::CBoardModel>()
          }
        , m_foodModel{
              std::make_unique<Snake2D::CFoodModel>()
          }
        , m_snakeModel{
              std::make_unique<Snake2D::CSnakeModel>()
          }
        , m_scoreboardModel{
              std::make_unique<Snake2D::CScoreboardModel>()
          }
    {
        m_textureManager.load(
            Snake2D::ETextureId::Scoreboard,
            Snake2D::g_imgDirPath + SNAKE2D_SCOREBOARD_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::Food1,
            Snake2D::g_imgDirPath + SNAKE2D_FOOD1_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::Food2,
            Snake2D::g_imgDirPath + SNAKE2D_FOOD2_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::Food3,
            Snake2D::g_imgDirPath + SNAKE2D_FOOD3_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::SnakeBodyV,
            Snake2D::g_imgDirPath + SNAKE2D_SNAKEBODYV_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::SnakeBodyTurn,
            Snake2D::g_imgDirPath + SNAKE2D_SNAKEBODYTURN_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::SnakeHead,
            Snake2D::g_imgDirPath + SNAKE2D_SNAKEHEAD_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::SnakeTail,
            Snake2D::g_imgDirPath + SNAKE2D_SNAKETAIL_FILE_NAME,
            sf::IntRect()
        );
        m_textureManager.load(
            Snake2D::ETextureId::Cell,
            Snake2D::g_imgDirPath + SNAKE2D_BOARDCELL_FILE_NAME,
            sf::IntRect()
        );
        m_fontManager.load(
            Snake2D::EFontId::Consola,
            Snake2D::g_fontsDirPath + "consola.ttf"
        );
        initializeScoreboard();
        initializeBoard();
        initializeSnake();
    }

    CGameController::~CGameController()
    {}

    void CGameController::endGame()
    {
        if (!Snake2D::g_inGame) { return; }

        m_boardModel.reset(new Snake2D::CBoardModel());
        m_foodModel.reset(new Snake2D::CFoodModel());
        m_snakeModel.reset(new Snake2D::CSnakeModel());
        m_scoreboardModel.reset(new Snake2D::CScoreboardModel());
        initializeScoreboard();
        initializeBoard();
        initializeSnake();
        Snake2D::g_inGame = false;
    }

    sf::Sprite CGameController::execute(void* args)
    {
        m_rendered.clear(sf::Color::Black);

        if (Snake2D::g_inGame)
        {
            bool foodWasEaten{ 
                m_snakeModel->ateFood(m_foodModel->getLocation())
            };

            if (foodWasEaten)
            {
                m_scoreboardModel->upScore();
            }

            renderBoard();
            renderSnake(true, foodWasEaten);
            renderFood(foodWasEaten);
            renderScoreboard();
        }
        else // init
        {
            renderBoard();
            renderSnake(false, false);
            renderFood(true);
            renderScoreboard();
            Snake2D::g_inGame = true;
            Snake2D::g_currentAction = Snake2D::EAction::ResumeGame;
        }

        m_rendered.display();

        return sf::Sprite(m_rendered.getTexture());
    }

    bool CGameController::handleInput(const sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Up:
            {
                m_snakeModel->setDirection(EDirection::Up);
            }
            break;
        case sf::Keyboard::Right:
            {
                m_snakeModel->setDirection(EDirection::Right);
            }
            break;
        case sf::Keyboard::Down:
            {
                m_snakeModel->setDirection(EDirection::Down);
            }
            break;
        case sf::Keyboard::Left:
            {
                m_snakeModel->setDirection(EDirection::Left);
            }
            break;
        case sf::Keyboard::Escape:
            {
                Snake2D::g_currentAction = Snake2D::EAction::LoadMenuScreen;
            }
            break;
        default:
            return false;
        }
        return true;
    }

    void CGameController::initializeSnake()
    {
        Snake2D::EDirection direction{ Snake2D::generateRandomDirection() };
        
        m_snakeModel->setDirection(direction);

        std::list<Snake2D::CPoint2D> snakeLocation{};

        Snake2D::CPoint2D fragmentLocation;
        Snake2D::EDirection growthDirection{
            Snake2D::oppositeDirection(direction)
        };

        int size{ 3 };
        for (int i{ 0 }; i < size; ++i)
        {
            fragmentLocation = (snakeLocation.size() == 0)
                ? Snake2D::generateRandomPoint()
                : fragmentLocation.move(growthDirection);

            snakeLocation.push_back(fragmentLocation);
        }

        m_snakeModel->setLocation(std::move(snakeLocation));
    }

    void CGameController::initializeBoard()
    {
        sf::RenderTexture rt{};
        rt.create(
            Snake2D::Board::width_px,
            Snake2D::Board::height_px
        );

        sf::Sprite cellSprite{
            *m_textureManager.get(Snake2D::ETextureId::Cell)
        };
        cellSprite.setScale(0.5f, 0.5f);

        for (int x{ 0 }; x < m_boardModel->getWidth(); ++x)
        {
            for (int y{ 0 }; y < m_boardModel->getHeight(); ++y)
            {
                cellSprite.setPosition(
                    sf::Vector2f(
                        static_cast<float>(x * Snake2D::Board::cellSize_px),
                        static_cast<float>(y * Snake2D::Board::cellSize_px)
                    )
                );
                rt.draw(cellSprite);
            }
        }
        rt.display();

        m_interTextures[Snake2D::EInterTexture::Background] =
            rt.getTexture();

        m_interSprites[Snake2D::EInterSprite::Board] =
            sf::Sprite(m_interTextures.at(Snake2D::EInterTexture::Background));
    }

    void CGameController::initializeScoreboard()
    {
        sf::RenderTexture rt{};
        rt.create(
            static_cast<int>(Snake2D::g_scoreboardSize_px.x),
            static_cast<int>(Snake2D::g_scoreboardSize_px.y)
        );

        sf::Sprite scoreboardSprite{
            *m_textureManager.get(Snake2D::ETextureId::Scoreboard)
        };

        sf::Text text{
            "Score: ",
            *m_fontManager.get(Snake2D::EFontId::Consola), 32
        };
        text.setPosition(32, 32);
        
        rt.draw(scoreboardSprite);
        rt.draw(text);
        rt.display();

        m_interTextures[Snake2D::EInterTexture::Scoreboard] =
            rt.getTexture();

        m_interSprites[Snake2D::EInterSprite::Scoreboard] =
            sf::Sprite(m_interTextures.at(Snake2D::EInterTexture::Scoreboard));
    }

    void CGameController::renderSnake(const bool updateState,
                                      const bool foodWasEaten)
    {
        if (updateState)
        {
            m_snakeModel->move();

            // If food was eaten - there can not be any body part in that location
            // Hence, collision checking can be skipped
            if (!foodWasEaten)
            {
                // Moves snake's tail (no extension since food was not eaten)
                m_snakeModel->popBack();
                if (m_snakeModel->hasCollided(m_snakeModel->getHead()))
                {
                    Snake2D::g_currentAction = Snake2D::EAction::LoadEndGameScreen;
                }
            }
        }

        std::list<Snake2D::CPoint2D> snakeBody{ m_snakeModel->getLocation() };
        std::vector<Snake2D::EDirection> directions{};
        std::queue<Snake2D::CPoint2D> lastLocations{};
        for (const auto& fragment : snakeBody)
        {
            lastLocations.push(fragment);
            if (lastLocations.size() < 2) { continue; }

            Snake2D::CPoint2D currLocation{
                lastLocations.front()
            };  lastLocations.pop();

            directions.push_back(
                Snake2D::defineDirection(currLocation, lastLocations.front())
            );
        }
        directions.push_back(directions.at(directions.size() - 1));

        for (std::list<Snake2D::CPoint2D>::const_iterator it{ snakeBody.cbegin() };
             it != snakeBody.cend(); ++it)
        {
            std::ptrdiff_t i = std::distance(snakeBody.cbegin(), it);

            Snake2D::ETextureId textureId{};
            if (i == 0)
            {
                textureId = Snake2D::ETextureId::SnakeHead;
            }
            else if (i == snakeBody.size() - 1)
            {
                textureId = Snake2D::ETextureId::SnakeTail;
            }
            else
            {
                textureId = (directions.at(i - 1) == directions.at(i))
                    ? Snake2D::ETextureId::SnakeBodyV
                    : Snake2D::ETextureId::SnakeBodyTurn;
            }

            sf::Sprite sprite{ *m_textureManager.get(textureId) };
            sprite.setOrigin(32.0f, 32.0f);

            float angle{ calcRotationAngle(
                textureId, (i == 0) ? Snake2D::EDirection::None 
                : directions.at(i - 1), directions.at(i)
            ) };

            sprite.setScale(0.5f, 0.5f);
            sprite.rotate(angle);
            sprite.setPosition(it->x + 16, it->y + 16);
            m_rendered.draw(sprite);
        }
    }

    void CGameController::renderFood(const bool updateState)
    {
        if (updateState)
        {

            int randomFoodTexture_n{ 
                Snake2D::generateRandomInt(8, 10) 
            };
            sf::Sprite foodSprite{
                *m_textureManager.get(
                    static_cast<Snake2D::ETextureId>(randomFoodTexture_n)
                )
            };

            renewFoodLocation();

            foodSprite.setScale(0.5f, 0.5f);
            foodSprite.setPosition(m_foodModel->getLocation());

            m_interSprites[Snake2D::EInterSprite::Food] = foodSprite;

        }

        m_rendered.draw(
            m_interSprites.at(Snake2D::EInterSprite::Food)
        );
    }

    void CGameController::renderBoard()
    {
        sf::Sprite board{
            m_interSprites.at(Snake2D::EInterSprite::Board)
        };
        board.setPosition(0, Snake2D::g_scoreboardSize_px.y);
        m_rendered.draw(board);
    }

    void CGameController::renderScoreboard()
    {
        m_rendered.draw(
            m_interSprites.at(Snake2D::EInterSprite::Scoreboard)
        );

        sf::Text score{
            std::to_string(m_scoreboardModel->getScore()),
            *m_fontManager.get(Snake2D::EFontId::Consola), 32
        };
        score.setPosition(156, 32);

        m_rendered.draw(score);
    }

    void CGameController::renewFoodLocation()
    {
        if (m_snakeModel->getSize() < 3) { return; }

        std::vector<Snake2D::CPoint2D> invalidLocations{};
        while (true)
        {
            Snake2D::CPoint2D randomPoint{ Snake2D::generateRandomPoint() };

            // Avoids the same failed locations
            if (std::find(invalidLocations.cbegin(), invalidLocations.cend(),
                randomPoint) != invalidLocations.cend())
            {
                continue;
            }

            // Avoids overlapping with snake
            std::list<Snake2D::CPoint2D> snake{ m_snakeModel->getLocation() };

            auto it = std::find(snake.cbegin(), snake.cend(), randomPoint);
            if (it == snake.cend())
            {
                m_foodModel->setLocation(std::move(randomPoint));
                return;
            }
            else
            {
                invalidLocations.push_back(randomPoint);
            }
        }
    }
}