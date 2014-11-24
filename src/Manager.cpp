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
}

////////////////////////////////////////////////////////////
void Manager::render(int layer, sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    for (auto itr = mMaps.begin(); itr != mMaps.end(); itr++)
    {
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
