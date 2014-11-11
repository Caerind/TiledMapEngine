#ifndef TME_MANAGER_HPP
#define TME_MANAGER_HPP

#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

class Manager
{
    public:
        Manager();
        ~Manager();

        bool loadMap(std::string const& filename);
        void addMap(Map::Ptr map);
        Map::Ptr getMap(std::string const& filename);

        bool loadTexture(std::string const& filename);
        void addTexture(std::shared_ptr<sf::Texture> texture, std::string const& filename);
        std::shared_ptr<sf::Texture> getTexture(std::string const& filename);

    private:
        std::map<std::string,Map::Ptr> mMaps;
        std::map<std::string,std::shared_ptr<sf::Texture>> mTextures;
};

#endif // TME_MANAGER_HPP
