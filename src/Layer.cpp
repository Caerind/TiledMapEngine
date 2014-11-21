#include "../include/Layer.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
// LAYER::TILE                                            //
////////////////////////////////////////////////////////////
Layer::Tile::Tile() : mId(0), mTileset(nullptr)
{
}

////////////////////////////////////////////////////////////
void Layer::Tile::load(Map* map, int id)
{
    setId(id);
    mTileset = map->getTileset(mId);
    if (mTileset != nullptr)
    {
        setPosition(mTileset->getTileOffset().x, mTileset->getTileOffset().y);

        sf::IntRect tRect = mTileset->getTextureRect(mId);

        mVertices[0].texCoords = sf::Vector2f(tRect.left, tRect.top);
        mVertices[1].texCoords = sf::Vector2f(tRect.left + mTileset->getTileWidth(), tRect.top);
        mVertices[2].texCoords = sf::Vector2f(tRect.left + mTileset->getTileWidth(), tRect.top + mTileset->getTileHeight());
        mVertices[3].texCoords = sf::Vector2f(tRect.left, tRect.top + mTileset->getTileHeight());
    }
}

////////////////////////////////////////////////////////////
void Layer::Tile::setTilePos(int x, int y, int width, int height)
{
    mVertices[0].position = sf::Vector2f(x, y);
    mVertices[1].position = sf::Vector2f(x + width, y);
    mVertices[2].position = sf::Vector2f(x + width, y + height);
    mVertices[3].position = sf::Vector2f(x, y + height);
}

////////////////////////////////////////////////////////////
int Layer::Tile::getId() const
{
    return mId;
}

////////////////////////////////////////////////////////////
void Layer::Tile::setId(int id)
{
    mId = id;
}

////////////////////////////////////////////////////////////
Tileset::Ptr Layer::Tile::getTileset() const
{
    return mTileset;
}

////////////////////////////////////////////////////////////
void Layer::Tile::setTileset(Tileset::Ptr tileset)
{
    mTileset = tileset;
}

////////////////////////////////////////////////////////////
void Layer::Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mTileset != nullptr)
    {
        states.transform *= getTransform();
        if (mTileset->getTexture() != nullptr)
        {
            states.texture = mTileset->getTexture().get();
        }
        target.draw(mVertices, 4, sf::Quads, states);
    }
}

////////////////////////////////////////////////////////////
// LAYER                                           //
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
        for (int j = 0; j < mHeight; j++)
        {
            for (int i = 0; i < mWidth; i++)
            {
                target.draw(mTiles[Layer::Pos(i,j)]);
            }
        }
    }
}

////////////////////////////////////////////////////////////
int Layer::getWidth() const
{
    return mWidth;
}

////////////////////////////////////////////////////////////
int Layer::getHeight() const
{
    return mHeight;
}

////////////////////////////////////////////////////////////
void Layer::setWidth(int width)
{
    mWidth = width;
}

////////////////////////////////////////////////////////////
void Layer::setHeight(int height)
{
    mHeight = height;
}

////////////////////////////////////////////////////////////
Layer::Tile Layer::getTile(int x, int y)
{
    return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) ? mTiles[Layer::Pos(x,y)] : Tile();
}

////////////////////////////////////////////////////////////
int Layer::getTileId(int x, int y)
{
    return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) ? mTiles[Layer::Pos(x,y)].getId() : 0;
}

////////////////////////////////////////////////////////////
Layer::TileMap Layer::getTiles() const
{
    return mTiles;
}

////////////////////////////////////////////////////////////
std::map<Layer::Pos,int> Layer::getTilesIds()
{
    std::map<Layer::Pos,int> map;
    for (int i = 0; i < mWidth; i++)
    {
        for (int j = 0; j < mHeight; j++)
        {
            map[Layer::Pos(i,j)] = mTiles[Layer::Pos(i,j)].getId();
        }
    }
    return map;
}

////////////////////////////////////////////////////////////
void Layer::setTile(int x, int y, Tile tile)
{
    if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
    {
        if(tile.getTileset() != nullptr && mMap != nullptr)
        {
            int mapTileWidth = mMap->getTileWidth();
            int mapTileHeight = mMap->getTileHeight();
            int width = tile.getTileset()->getTileWidth();
            int height = tile.getTileset()->getTileHeight();

            if (mMap->getOrientation() == "orthogonal")
            {
                tile.setTilePos(x * mapTileWidth, y * mapTileHeight, width, height);
            }
            else if (mMap->getOrientation() == "isometric")
            {
                tile.setTilePos((x-y) * mapTileWidth * 0.5,(x+y) * mapTileHeight * 0.5,width,height);
            }
            else if (mMap->getOrientation() == "staggered")
            {
                int posX;
                if ((y % 2) == 0)
                {
                    posX = x * mapTileWidth;
                }
                else
                {
                    posX = x * mapTileWidth + mapTileWidth /2;
                }
                tile.setTilePos(posX,y * mapTileHeight / 2,width,height);
            }

            mTiles[Layer::Pos(x,y)] = tile;
        }
    }
}

////////////////////////////////////////////////////////////
void Layer::setTileId(int x, int y, int id)
{
    Tile tile;
    if (mMap != nullptr)
    {
        tile.load(mMap,id);
        setTile(x,y,tile);
    }
}

////////////////////////////////////////////////////////////
void Layer::setTiles(Layer::TileMap const& tiles)
{
    mTiles = tiles;
    // Update tiles
}

////////////////////////////////////////////////////////////
void Layer::setTilesIds(std::map<Layer::Pos,int> const& tiles)
{
    // Update tiles
}
