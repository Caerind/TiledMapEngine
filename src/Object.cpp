#include "../include/Object.hpp"

////////////////////////////////////////////////////////////
Object::Object(Map* map) : mMap(map), mName(""), mType(Object::Rectangle), mX(0), mY(0), mWidth(0), mHeight(0), mRotation(0.f), mGid(0), mVisible(1), mPoints("")
{
}

////////////////////////////////////////////////////////////
std::string Object::getName() const
{
    return mName;
}

////////////////////////////////////////////////////////////
Object::Type Object::getType() const
{
    return mType;
}

////////////////////////////////////////////////////////////
int Object::getX() const
{
    return mX;
}

////////////////////////////////////////////////////////////
int Object::getY() const
{
    return mY;
}

////////////////////////////////////////////////////////////
int Object::getWidth() const
{
    return mWidth;
}

////////////////////////////////////////////////////////////
int Object::getHeight() const
{
    return mHeight;
}

////////////////////////////////////////////////////////////
float Object::getRotation() const
{
    return mRotation;
}

////////////////////////////////////////////////////////////
int Object::getGid() const
{
    return mGid;
}

////////////////////////////////////////////////////////////
bool Object::isVisible() const
{
    return mVisible;
}

////////////////////////////////////////////////////////////
std::string Object::getPoints() const
{
    std::ostringstream oss;
    for (int i = 0; i < static_cast<int>(mVertices.size()); i++)
    {
        oss << mVertices[i].position.x << "," << mVertices[i].position.y << " ";

        if (i == static_cast<int>(mVertices.size()) - 2 && (mType == Object::Polygon || mType == Object::Rectangle))
        {
            break;
        }
    }
    return oss.str();
}

////////////////////////////////////////////////////////////
sf::Vertex* Object::getVertex(int id)
{
    if (id >= 0 && id < static_cast<int>(mVertices.size()))
    {
        return &mVertices[id];
    }
    return nullptr;
}

////////////////////////////////////////////////////////////
void Object::setName(std::string const& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////
void Object::setType(Object::Type type)
{
    mType = type;

    if (mType == Object::Rectangle)
    {
        mVertices.push_back(sf::Vertex(sf::Vector2f(0, 0)));
        mVertices.push_back(sf::Vertex(sf::Vector2f(mWidth, 0)));
        mVertices.push_back(sf::Vertex(sf::Vector2f(mWidth, mHeight)));
        mVertices.push_back(sf::Vertex(sf::Vector2f(0, mHeight)));
        mVertices.push_back(sf::Vertex(sf::Vector2f(0, 0)));  // Close the rectangle
    }
    else if (mType == Object::Ellipse)
    {
        const float PI = 3.14159265358979f;
        float a = mWidth / 2.f;
        float b = mHeight / 2.f;
        float x, y;
        sf::Vector2f center = sf::Vector2f(a,b);
        float partitions = pow(2.f, 3.f + ceil((a + b) / 30));
        float angle_increment = 360.f / partitions;
        for (int i = 0; i * angle_increment <= 360.f; ++i)
        {
            x = center.x + a * cos((i * angle_increment) * PI / 180.f);
            y = center.y + b * sin((i * angle_increment) * PI / 180.f);
            mVertices.push_back(sf::Vertex(sf::Vector2f(x, y)));
        }
    }
    else if (mType == Object::Polygon || mType == Object::Polyline)
    {
        std::stringstream sstream(mPoints);
        float x_pos, y_pos;
        while (sstream >> x_pos)
        {
            if (sstream.peek() == ',')
                sstream.ignore();
            sstream >> y_pos;
            mVertices.push_back(sf::Vertex(sf::Vector2f(x_pos, y_pos)));
        }
        if (mType == Object::Polygon)
            mVertices.push_back(mVertices[0]);  // Close the polygon
    }
    else if (mType == Object::Tile)
    {

    }
}

////////////////////////////////////////////////////////////
void Object::setX(int x)
{
    mX = x;
    sf::Transformable::setPosition(mX,mY);
}

////////////////////////////////////////////////////////////
void Object::setY(int y)
{
    mY = y;
    sf::Transformable::setPosition(mX,mY);
}

////////////////////////////////////////////////////////////
void Object::setWidth(int width)
{
    mWidth = width;
}

////////////////////////////////////////////////////////////
void Object::setHeight(int height)
{
    mHeight = height;
}

////////////////////////////////////////////////////////////
void Object::setRotation(float rotation)
{
    mRotation = rotation;
    sf::Transformable::setRotation(rotation);
}

////////////////////////////////////////////////////////////
void Object::setGid(int gid)
{
    mGid = gid;
    setType(Object::Tile);
}

////////////////////////////////////////////////////////////
void Object::setVisible(bool visible)
{
    mVisible = visible;
}

////////////////////////////////////////////////////////////
void Object::setPoints(std::string const& points)
{
    mPoints = points;
}

////////////////////////////////////////////////////////////
void Object::setVertex(sf::Vertex vertex, int id)
{
    if (id >= 0 && id < static_cast<int>(mVertices.size()))
    {
        mVertices[id] = vertex;
    }
}

////////////////////////////////////////////////////////////
void Object::applyColor(sf::Color color)
{
    for (int i = 0; i < static_cast<int>(mVertices.size()); i++)
    {
        mVertices[i].color = color;
    }
}

////////////////////////////////////////////////////////////
void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mVisible)
    {
        states.transform *= getTransform();

        if (mGid != 0)
        {
            //states.texture = ...
        }

        target.draw(&mVertices[0], mVertices.size(), sf::LinesStrip, states);
    }
}

