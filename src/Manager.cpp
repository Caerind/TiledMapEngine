#include "../include/Manager.hpp"

namespace tme
{

////////////////////////////////////////////////////////////
Manager::Manager()
{
}

////////////////////////////////////////////////////////////
Manager::~Manager()
{
    //TODO : Fix a bug here ...
}

////////////////////////////////////////////////////////////
void Manager::render(int layer, sf::RenderTarget& target, sf::RenderStates states, sf::FloatRect rect)
{
    states.transform *= getTransform();
    if (rect == sf::FloatRect(0,0,0,0))
    {
        for (auto itr = mMaps.begin(); itr != mMaps.end(); itr++)
        {
            itr->second->render(layer,target,states);
        }
    }
    else
    {
        render(layer,target,rect,states);
    }
}

////////////////////////////////////////////////////////////
void Manager::render(int layer, sf::RenderTarget& target, sf::FloatRect rect, sf::RenderStates states)
{
    for (auto itr = mMaps.begin(); itr != mMaps.end(); itr++)
    {
        if (itr->second->getBounds().intersects(rect))
            itr->second->render(layer,target,states);
    }
}

////////////////////////////////////////////////////////////
bool Manager::loadMap(std::string const& filename)
{
    if (mMaps.find(filename) == mMaps.end())
    {
        Map::Ptr map = std::shared_ptr<Map>(new Map(this));
        if (map->loadFromFile(filename))
        {
            mMaps[filename] = map;
            return true;
        }
        return false;
    }
    else
    {
        return true;
    }
}

////////////////////////////////////////////////////////////
Map::Ptr Manager::getMap(std::string const& filename)
{
    if (mMaps.find(filename) != mMaps.end())
    {
        return mMaps[filename];
    }
    else
    {
        return nullptr;
    }
}

////////////////////////////////////////////////////////////
Image::Ptr Manager::getImage(std::string const& sourceName)
{
    if (mImages.find(sourceName) != mImages.end())
    {
        return mImages[sourceName];
    }
    else
    {
        return nullptr;
    }
}

////////////////////////////////////////////////////////////
void Manager::addImage(Image::Ptr img)
{
    if (img != nullptr)
    {
        mImages[img->getSource()] = img;
    }
}

} // namespace tme
