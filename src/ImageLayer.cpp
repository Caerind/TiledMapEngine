#include "../include/ImageLayer.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
ImageLayer::ImageLayer(Map* map) : Image(map), mOpacity(1.f), mVisible(true)
{
}

////////////////////////////////////////////////////////////
bool ImageLayer::loadFromFile(std::string const& filename)
{
    if (!load(filename))
    {
        return false;
    }

    update();

    return true;
}

////////////////////////////////////////////////////////////
void ImageLayer::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mVisible)
    {
        if (getTexture() != nullptr)
        {
            states.texture = getTexture().get();
        }
        target.draw(mVertices, 4, sf::Quads, states);
    }
}

////////////////////////////////////////////////////////////
std::string ImageLayer::getName() const
{
    return mName;
}

////////////////////////////////////////////////////////////
int ImageLayer::getX() const
{
    return mX;
}

////////////////////////////////////////////////////////////
int ImageLayer::getY() const
{
    return mY;
}

////////////////////////////////////////////////////////////
float ImageLayer::getOpacity() const
{
    return mOpacity;
}

////////////////////////////////////////////////////////////
bool ImageLayer::isVisible() const
{
    return mVisible;
}

////////////////////////////////////////////////////////////
void ImageLayer::setName(std::string const& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////
void ImageLayer::setX(int x)
{
    mX = x;
    update();
}

////////////////////////////////////////////////////////////
void ImageLayer::setY(int y)
{
    mY = y;
    update();
}

////////////////////////////////////////////////////////////
void ImageLayer::setOpacity(float opacity)
{
    mOpacity = opacity;
}

////////////////////////////////////////////////////////////
void ImageLayer::setVisible(bool visible)
{
    mVisible = visible;
}

////////////////////////////////////////////////////////////
void ImageLayer::update()
{
    mVertices[0].position = sf::Vector2f(mX, mY);
    mVertices[1].position = sf::Vector2f(mX+mWidth,mY);
    mVertices[2].position = sf::Vector2f(mX+mWidth,mY+mHeight);
    mVertices[3].position = sf::Vector2f(mX,mY+mHeight);

    mVertices[0].texCoords = sf::Vector2f(0,0);
    mVertices[1].texCoords = sf::Vector2f(mWidth,0);
    mVertices[2].texCoords = sf::Vector2f(mWidth,mHeight);
    mVertices[3].texCoords = sf::Vector2f(0,mHeight);
}
