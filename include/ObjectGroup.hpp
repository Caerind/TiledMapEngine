#ifndef OBJECTGROUP_HPP
#define OBJECTGROUP_HPP

#include <vector>

#include "ILayer.hpp"
#include "Image.hpp"
#include "Object.hpp"

class Map;

class ObjectGroup : public ILayer
{
    public:
        typedef std::shared_ptr<ObjectGroup> Ptr;

    public:
        ObjectGroup(Map* map);

        void render(sf::RenderTarget& target, sf::RenderStates states);

        std::string getColor() const;
        void setColor(std::string const& color);
        void setOpacity(float opacity);

        int getObjectCount() const;
        Object::Ptr getObject(std::string const& name);
        Object::Ptr getObject(int id);
        void setObject(Object::Ptr object);

        int getWidth() const;
        int getHeight() const;
        void setWidth(int width);
        void setHeight(int height);

    private:
        Map* mMap;

        std::string mColor; // The color used to display the objects in this group.
        int mWidth; //...
        int mHeight; //...

        std::vector<Object::Ptr> mObjects;
};

#endif // OBJECTGROUP_HPP
