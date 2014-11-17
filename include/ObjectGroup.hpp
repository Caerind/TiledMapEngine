#ifndef OBJECTGROUP_HPP
#define OBJECTGROUP_HPP

#include <map>
#include <string>

#include <SFML/Graphics/Transformable.hpp>

#include "ILayer.hpp"
#include "Object.hpp"

class Map;

class ObjectGroup : public ILayer, public sf::Transformable
{
    public:
        typedef std::shared_ptr<ObjectGroup> Ptr;

    public:
        ObjectGroup(Map* map);

        void render(sf::RenderTarget& target, sf::RenderStates states);

        std::string getName() const;
        std::string getColor() const;
        float getOpacity() const;
        bool isVisible() const;

        Object::Ptr getObject(std::string const& name);
        Object::Ptr getObject(int id);

        void setName(std::string const& name);
        void setColor(std::string const& color);
        void setOpacity(float opacity);
        void setVisible(bool visible);

        void setObject(Object::Ptr object);

    private:
        Map* mMap;

        std::string mName; // The name of the object group.
        std::string mColor; // The color used to display the objects in this group.
        float mOpacity; // The opacity of the layer as a value from 0 to 1. Defaults to 1.
        bool mVisible; // Whether the layer is shown (1) or hidden (0). Defaults to 1.

        std::map<std::string,Object::Ptr> mObjects;
};

#endif // OBJECTGROUP_HPP
