#include "../include/Manager.hpp"

Manager::Manager()
{
}

Manager::~Manager()
{
}

bool Manager::loadMap(std::string const& filename)
{
    if (mMaps.find(filename) == mMaps.end())
    {
        Map::Ptr map = std::make_shared<Map>(new Map());
        if (map->loadFromFile(filename))
        {
            map->setManager(this);
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

void Manager::addMap(Map::Ptr map)
{
    if (map != nullptr)
    {
        map->setManager(this);
        mMaps[map->getFilename()] = map;
    }
}

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

bool Manager::loadTexture(std::string const& filename)
{
    if (mTextures.find(filename) == mTextures.end())
    {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(new sf::Texture());
        if (texture->loadFromFile(filename))
        {
            mTextures[filename] = texture;
            return true;
        }
        return false;
    }
    else
    {
        return true;
    }
}

void Manager::addTexture(std::shared_ptr<sf::Texture> texture, std::string const& filename)
{
    if (texture != nullptr && filename != "")
    {
        mTextures[filename] = texture;
    }
}

std::shared_ptr<sf::Texture> Manager::getTexture(std::string const& filename)
{
    if (mTextures.find(filename) != mTextures.end())
    {
        return mTextures[filename];
    }
    else
    {
        if (loadTexture(filename))
        {
            return mTextures[filename];
        }
        else
        {
            return nullptr;
        }
    }
}
