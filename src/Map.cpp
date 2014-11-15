#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
Map::Map() : mManager(nullptr)
{
}

////////////////////////////////////////////////////////////
Map::Map(Manager* manager) : mManager(manager)
{
}

////////////////////////////////////////////////////////////
Map::~Map()
{
}

////////////////////////////////////////////////////////////
bool Map::loadFromFile(std::string const& filename)
{
    pugi::xml_document tmxFile;

    if (!tmxFile.load_file(filename.c_str()))
    {
        return false;
    }

    pugi::xml_node mapNode;

    if (!(mapNode = tmxFile.child("map")))
    {
        return false;
    }

    return parseMap(mapNode);
}

////////////////////////////////////////////////////////////
void Map::update(sf::Time dt)
{
}

////////////////////////////////////////////////////////////
void Map::render(unsigned int layer, sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    unsigned int i = 0;
    for (auto itr = mLayers.begin(); itr != mLayers.end(); itr++)
    {
    	if (layer == i)
    	{
    		if (layer == 0 && mBackgroundColor != "")
    		{
                sf::RectangleShape background;
                background.setSize(sf::Vector2f(mWidth * mTileWidth, mHeight * mTileHeight));
                background.setFillColor(Image::getColor(mBackgroundColor));
                target.draw(background,states);
    		}

    		itr->second->render(target,states);
    	}
    }
}

////////////////////////////////////////////////////////////
float Map::getVersion() const
{
    return mVersion;
}

////////////////////////////////////////////////////////////
std::string Map::getOrientation() const
{
    return mOrientation;
}

////////////////////////////////////////////////////////////
int Map::getWidth() const
{
    return mWidth;
}

////////////////////////////////////////////////////////////
int Map::getHeight() const
{
    return mHeight;
}

////////////////////////////////////////////////////////////
int Map::getTileWidth() const
{
    return mTileWidth;
}

////////////////////////////////////////////////////////////
int Map::getTileHeight() const
{
    return mTileHeight;
}

////////////////////////////////////////////////////////////
std::string Map::getBackgroundColor() const
{
    return mBackgroundColor;
}

////////////////////////////////////////////////////////////
std::string Map::getRenderOrder() const
{
    return mRenderOrder;
}

////////////////////////////////////////////////////////////
Tileset::Ptr Map::getTileset(int gid)
{
    for (auto itr = mTilesets.begin(); itr != mTilesets.end(); itr++)
    {
        if (gid >= itr->second->getFirstGid() && gid <= itr->second->getLastGid())
            return itr->second;
    }
    return nullptr;
}

////////////////////////////////////////////////////////////
Tileset::Ptr Map::getTileset(std::string const& name)
{
    return (mTilesets.find(name) != mTilesets.end()) ? mTilesets[name] : nullptr;
}

////////////////////////////////////////////////////////////
Layer::Ptr Map::getLayer(std::string const& name)
{
    return (mLayers.find(name) != mLayers.end()) ? mLayers[name] : nullptr;
}

////////////////////////////////////////////////////////////
void Map::setVersion(float version)
{
    mVersion = version;
}

////////////////////////////////////////////////////////////
void Map::setOrientation(std::string const& orientation)
{
    mOrientation = orientation;
}

////////////////////////////////////////////////////////////
void Map::setWidth(int width)
{
    mWidth = width;
}

////////////////////////////////////////////////////////////
void Map::setHeight(int height)
{
    mHeight = height;
}

////////////////////////////////////////////////////////////
void Map::setTileWidth(int tileWidth)
{
    mTileWidth = tileWidth;
}

////////////////////////////////////////////////////////////
void Map::setTileHeight(int tileHeight)
{
    mTileHeight = tileHeight;
}

////////////////////////////////////////////////////////////
void Map::setBackgroundColor(std::string const& backgroundColor)
{
    mBackgroundColor = backgroundColor;
}

////////////////////////////////////////////////////////////
void Map::setRenderOrder(std::string const& renderOrder)
{
    mRenderOrder = renderOrder;
}

////////////////////////////////////////////////////////////
void Map::setTileset(Tileset::Ptr tileset)
{
    if (tileset != nullptr)
    {
    	mTilesets[tileset->getName()] = tileset;
    }
}

////////////////////////////////////////////////////////////
void Map::setLayer(Layer::Ptr layer)
{
    if (layer != nullptr)
    {
    	mLayers[layer->getName()] = layer;
    }
}

////////////////////////////////////////////////////////////
bool Map::parseMap(pugi::xml_node node)
{
    for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute())
    {
        std::string attrName = attr.name();
        if (attrName == "version") mVersion = attr.as_float();
        else if (attrName == "orientation") mOrientation = attr.value();
        else if (attrName == "width") mWidth = attr.as_int();
        else if (attrName == "height") mHeight = attr.as_int();
        else if (attrName == "tilewidth") mTileWidth = attr.as_int();
        else if (attrName == "tileheight") mTileHeight = attr.as_int();
        else if (attrName == "backgroundcolor") mBackgroundColor = attr.value();
        else if (attrName == "renderorder") mRenderOrder = attr.value();
    }

    for (pugi::xml_node n : node.children())
    {
        std::string nName = n.name();
        if (nName == "properties")
            if (!parseProperties(n))
                return false;
        if (nName == "tileset")
            if (!parseTileset(n))
                return false;
        if (nName == "layer")
            if (!parseLayer(n))
                return false;
    }



    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseTileset(pugi::xml_node node)
{
    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseLayer(pugi::xml_node node)
{
    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseProperties(pugi::xml_node node)
{
    return true;
}

////////////////////////////////////////////////////////////
std::string Map::getDirectory(std::string const& filename)
{
    return (filename.rfind("/") != std::string::npos) ? filename.substr(0, filename.rfind("/")) : "";
}

