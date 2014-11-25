#include "../include/Layer.hpp"
#include "../include/Map.hpp"

namespace tme
{

////////////////////////////////////////////////////////////
Layer::Layer(Map* map) : mMap(map)
{
    mType = LayerType::Layer;
}

////////////////////////////////////////////////////////////
void Layer::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mVisible)
    {
        states.transform *= getTransform();
        for (int j = 0; j < mSize.y; j++)
            for (int i = 0; i < mSize.x; i++)
                target.draw(mTiles[Layer::Pos(i,j)]);
    }
}

////////////////////////////////////////////////////////////
int Layer::getTileId(int x, int y)
{
    return (x >= 0 && x < mSize.x && y >= 0 && y < mSize.y) ? mTiles[Layer::Pos(x,y)].getId() : 0;
}

////////////////////////////////////////////////////////////
void Layer::setTileId(int x, int y, int id)
{
    Tile tile;
    if (mMap != nullptr)
    {
        tile.load(mMap,id);
        if (x >= 0 && x < mSize.x && y >= 0 && y < mSize.y)
        {
            if(tile.getTileset() != nullptr && mMap != nullptr)
            {
                int mapTileWidth = mMap->getTileSize().x;
                int mapTileHeight = mMap->getTileSize().y;
                int width = tile.getTileset()->getTileSize().x;
                int height = tile.getTileset()->getTileSize().y;

                if (mMap->getOrientation() == "orthogonal")
                    tile.setTilePos(x * mapTileWidth, y * mapTileHeight, width, height);
                else if (mMap->getOrientation() == "isometric")
                    tile.setTilePos((x-y) * mapTileWidth * 0.5,(x+y) * mapTileHeight * 0.5,width,height);
                else if (mMap->getOrientation() == "staggered")
                {
                    int posX;
                    if ((y % 2) == 0)
                        posX = x * mapTileWidth;
                    else
                        posX = x * mapTileWidth + mapTileWidth / 2;
                    tile.setTilePos(posX,y * mapTileHeight / 2,width,height);
                }
                mTiles[Layer::Pos(x,y)] = tile;
            }
        }
    }
}

////////////////////////////////////////////////////////////
void Layer::setOpacity(float opacity)
{
    mOpacity = opacity;
    for (auto itr = mTiles.begin(); itr != mTiles.end(); itr++)
        itr->second.setOpacity(opacity);
}

} // namespace tme
