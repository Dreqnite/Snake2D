// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef MAINMENUITEM_H
#define MAINMENUITEM_H

#include <SFML\Graphics.hpp>

#include "..\common\Parameters.h"

namespace Snake2D
{
    class CMainMenuItemModel
    {
    public:
                            
                                    CMainMenuItemModel(const Snake2D::EMenuItem type,
                                                       const sf::String& text,
                                                       const Snake2D::EAction scene);
                                    ~CMainMenuItemModel();
        inline Snake2D::EMenuItem   getType() const noexcept 
        { 
            return m_type;
        }
        inline sf::String           getText() const noexcept 
        { 
            return m_text; 
        }
        inline Snake2D::EAction     getAction() const noexcept 
        { 
            return m_action; 
        }
    private:
        Snake2D::EMenuItem  m_type;
        sf::String          m_text;
        Snake2D::EAction    m_action;
    };
}

#endif // !MAINMENUITEM_H

