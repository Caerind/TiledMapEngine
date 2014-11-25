#ifndef TME_TILE_HPP
#define TME_TILE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Tileset.hpp"

namespace tme
{

class Map;

class Tile: public sf::Drawable, public sf::Transformable
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

} // namespace tme

#endif // TME_TILE_HPP
