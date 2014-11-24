#include "../include/ObjectGroup.hpp"
#include "../include/Map.hpp"

namespace tme
{

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
            target.draw(*mObjects[i],states);
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

    sf::Color sfColor(Image::getColor(mColor));
    sfColor.a = 255.f * mOpacity;
    for (auto itr = mObjects.begin(); itr != mObjects.end(); itr++)
    {
        (*itr)->applyColor(sfColor);
    }
}

////////////////////////////////////////////////////////////
void ObjectGroup::setOpacity(float opacity)
{
    mOpacity = opacity;
    setColor(mColor);
}

////////////////////////////////////////////////////////////
int ObjectGroup::getObjectCount() const
{
    return static_cast<int>(mObjects.size());
}

////////////////////////////////////////////////////////////
tme::Object::Ptr ObjectGroup::getObject(std::string const& name)
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
tme::Object::Ptr ObjectGroup::getObject(int id)
{
    if (id >= 0 && id < static_cast<int>(mObjects.size()))
    {
        return mObjects[id];
    }
    return nullptr;
}

////////////////////////////////////////////////////////////
void ObjectGroup::setObject(tme::Object::Ptr object)
{
    if (object != nullptr)
    {
        sf::Color color = Image::getColor(mColor);
        color.a = 255.f * mOpacity;
        object->applyColor(color);

        mObjects.push_back(object);
    }
}

} // namespace tme
