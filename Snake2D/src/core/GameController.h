#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller.h"
#include "BoardModel.h"
#include "FoodModel.h"
#include "SnakeModel.h"
#include "ScoreboardModel.h"

namespace Snake2D
{
    enum class EModel
    {
        FoodModel,
        SnakeModel,
        BoardModel,
        ScoreboardModel
    };

    class CGameController 
        : public Snake2D::CController
    {
    public:
                                    CGameController();
                                    ~CGameController();
        void                        endGame();
        inline int                  getScore() const noexcept { return m_scoreboardModel->getScore(); }
        sf::Sprite                  execute(void* args) override;
        bool                        handleInput(const sf::Keyboard::Key key) override;
    private:
        Snake2D::FontManager        m_fontManager;

        // Intermediate sprites which are rarely being redrawn
        std::map<EInterSprite, sf::Sprite>
                                    m_interSprites;
        std::map<EInterTexture, sf::Texture>
                                    m_interTextures;

        // Models
        std::unique_ptr<Snake2D::CBoardModel>
                                    m_boardModel;
        std::unique_ptr<Snake2D::CFoodModel>    
                                    m_foodModel;
        std::unique_ptr<Snake2D::CSnakeModel>   
                                    m_snakeModel;
        std::unique_ptr<Snake2D::CScoreboardModel>
                                    m_scoreboardModel;
    private:
        void                        initializeSnake();
        void                        initializeBoard();
        void                        initializeScoreboard();

        void                        renderFood(const bool updateState);
        void                        renderSnake(const bool updateState,
                                                const bool foodWasEaten);
        void                        renderBoard();
        void                        renderScoreboard();
        void                        renewFoodLocation();
    };
}

#endif // !GAMECONTROLLER_H
