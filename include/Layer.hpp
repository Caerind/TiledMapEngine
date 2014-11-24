#ifndef TME_LAYER_HPP
#define TME_LAYER_HPP

#include <map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "ILayer.hpp"
#include "Tileset.hpp"
#include "Tile.hpp"

class Map;

namespace tme
{

class Layer : public ILayer
{
    public:
        typedef std::shared_ptr<Layer> Ptr;
        typedef std::pair<int,int> Pos;

    public:
        Layer(Map* map);

        void render(sf::RenderTarget& target, sf::RenderStates states);

        int getTileId(int x, int y);
        void setTileId(int x, int y, int id);

        void setOpacity(float opacity);

    private:
        Map* mMap;

        std::map<Pos,Tile> mTiles;
};

} // namespace tme

#endif // TME_LAYER_HPP
