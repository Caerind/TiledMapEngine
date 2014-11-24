#ifndef TME_LAYER_HPP
#define TME_LAYER_HPP

#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Time.hpp>

#include "ILayer.hpp"
#include "Tileset.hpp"

class Map;

class Layer : public ILayer
{
    public:
        typedef std::shared_ptr<Layer> Ptr;
        typedef std::pair<int,int> Pos;

        class Tile : public sf::Drawable, public sf::Transformable
        {
            public:
                Tile();

                void load(Map* map, int id);
                void setTilePos(int x, int y, int width, int height);

                int getId() const;
                void setId(int id);

                Tileset::Ptr getTileset() const;
                void setTileset(Tileset::Ptr tileset);

                void setOpacity(float opacity);

            private:
                virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            private:
                int mId; // The global tile ID.

                sf::Vertex mVertices[4];
                Tileset::Ptr mTileset;
        };

        typedef std::map<Pos,Tile> TileMap;

    public:
        Layer(Map* map);

        void render(sf::RenderTarget& target, sf::RenderStates states);

        int getWidth() const;
        int getHeight() const;

        void setWidth(int width);
        void setHeight(int height);

        Tile getTile(int x, int y);
        int getTileId(int x, int y);
        TileMap getTiles() const;
        std::map<Pos,int> getTilesIds();

        void setTile(int x, int y, Tile tile);
        void setTileId(int x, int y, int id);
        void setTiles(TileMap const& tiles);
        void setTilesIds(std::map<Pos,int> const& tiles);

        void setOpacity(float opacity);

    private:
        Map* mMap;

        int mWidth; // The width of the layer in tiles. Traditionally required, but as of Tiled Qt always the same as the map width.
        int mHeight; // The height of the layer in tiles. Traditionally required, but as of Tiled Qt always the same as the map height.

        TileMap mTiles;
};

#endif // TME_LAYER_HPP
