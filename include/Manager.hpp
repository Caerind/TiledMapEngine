#ifndef TME_MANAGER_HPP
#define TME_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Map.hpp"

class Manager : public sf::Transformable
{
    public:
        Manager();
        ~Manager();

        void render(int layer, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates());

        bool loadMap(std::string const& filename);
        Map::Ptr getMap(std::string const& filename);

        Image::Ptr getImage(std::string const& sourceName);
        void addImage(Image::Ptr img);

    private:
        std::map<std::string,Map::Ptr> mMaps;
        std::map<std::string,Image::Ptr> mImages; // Source/Image
};

#endif // TME_MANAGER_HPP
