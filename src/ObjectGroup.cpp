#include "../include/ObjectGroup.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
ObjectGroup::ObjectGroup(Map* map) : mMap(map)
{
    mType = LayerType::ObjectGroup;
}

////////////////////////////////////////////////////////////
void ObjectGroup::render(sf::RenderTarget& target, sf::RenderStates states)
{
    if (mVisible)
    {
        states.transform *= getTransform();
        for (int i = 0; i < static_cast<int>(mObjects.size()); i++)
        {
            if (mObjects[i] != nullptr)
            {
                target.draw(*mObjects[i],states);
            }
        }
    }
}

////////////////////////////////////////////////////////////
std::string ObjectGroup::getColor() const
{
    return mColor;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setColor(std::string const& color)
{
    mColor = color;
}

////////////////////////////////////////////////////////////
int ObjectGroup::getObjectCount() const
{
    return static_cast<int>(mObjects.size());
}

////////////////////////////////////////////////////////////
Object::Ptr ObjectGroup::getObject(std::string const& name)
{
    for (int i = 0; i < static_cast<int>(mObjects.size()); i++)
    {
        if (mObjects[i]->getName() == name)
        {
            return mObjects[i];
        }
    }
    return nullptr;
}

////////////////////////////////////////////////////////////
Object::Ptr ObjectGroup::getObject(int id)
{
    if (id >= 0 && id < static_cast<int>(mObjects.size()))
    {
        return mObjects[id];
    }
    return nullptr;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setObject(Object::Ptr object)
{
    if (object != nullptr)
    {
        mObjects.push_back(object);
    }
}

