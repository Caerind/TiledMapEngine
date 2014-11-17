#include "../include/ObjectGroup.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
ObjectGroup::ObjectGroup(Map* map) : mMap(map), mOpacity(1.f), mVisible(true)
{
}

////////////////////////////////////////////////////////////
void ObjectGroup::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mVisible)
    {
        states.transform *= getTransform();
        for (auto itr = mObjects.begin(); itr != mObjects.end(); itr++)
        {
            target.draw(*(itr->second),states);
        }
    }
}

////////////////////////////////////////////////////////////
std::string ObjectGroup::getName() const
{
    return mName;
}

////////////////////////////////////////////////////////////
std::string ObjectGroup::getColor() const
{
    return mColor;
}

////////////////////////////////////////////////////////////
float ObjectGroup::getOpacity() const
{
    return mOpacity;
}

////////////////////////////////////////////////////////////
bool ObjectGroup::isVisible() const
{
    return mVisible;
}

////////////////////////////////////////////////////////////
Object::Ptr ObjectGroup::getObject(std::string const& name)
{
    return (mObjects.find(name) != mObjects.end()) ? mObjects[name] : nullptr;
}

////////////////////////////////////////////////////////////
Object::Ptr ObjectGroup::getObject(int id)
{
    if (id >= static_cast<int>(mObjects.size()))
        return nullptr;
    int i = 0;
    for (auto itr = mObjects.begin(); itr != mObjects.end(); itr++)
    {
        if (id == i)
        {
            return itr->second;
        }
        i++;
    }
    return nullptr;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setName(std::string const& name)
{
    mName = name;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setColor(std::string const& color)
{
    mColor = color;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setOpacity(float opacity)
{
    mOpacity = opacity;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setVisible(bool visible)
{
    mVisible = visible;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setObject(Object::Ptr object)
{
    if (object != nullptr)
    {
        mObjects[object->getName()] = object;
    }
}

