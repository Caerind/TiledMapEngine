#include "../include/Layer.hpp"
#include "../include/Map.hpp"

#include <iostream>

////////////////////////////////////////////////////////////
Layer::Tile::Tile()
{
}

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
                if (mTiles[i][j].tileset != nullptr)
                {
                    if (mTiles[i][j].tileset->getTexture() != nullptr)
                    {
                        sf::RenderStates tStates = states;
                        tStates.texture = mTiles[i][j].tileset->getTexture().get();
                        target.draw(mTiles[i][j].vertices, 4, sf::Quads, tStates);
                    }
                }
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
    return (x >= 0 && x < mWidth && y >= 0 && y < mHeight) ? mTiles[x][y].gid : 0;
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
            ids[i][j] = mTiles[i][j].gid;
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
    if (x >= 0 && x < mWidth && y >= 0 && y < mHeight && mMap != nullptr)
    {
        tile.tileset = mMap->getTileset(tile.gid);

        if(tile.tileset != nullptr)
        {
            int tileWidth = tile.tileset->getTileWidth();
            int tileHeight = tile.tileset->getTileHeight();
            sf::IntRect tRect = tile.tileset->getTextureRect(tile.gid);

            tile.vertices[0].position = sf::Vector2f(x * mMap->getTileWidth(), y * mMap->getTileHeight());
            tile.vertices[1].position = sf::Vector2f(x * mMap->getTileWidth() + tileWidth, y * mMap->getTileHeight());
            tile.vertices[2].position = sf::Vector2f(x * mMap->getTileWidth() + tileWidth, y * mMap->getTileHeight() + tileHeight);
            tile.vertices[3].position = sf::Vector2f(x * mMap->getTileWidth(), y * mMap->getTileHeight() + tileHeight);

            tile.vertices[0].texCoords = sf::Vector2f(tRect.left, tRect.top);
            tile.vertices[1].texCoords = sf::Vector2f(tRect.left + tileWidth, tRect.top);
            tile.vertices[2].texCoords = sf::Vector2f(tRect.left + tileWidth, tRect.top + tileHeight);
            tile.vertices[3].texCoords = sf::Vector2f(tRect.left, tRect.top + tileHeight);
        }
    }
}

////////////////////////////////////////////////////////////
void Layer::setTileId(int x, int y, int id)
{
    Tile tile;
    tile.gid = id;
    setTile(x,y,tile);
}

////////////////////////////////////////////////////////////
void Layer::setTiles(std::vector<std::vector<Layer::Tile>> const& tiles)
{
    mTiles = tiles;
    // Update tiles
}

////////////////////////////////////////////////////////////
void Layer::setTilesIds(std::vector<std::vector<int>> const& tiles)
{
    unsigned int size = tiles.size();
    unsigned int size2 = 0;
    if (size >= 1)
        size2 = tiles[0].size();

    mTiles.resize(size);
    for (unsigned int i = 0; i < size; i++)
    {
        mTiles[i].resize(size2);
    }

    for (unsigned int j = 0; j < size; j++)
    {
        for (unsigned int i = 0; i < size2; i++)
        {
            Tile t;
            t.gid = tiles[i][j];
            mTiles[i][j] = t;
        }
    }
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
