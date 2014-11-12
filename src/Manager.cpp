#include "../include/Manager.hpp"

Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::update(sf::Time dt)
{
    for (auto itr = mMaps.begin(); itr != mMaps.end(); itr++)
    {
        itr->second->update(dt);
    }
}

void Manager::render(unsigned int layer, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates())
{
    states.transform *= getTransform();
    for (auto itr = mMaps.begin(); itr != mMaps.end(); itr++)
    {
        itr->second->render(layer,target,states);
    }
}

bool Manager::loadMap(std::string const& filename)
{
    if (mMaps.find(filename) == mMaps.end())
    {
        Map::Ptr map = std::make_shared<Map>(new Map(this));
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

/*
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
/*
