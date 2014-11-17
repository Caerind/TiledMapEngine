#include "../include/Tileset.hpp"

#include <iostream>

////////////////////////////////////////////////////////////
Tileset::TileOffset::TileOffset() : x(0), y(0)
{
}

////////////////////////////////////////////////////////////
Tileset::Tile::Tile()
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
Tileset::Tileset(Map* map) : mMap(map)
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
    if (id >= 0 && id < getTilesPerRow() * getTilesPerCol())
    {
        rect.left = mMargin + (id % getTilesPerRow() - 1) * (mTileWidth + mSpacing);
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
int Tileset::getTilesPerRow() const
{
    int width = getWidth() - (mMargin * 2);
    int count;
    if (mSpacing > 0)
    {
        while (width > mTileWidth)
        {
            width -= mTileWidth - mSpacing;
            count++;
        }
        return count;
    }
    else
    {
        count = width / mTileWidth;
        return count;
    }
}

////////////////////////////////////////////////////////////
int Tileset::getTilesPerCol() const
{
    int height = getHeight() - (mMargin * 2);
    if (mSpacing > 0)
    {
        int j;
        while (height > mTileHeight)
        {
            height -= mTileHeight - mSpacing;
            j++;
        }
        return j;
    }
    else
    {
        return height / mTileHeight;
    }
}
