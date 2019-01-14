// Copyright (c) 2018-2019 Andrei Krylov 
// Distributed under the GNU AGPLv3 software license, see the accompanying
// file LICENSE or https://choosealicense.com/licenses/agpl-3.0/.

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "SFML\Graphics.hpp"

#include "..\common\Parameters.h"

namespace Snake2D
{

    template <typename IdType, typename ResourceType>
    class CResourceManager
    {
    public:
        using ResourcePtr = std::unique_ptr<ResourceType>;

        CResourceManager()
            : m_resources{}
        {}

        ~CResourceManager()
        {}
        
        void load(const IdType id,
                  const sf::String& filePath)
        {
            ResourcePtr resource{ new ResourceType() };
            if (!resource->loadFromFile(filePath))
            {
                throw std::runtime_error(
                    "Error! file was not found:" + filePath
                );
            }
            m_resources.insert(std::make_pair(id, std::move(resource)));
        }

        template <typename Parameter> 
        void load(const IdType id,
                  const sf::String& filePath,
                  const Parameter& parameter)
        {
            ResourcePtr resource{ new ResourceType() };
            if (!resource->loadFromFile(filePath, parameter))
            {
                throw std::runtime_error(
                    "Error! file was not found:" + filePath
                );
            }
            m_resources.insert(std::make_pair(id, std::move(resource)));
        }

        const ResourcePtr& get(const IdType id) const
        {
            typename std::map<IdType, ResourcePtr>::const_iterator it =
                m_resources.find(id);
            if (it == m_resources.cend())
            {
                std::string errorMsg{
                    "Error: identifier \""
                    + std::to_string(static_cast<int>(id)) +
                    "\" was not found!"
                };
                throw std::runtime_error(errorMsg);
            }
            return it->second;
        }
    private:
        std::map<IdType, ResourcePtr> m_resources;
    };

    using TextureManager = Snake2D::CResourceManager<Snake2D::ETextureId, sf::Texture>;
    using FontManager = Snake2D::CResourceManager<Snake2D::EFontId, sf::Font>;
}

#endif // !RESOURCEMANAGER_H
