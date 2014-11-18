#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
Map::Map() : mManager(nullptr), mVersion(1.0f), mOrientation(""), mWidth(0), mHeight(0), mTileWidth(0), mTileHeight(0)
, mBackgroundColor(""), mRenderOrder("")
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

    mFilename = filename;

    pugi::xml_node mapNode;

    if (!(mapNode = tmxFile.child("map")))
    {
        return false;
    }

    return parseMap(mapNode);
}

////////////////////////////////////////////////////////////
bool Map::saveToFile(std::string const& filename)
{
    if (filename != "")
    {
        return saveMap(filename);
    }
    else if (filename == "" && mFilename != "")
    {
        return saveMap(mFilename);
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////
void Map::render(int layer, sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();
    if (layer == 0 && mBackgroundColor != "")
    {
        sf::RectangleShape background;
        background.setSize(sf::Vector2f(mWidth * mTileWidth, mHeight * mTileHeight));
        background.setFillColor(Image::getColor(mBackgroundColor));
        target.draw(background,states);
    }
    if (layer >= 0 && layer < getILayerCount() && mILayers[layer] != nullptr)
    {
        mILayers[layer]->render(target,states);
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
Layer::Ptr Map::getLayer(int id)
{
    if (id >= getLayerCount())
        return nullptr;
    int i = 0;
    for (auto itr = mLayers.begin(); itr != mLayers.end(); itr++)
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
Layer::Ptr Map::getLayer(std::string const& name)
{
    return (mLayers.find(name) != mLayers.end()) ? mLayers[name] : nullptr;
}

////////////////////////////////////////////////////////////
ImageLayer::Ptr Map::getImageLayer(int id)
{
    if (id >= getImageLayerCount())
        return nullptr;
    int i = 0;
    for (auto itr = mImageLayers.begin(); itr != mImageLayers.end(); itr++)
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
ImageLayer::Ptr Map::getImageLayer(std::string const& name)
{
    return (mImageLayers.find(name) != mImageLayers.end()) ? mImageLayers[name] : nullptr;
}

////////////////////////////////////////////////////////////
int Map::getLayerCount() const
{
    return mLayers.size();
}

////////////////////////////////////////////////////////////
int Map::getTilesetCount() const
{
    return mTilesets.size();
}

////////////////////////////////////////////////////////////
int Map::getImageLayerCount() const
{
    return mImageLayers.size();
}

////////////////////////////////////////////////////////////
int Map::getILayerCount() const
{
    return mILayers.size();
}

////////////////////////////////////////////////////////////
Manager* Map::getManager() const
{
    return mManager;
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
    	mILayers.push_back(layer);
    }
}

////////////////////////////////////////////////////////////
void Map::setImageLayer(ImageLayer::Ptr layer)
{
    if (layer != nullptr)
    {
    	mImageLayers[layer->getName()] = layer;
    	mILayers.push_back(layer);
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
            if (!parseProperties(n,this))
                return false;
        if (nName == "tileset")
            if (!parseTileset(n))
                return false;
        if (nName == "layer")
            if (!parseLayer(n))
                return false;
        if (nName == "imagelayer")
            if (!parseImageLayer(n))
                return false;
    }

    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseProperties(pugi::xml_node node, Properties* properties)
{
    if (properties == nullptr)
    {
        return false;
    }

    if (node)
    {
        for (auto property : node.children("property"))
        {
            properties->setProperty(std::string(property.attribute("name").as_string()), std::string(property.attribute("value").as_string()));
        }
    }
    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseTileset(pugi::xml_node node)
{
    Tileset::Ptr tileset = std::shared_ptr<Tileset>(new Tileset(this));

    tileset->setFirstGid(node.attribute("firstgid").as_int());

    pugi::xml_attribute source = node.attribute("source");
    if (source)
    {
        pugi::xml_document tsx;
        if (!tsx.load_file(std::string(getDirectory(mFilename) + source.as_string()).c_str()))
        {
            return false;
        }
        node = tsx.child("tileset");
    }

    tileset->setName(node.attribute("name").as_string());
    tileset->setTileWidth(node.attribute("tilewidth").as_int());
    tileset->setTileHeight(node.attribute("tileheight").as_int());

    pugi::xml_attribute spacing = node.attribute("spacing");
    if (spacing) tileset->setSpacing(spacing.as_int());

    pugi::xml_attribute margin = node.attribute("margin");
    if (margin) tileset->setMargin(margin.as_int());

    for (const pugi::xml_node& n : node.children())
    {
        std::string nName = n.name();
        if (nName == "tileoffset")
        {
            Tileset::TileOffset offset;
            offset.x = n.attribute("x").as_int();
            offset.y = n.attribute("y").as_int();
            tileset->setTileOffset(offset);
        }
        else if (nName == "image")
        {
            if (n.attribute("source"))
            {
                if (!tileset->load(std::string(getDirectory(mFilename) + n.attribute("source").as_string())))
                {
                    return false;
                }
            }
        }
        else if (nName == "terraintypes")
        {
            // ...
        }
        else if (nName == "properties")
        {
            if (!parseProperties(n,tileset.get()))
                return false;
        }
    }

    // Parse each tile property
    for (const pugi::xml_node& tile_node : node.children("tile"))
    {
        Tileset::Tile::Ptr tile = std::shared_ptr<Tileset::Tile>(new Tileset::Tile());
        if (tile_node.attribute("id")) tile->setId(tile_node.attribute("id").as_int());
        if (tile_node.attribute("terrain")) tile->setTerrain(tile_node.attribute("terrain").as_string());
        if (tile_node.attribute("probability")) tile->setProbability(tile_node.attribute("probability").as_float());

        pugi::xml_node prop = tile_node.child("properties");
        if (prop)
        {
            if (!parseProperties(prop,tile.get()))
            {
                return false;
            }
        }

        tileset->addTile(tile);
    }

    mTilesets[tileset->getName()] = tileset;

    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseLayer(pugi::xml_node node)
{
    Layer::Ptr layer = std::shared_ptr<Layer>(new Layer(this));

    layer->setName(node.attribute("name").as_string());

    pugi::xml_attribute attribute_x = node.attribute("x");
    pugi::xml_attribute attribute_y = node.attribute("y");
    pugi::xml_attribute attribute_width = node.attribute("width");
    pugi::xml_attribute attribute_height = node.attribute("height");
    pugi::xml_attribute attribute_opacity = node.attribute("opacity");
    pugi::xml_attribute attribute_visible = node.attribute("visible");

    if (attribute_x) layer->setX(attribute_x.as_int());
    if (attribute_y) layer->setY(attribute_y.as_int());
    if (attribute_width)
        layer->setWidth(attribute_width.as_int());
    else
        layer->setWidth(getWidth());
    if (attribute_height)
        layer->setHeight(attribute_height.as_int());
    else
        layer->setHeight(getHeight());
    if (attribute_opacity) layer->setOpacity(attribute_opacity.as_float());
    if (attribute_visible) layer->setVisible(attribute_visible.as_bool());

    for (const pugi::xml_node& n : node.children())
    {
        std::string nName = n.name();
        if (nName == "properties")
        {
            if (!parseProperties(n,layer.get()))
                return false;
        }
        else if (nName == "data")
        {
            std::string data = n.text().as_string();
            Layer::Tile tile;
            int posX = 0;
            int posY = 0;
            // Check if the encoding attribute exists in data_node
            pugi::xml_attribute attribute_encoding = n.attribute("encoding");
            if (attribute_encoding)
            {
                std::string encoding = attribute_encoding.as_string();

                if (encoding == "base64") // Base64 encoding
                {
                    std::stringstream ss;
                    ss << data;
                    ss >> data;
                    if (!ParserUtils::base64_decode(data))
                    {
                        return false;
                    }

                    int expectedSize = layer->getWidth() * layer->getHeight() * 4;  // number of tiles * 4 bytes = 32bits / tile
                    std::vector<unsigned char>byteVector;  // to hold decompressed data as bytes
                    byteVector.reserve(expectedSize);

                    // Check if the compression attribute exists in data_node
                    if (n.attribute("compression"))
                    {
                        if (!ParserUtils::decompressString(data))
                        {
                            return false;
                        }
                        for (std::string::iterator i = data.begin(); i != data.end(); ++i)
                            byteVector.push_back(*i);
                    }
                    else
                    {
                        for (std::string::iterator i = data.begin(); i != data.end(); ++i)
                            byteVector.push_back(*i);
                    }

                    for (unsigned int i = 0; i < byteVector.size() - 3 ; i += 4)
                    {
                        layer->setTileId(posX,posY,byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24);

                        posX = (posX + 1) % layer->getWidth();
                        if (posX == 0) posY++;
                    }
                }
                else if (encoding == "csv") // CSV encoding
                {
                    int id;
                    std::stringstream data_stream(data);
                    while (data_stream >> id)
                    {
                        if (data_stream.peek() == ',')
                            data_stream.ignore();

                        layer->setTileId(posX,posY,id);

                        posX = (posX + 1) % layer->getWidth();
                        if (posX == 0) posY++;
                    }
                }
            }
            else // Unencoded
            {
                for (const pugi::xml_node& tile_node : n.children("tile"))
                {
                    layer->setTileId(posX,posY,tile_node.attribute("gid").as_int());

                    posX = (posX + 1) % layer->getWidth();
                    if (posX == 0) posY++;
                }
            }
        }
    }

    setLayer(layer);
    return true;
}

////////////////////////////////////////////////////////////
bool Map::parseImageLayer(pugi::xml_node node)
{
    ImageLayer::Ptr layer = std::shared_ptr<ImageLayer>(new ImageLayer(this));

    layer->setName(node.attribute("name").as_string());

    pugi::xml_attribute attribute_x = node.attribute("x");
    pugi::xml_attribute attribute_y = node.attribute("y");
    pugi::xml_attribute attribute_opacity = node.attribute("opacity");
    pugi::xml_attribute attribute_visible = node.attribute("visible");

    if (attribute_x) layer->setX(attribute_x.as_int());
    if (attribute_y) layer->setY(attribute_y.as_int());
    if (attribute_opacity) layer->setOpacity(attribute_opacity.as_float());
    if (attribute_visible) layer->setVisible(attribute_visible.as_bool());

    for (const pugi::xml_node& n : node.children())
    {
        std::string nName = n.name();
        if (nName == "properties")
        {
            if (!parseProperties(n,layer.get()))
                return false;
        }
        else if (nName == "image")
        {
            if (n.attribute("source"))
            {
                if (!layer->loadFromFile(std::string(getDirectory(mFilename) + n.attribute("source").as_string())))
                {
                    return false;
                }
            }
        }
    }

    setImageLayer(layer);
    return true;
}

////////////////////////////////////////////////////////////
bool Map::saveMap(std::string const& filename)
{
    std::ofstream file(filename);
    if (!file)
    {
        return false;
    }

    // XML Header
    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;

    // Open Map Node
    file << "<map version=\"" << mVersion << "\" orientation=\"" << mOrientation << "\" width=\"" << mWidth << "\" height=\"" << mHeight << "\"";
    file << " tilewidth=\"" << mTileWidth << "\" tileheight=\"" << mTileHeight << "\" backgroundcolor=\"" << mBackgroundColor << "\" renderorder=\"" << mRenderOrder << "\">" << std::endl;

    int indent = 1;
    // Map Properties
    saveProperties(file,this,indent);

    // Save All Tilesets
    saveTilesets(file);







    // End Map Node
    file << "</map>" << std::endl;

    file.close();

    return true;
}

////////////////////////////////////////////////////////////
void Map::saveProperties(std::ofstream& stream, Properties* properties, int indent)
{
    if (properties != nullptr)
    {
        if (!properties->isEmpty())
        {
            addIndent(stream,indent);
            stream << "<properties>" << std::endl;
            for (int i = 0; i < properties->getPropertyCount(); i++)
            {
                Properties::Property p = properties->getProperty(i);
                if (p.first != "")
                {
                    addIndent(stream,indent + 1);
                    stream << "<property name=\"" << p.first << "\" value=\"" << p.second << "\"/>" << std::endl;
                }
            }
            addIndent(stream,indent);
            stream << "</properties>" << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////
void Map::saveTilesets(std::ofstream& stream)
{
    for (auto itr = mTilesets.begin(); itr != mTilesets.end(); itr++)
    {
        if (itr->second != nullptr)
        {
            stream << " <tileset firstgid=\"" << itr->second->getFirstGid();
            stream << "\" name=\"" << itr->second->getName();
            stream << "\" tilewidth=\"" << itr->second->getTileWidth();
            stream << "\" tileheight=\"" << itr->second->getTileHeight();
            stream << "\" spacing=\"" << itr->second->getSpacing();
            stream << "\" margin=\"" << itr->second->getMargin();
            stream << "\">" << std::endl;

            // Write Properties
            saveProperties(stream,itr->second.get(),2);

            // Write Image
            stream << "  <image source=\"" << itr->second->getSource();
            stream << "\" trans=\"" << itr->second->getTrans();
            stream << "\" width=\"" << itr->second->getWidth();
            stream << "\" height=\"" << itr->second->getHeight();
            stream << "\"/>" << std::endl;

            // Write Tile/Terrain/TileOffset



            stream << " </tileset>" << std::endl;
        }
    }
}

////////////////////////////////////////////////////////////
void Map::addIndent(std::ofstream& stream, int indent)
{
    for (int i = 0; i < indent; i++)
    {
        stream << " ";
    }
}

////////////////////////////////////////////////////////////
std::string Map::getDirectory(std::string const& filename)
{
    return filename.substr(0, filename.find_last_of('/') + 1);
}

