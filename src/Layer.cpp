#include "../include/Layer.hpp"
#include "../include/Map.hpp"

#include <iostream>
#include <SFML/System/Sleep.hpp>

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
Layer::Layer(Map* map) : mMap(map), mOpacity(1.f), mVisible(true)
{
}

////////////////////////////////////////////////////////////
void Layer::update(sf::Time dt)
{
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
                target.draw(mTiles[i][j]);
            }
        }
    }
}

////////////////////////////////////////////////////////////
std::string Layer::getName() const
{
    return mName;
}

////////////////////////////////////////////////////////////
int Layer::getX() const
{
    return mX;
}

////////////////////////////////////////////////////////////
int Layer::getY() const
{
    return mY;
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
float Layer::getOpacity() const
{
    return mOpacity;
}

////////////////////////////////////////////////////////////
bool Layer::isVisible() const
{
    return mVisible;
}

////////////////////////////////////////////////////////////
Layer::Tile Layer::getTile(int x, int y) const
{
    return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) ? mTiles[x][y] : Tile();
}

////////////////////////////////////////////////////////////
int Layer::getTileId(int x, int y) const
{
    return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) ? mTiles[x][y].getId() : 0;
}

////////////////////////////////////////////////////////////
std::vector<std::vector<Layer::Tile>> Layer::getTiles() const
{
    return mTiles;
}

////////////////////////////////////////////////////////////
std::vector<std::vector<int>> Layer::getTilesIds() const
{
    unsigned int size = mTiles.size();
    unsigned int size2 = 0;
    if (size >= 1)
        size2 = mTiles[0].size();

    std::vector<std::vector<int>> ids;

    ids.resize(size);
    for (unsigned int i = 0; i < size; i++)
    {
        ids[i].resize(size2);
    }

    for (unsigned int j = 0; j < size; j++)
    {
        for (unsigned int i = 0; i < size2; i++)
        {
            ids[i][j] = mTiles[i][j].getId();
        }
    }

    return ids;
}

////////////////////////////////////////////////////////////
void Layer::setName(std::string const& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////
void Layer::setX(int x)
{
    mX = x;
    setPosition(static_cast<float>(x),getPosition().y);
}

////////////////////////////////////////////////////////////
void Layer::setY(int y)
{
    mY = y;
    setPosition(getPosition().x,static_cast<float>(y));
}

////////////////////////////////////////////////////////////
void Layer::setWidth(int width)
{
    mWidth = width;
    resize();
}

////////////////////////////////////////////////////////////
void Layer::setHeight(int height)
{
    mHeight = height;
    resize();
}

////////////////////////////////////////////////////////////
void Layer::setOpacity(float opacity)
{
    mOpacity = opacity;
}

////////////////////////////////////////////////////////////
void Layer::setVisible(bool visible)
{
    mVisible = visible;
}

////////////////////////////////////////////////////////////
void Layer::setTile(int x, int y, Tile tile)
{
    if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
    {
        if(tile.getTileset() != nullptr)
        {
            tile.setTilePos(x * mMap->getTileWidth(), y * mMap->getTileHeight(), tile.getTileset()->getTileWidth(), tile.getTileset()->getTileHeight());

            mTiles[x][y] = tile;
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
void Layer::setTiles(std::vector<std::vector<Layer::Tile>> const& tiles)
{
    // Update Tiles
}

////////////////////////////////////////////////////////////
void Layer::setTilesIds(std::vector<std::vector<int>> const& tiles)
{
    // Update tiles
}

////////////////////////////////////////////////////////////
void Layer::resize()
{
    while (mTiles.size() < static_cast<unsigned int>(mWidth))
    {
        mTiles.push_back(std::vector<Layer::Tile>(mHeight));
    }
    while (mTiles.size() > static_cast<unsigned int>(mWidth))
    {
        mTiles.pop_back();
    }
    for (unsigned int x = 0; x < static_cast<unsigned int>(mWidth); x++)
    {
        while (mTiles[x].size() < static_cast<unsigned int>(mHeight))
        {
            mTiles[x].push_back(Layer::Tile());
        }
        while (mTiles[x].size() > static_cast<unsigned int>(mHeight))
        {
            mTiles[x].pop_back();
        }
    }
}
