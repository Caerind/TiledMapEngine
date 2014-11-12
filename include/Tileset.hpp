#ifndef TME_TILESET_HPP
#define TME_TILESET_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Map;

class Tileset
{
    public:
        typedef std::shared_ptr<Tileset> Ptr;

        struct TileOffset
        {


        };

        struct Tile
        {
            Tile();



            Properties mProperties;
        };

        struct TerrainTypes
        {

        };

        struct Terrain
        {

        };

    public:
        Tileset(Map* map);

        // Getters
        int getFirstGid() const;
        std::string getName() const;
        sf::Vector2i getTileSize() const;
        int getSpacing() const;
        int getMargin() const;
        std::string getSource() const;
        std::shared_ptr<sf::Texture> getTexture() const;
        sf::Vector2i getTextureSize() const;

        // Setters
        void setFirstGid(int first);
        void setName(std::string const& name);
        void setTileSize(sf::Vector2i tileSize);
        void setSpacing(int spacing);
        void setMargin(int margin);
        void setSource(std::string const& source);
        void setTexture(std::shared_ptr<sf::Texture> texture);
        void setTextureSize(sf::Vector2i textureSize);

    private:
        Map* mMap;

        // Tileset Part
        int mFirstGid;
        std::string mName;
        sf::Vector2i mTileSize;
        int mSpacing;
        int mMargin;

        // Image Part
        std::string mSource;
        std::shared_ptr<sf::Texture> mTexture;
        sf::Vector2i mTextureSize;
};

#endif // TME_TILESET_HPP
