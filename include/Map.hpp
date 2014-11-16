#ifndef TME_MAP_HPP
#define TME_MAP_HPP

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Time.hpp>

#include "../pugixml/pugixml.hpp"

#include "Layer.hpp"
#include "ParserUtils.hpp"
#include "Properties.hpp"
#include "Tileset.hpp"

/*

To Do :

-Parser
-RenderOrder?

*/

class Manager;

class Map : public Properties, public sf::Transformable
{
    public:
        typedef std::shared_ptr<Map> Ptr;

    public:
        Map();
        Map(Manager* manager);
        ~Map();

        bool loadFromFile(std::string const& filename);

        void update(sf::Time dt);
        void render(unsigned int layer, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates());

        float getVersion() const;
        std::string getOrientation() const;
        int getWidth() const;
        int getHeight() const;
        int getTileWidth() const;
        int getTileHeight() const;
        std::string getBackgroundColor() const;
        std::string getRenderOrder() const;
        Tileset::Ptr getTileset(int gid);
        Tileset::Ptr getTileset(std::string const& name);
        Layer::Ptr getLayer(std::string const& name);

        void setVersion(float version);
        void setOrientation(std::string const& orientation);
        void setWidth(int width);
        void setHeight(int height);
        void setTileWidth(int tileWidth);
        void setTileHeight(int tileHeight);
        void setBackgroundColor(std::string const& backgroundColor);
        void setRenderOrder(std::string const& renderOrder);
        void setTileset(Tileset::Ptr tileset);
        void setLayer(Layer::Ptr layer);

    private:
        bool parseMap(pugi::xml_node node);
        bool parseProperties(pugi::xml_node node, Properties* properties);
        bool parseTileset(pugi::xml_node node); // Including Image
        bool parseLayer(pugi::xml_node node); // Including Tiles

    private:
        static std::string getDirectory(std::string const& filename);

    private:
        Manager* mManager;
        std::string mFilename;

        float mVersion; // The TMX format version, generally 1.0.
        std::string mOrientation; // Map orientation. Tiled supports "orthogonal", "isometric" and "staggered" (since 0.9) at the moment.
        int mWidth; // The map width in tiles.
        int mHeight; // The map height in tiles.
        int mTileWidth; // The width of a tile.
        int mTileHeight; // The height of a tile.
        std::string mBackgroundColor; // The background color of the map. (since 0.9, optional)
        std::string mRenderOrder; // The order in which tiles on tile layers are rendered. Valid values are right-down (the default), right-up, left-down and left-up. In all cases, the map is drawn row-by-row. (since 0.10, but only supported for orthogonal maps at the moment)

        std::map<std::string,Tileset::Ptr> mTilesets;
        std::map<std::string,Layer::Ptr> mLayers;
        //std::map<std::string,ObjectGroup::Ptr> mObjectGroups;
        //std::map<std::string,ImageLayer::Ptr> mImageLayers;
};

#endif // TME_MAP_HPP
