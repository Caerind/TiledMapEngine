#include "../include/Tileset.hpp"

////////////////////////////////////////////////////////////
Tileset::TileOffset::TileOffset() : x(0), y(0)
{
}

////////////////////////////////////////////////////////////
Tileset::Tile::Tile() : mId(0), mTerrain(""), mProbability(0.0f)
{
}

////////////////////////////////////////////////////////////
int Tileset::Tile::getId() const
{
    return mId;
}

////////////////////////////////////////////////////////////
std::string Tileset::Tile::getTerrain() const
{
    return mTerrain;
}

////////////////////////////////////////////////////////////
float Tileset::Tile::getProbability() const
{
    return mProbability;
}

////////////////////////////////////////////////////////////
void Tileset::Tile::setId(int id)
{
    mId = id;
}

////////////////////////////////////////////////////////////
void Tileset::Tile::setTerrain(std::string const& terrain)
{
    mTerrain = terrain;
}

////////////////////////////////////////////////////////////
void Tileset::Tile::setProbability(float probability)
{
    mProbability = probability;
}

////////////////////////////////////////////////////////////
Tileset::Tileset(Map* map) : Image(map)
{
}

////////////////////////////////////////////////////////////
int Tileset::getFirstGid() const
{
    return mFirstGid;
}

////////////////////////////////////////////////////////////
std::string Tileset::getName() const
{
    return mName;
}

////////////////////////////////////////////////////////////
int Tileset::getTileWidth() const
{
    return mTileWidth;
}

////////////////////////////////////////////////////////////
int Tileset::getTileHeight() const
{
    return mTileHeight;
}

////////////////////////////////////////////////////////////
int Tileset::getSpacing() const
{
    return mSpacing;
}

////////////////////////////////////////////////////////////
int Tileset::getMargin() const
{
    return mMargin;
}

////////////////////////////////////////////////////////////
Tileset::TileOffset& Tileset::getTileOffset()
{
    return mTileOffset;
}

////////////////////////////////////////////////////////////
Tileset::Tile Tileset::getTile(int id)
{
    return mTiles[id];
}

////////////////////////////////////////////////////////////
int Tileset::getLastGid() const
{
    return mFirstGid + getTilesPerRow() * getTilesPerCol() - 1;
}

////////////////////////////////////////////////////////////
sf::IntRect Tileset::getTextureRect(int id) const
{
    sf::IntRect rect(0,0,mTileWidth,mTileHeight);
    id -= mFirstGid;
    if (id >= 0 && id < getTilesPerRow() * getTilesPerCol())
    {
        rect.left = mMargin + (id % getTilesPerRow()) * (mTileWidth + mSpacing);
        rect.top = mMargin + (id / getTilesPerRow()) * (mTileHeight + mSpacing);
    }
    return rect;
}

////////////////////////////////////////////////////////////
void Tileset::setFirstGid(int first)
{
    mFirstGid = first;
}

////////////////////////////////////////////////////////////
void Tileset::setName(std::string const& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////
void Tileset::setTileWidth(int width)
{
    mTileWidth = width;
}

////////////////////////////////////////////////////////////
void Tileset::setTileHeight(int height)
{
    mTileHeight = height;
}

////////////////////////////////////////////////////////////
void Tileset::setSpacing(int spacing)
{
    mSpacing = spacing;
}

////////////////////////////////////////////////////////////
void Tileset::setMargin(int margin)
{
    mMargin = margin;
}

////////////////////////////////////////////////////////////
void Tileset::setTileOffset(TileOffset offset)
{
    mTileOffset = offset;
}

////////////////////////////////////////////////////////////
void Tileset::addTile(Tileset::Tile::Ptr tile)
{
    if (tile != nullptr)
    {
        mTiles[tile->getId()] = *(tile.get());
    }
}

////////////////////////////////////////////////////////////
Tileset::Tile Tileset::getTileInContainer(int id) const
{
    if (id < 0 || id >= getTileCount())
    {
        return Tile();
    }
    int i = 0;
    for (auto itr = mTiles.begin(); itr != mTiles.end(); itr++)
    {
        if (i == id)
        {
            return itr->second;
        }
        i++;
    }
    return Tile();
}

////////////////////////////////////////////////////////////
int Tileset::getTileCount() const
{
    return static_cast<int>(mTiles.size());
}

////////////////////////////////////////////////////////////
int Tileset::getTilesPerRow() const
{
    int width = getWidth() - (mMargin * 2);
    int fWidth = 0;
    if (mSpacing != 0)
    {
        for (int i = 0; i <= width;)
        {
            i += mTileWidth + mSpacing;
            fWidth += mTileWidth;
        }
    }
    else
    {
        fWidth = width;
    }
    return (fWidth / mTileWidth);
}

////////////////////////////////////////////////////////////
int Tileset::getTilesPerCol() const
{
    int height = getHeight() - (mMargin * 2);
    int fHeight = 0;
    if (mSpacing != 0)
    {
        for (int i = 0; i <= height;)
        {
            i += mTileHeight + mSpacing;
            fHeight += mTileHeight;
        }
    }
    else
    {
        fHeight = height;
    }
    return (fHeight / mTileHeight);
}
