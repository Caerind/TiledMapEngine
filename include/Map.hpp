#ifndef TME_MAP_HPP
#define TME_MAP_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "Properties.hpp"


class Manager;

class Map : public sf::Transformable
{
    public:
        typedef std::shared_ptr<Map> Ptr;

    public:
        Map(Manager* manager);
        ~Map();

        bool loadFromFile(std::string const& filename);
        //bool saveToFile(std::string const& filename = "");

        void update(sf::Time dt);
        void render(unsigned int layer, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates());

        // Getters
        std::string getFilename() const;
        float getVersion() const;
        std::string getOrientation() const;
        sf::Vector2i getSize() const;
        sf::Vector2i getTileSize() const;
        TileLayer::Ptr getTileLayer(std::string const& name) const;
        ImageLayer::Ptr getImageLayer(std::string const& name) const;
        ObjectLayer::Ptr getObjectLayer(std::string const& name) const;
        Tileset::Ptr getTileset(std::string const& name) const;
        Properties& getProperties();

        // Setters
        void setFilename(std::string const& filename);
        void setVersion(float version);
        void setOrientation(std::string const& orientation);
        void setSize(sf::Vector2i size);
        void setTileSize(sf::Vector2i tileSize);
        void setTileLayer(TileLayer::Ptr layer);
        void setImageLayer(ImageLayer::Ptr layer);
        void setObjectLayer(Objectlayer::Ptr layer);
        void setProperties();
        void setProperty();

    private:
        Manager* mManager;

        std::string mFilename;

        float mVersion;
        std::string mOrientation;

        sf::Vector2i mSize;
        sf::Vector2i mTileSize;

        std::map<std::string,TileLayer::Ptr> mTileLayers;
        std::map<std::string,ImageLayer::Ptr> mImageLayers;
        std::map<std::string,ObjectLayer::Ptr> mObjectLayers;
        std::map<std::string,Tileset::Ptr> mTilesets;

        Properties mProperties;
};

#endif // TME_MAP_HPP
