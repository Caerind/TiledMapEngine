#ifndef TME_LAYER_HPP
#define TME_LAYER_HPP

#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Time.hpp>

#include "Properties.hpp"
#include "Tileset.hpp"

class Map;

class Layer : public Properties, public sf::Transformable
{
    public:
        typedef std::shared_ptr<Layer> Ptr;

        struct Tile
        {
            Tile();

            int gid; // The global tile ID.
        };

    public:
        Layer(Map* map);

        void update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

        std::string getName() const;
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        float getOpacity() const;
        bool isVisible() const;
        Tile getTile(int x, int y) const;

        std::vector<std::vector<Tile>> getTiles() const;
        std::vector<std::vector<int>> getTilesIds() const;

        void setName(std::string const& name);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setOpacity(float opacity);
        void setVisible(bool visible);
        void setTile(int x, int y, Tile tile);

        void setTiles(std::vector<std::vector<Tile>> const& tiles);
        void setTilesIds(std::vector<std::vector<int>> const& tiles);

    private:
        void resize();

    private:
        Map* mMap;

        Tileset::Ptr mTileset;

        std::vector<std::vector<Tile>> mTiles;
        sf::VertexArray mLayer;

        std::string mName; // The name of the layer.
        int mX; // The x coordinate of the layer in tiles. Defaults to 0 and can no longer be changed in Tiled Qt.
        int mY; // The y coordinate of the layer in tiles. Defaults to 0 and can no longer be changed in Tiled Qt.
        int mWidth; // The width of the layer in tiles. Traditionally required, but as of Tiled Qt always the same as the map width.
        int mHeight; // The height of the layer in tiles. Traditionally required, but as of Tiled Qt always the same as the map height.
        float mOpacity; // The opacity of the layer as a value from 0 to 1. Defaults to 1.
        bool mVisible; // Whether the layer is shown (1) or hidden (0). Defaults to 1.
};

#endif // TME_LAYER_HPP
