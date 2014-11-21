#include "../include/ImageLayer.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
ImageLayer::ImageLayer(Map* map) : Image(map)
{
    mType = LayerType::ImageLayer;
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
        states.transform *= getTransform();
        if (getTexture() != nullptr)
        {
            states.texture = getTexture().get();
        }
        target.draw(mVertices, 4, sf::Quads, states);
    }
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
void ImageLayer::update()
{
    mVertices[0].position = sf::Vector2f(0, 0);
    mVertices[1].position = sf::Vector2f(mWidth,0);
    mVertices[2].position = sf::Vector2f(mWidth,mHeight);
    mVertices[3].position = sf::Vector2f(0,mHeight);

    mVertices[0].texCoords = sf::Vector2f(0,0);
    mVertices[1].texCoords = sf::Vector2f(mWidth,0);
    mVertices[2].texCoords = sf::Vector2f(mWidth,mHeight);
    mVertices[3].texCoords = sf::Vector2f(0,mHeight);

    setPosition(mX,mY);
}
