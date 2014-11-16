#include "../include/Layer.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
Layer::Tile::Tile()
{
}

////////////////////////////////////////////////////////////
Layer::Layer(Map* map) : mMap(map), mLayer(sf::Quads), mOpacity(1.f), mVisible(true)
{
}

////////////////////////////////////////////////////////////
void Layer::update(sf::Time dt)
{
}

////////////////////////////////////////////////////////////
void Layer::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mVisible && mMap != nullptr)
    {
        states.transform *= getTransform();
        //states.texture = texture;
        target.draw(mLayer,states);
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
        mTiles[x][y] = tile;

        int idInLayer = (x + y * mWidth) * 4;
        Tileset::Ptr tileset = mMap->getTileset(tile.gid);

        if(idInLayer >= 0 && idInLayer < static_cast<int>(mLayer.getVertexCount()) && tileset != nullptr)
        {
            int tileWidth = tileset->getTileWidth();
            int tileHeight = tileset->getTileHeight();
            sf::IntRect tRect = tileset->getTextureRect(tile.gid);

            sf::Vertex* quad = &mLayer[idInLayer];
            quad[0].position = sf::Vector2f(x * mMap->getTileWidth(), y * mMap->getTileHeight());
            quad[1].position = sf::Vector2f(x * mMap->getTileWidth() + tileWidth, y * mMap->getTileHeight());
            quad[2].position = sf::Vector2f(x * mMap->getTileWidth() + tileWidth, y * mMap->getTileHeight() + tileHeight);
            quad[3].position = sf::Vector2f(x * mMap->getTileWidth(), y * mMap->getTileHeight() + tileHeight);

            quad[0].texCoords = sf::Vector2f(tRect.left, tRect.top);
            quad[1].texCoords = sf::Vector2f(tRect.left + tileWidth, tRect.top);
            quad[2].texCoords = sf::Vector2f(tRect.left + tileWidth, tRect.top + tileHeight);
            quad[3].texCoords = sf::Vector2f(tRect.left, tRect.top + tileHeight);
        }
    }
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

    mLayer.resize(mWidth * mHeight * 4);
}
