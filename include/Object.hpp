#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Properties.hpp"

class Map;

class Object : public Properties, public sf::Drawable, public sf::Transformable
{
    public:
        typedef std::shared_ptr<Object> Ptr;

        enum Type
        {
            Rectangle,
            Ellipse,
            Polygon,
            Polyline,
            Tile,
        };

    public:
        Object(Map* map);

        std::string getName() const;
        Type getType() const;
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        float getRotation() const;
        int getGid() const;
        bool isVisible() const;
        std::string getPoints() const;

        sf::Vertex* getVertex(int id);

        void setName(std::string const& name);
        void setType(Type type);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        void setRotation(float rotation);
        void setGid(int gid);
        void setVisible(bool visible);
        void setPoints(std::string const& points);

        void setVertex(sf::Vertex vertex, int id);

        void applyColor(sf::Color color);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Map* mMap;

        std::string mName; // The name of the object. An arbitrary string.
        Type mType; // The type of the object. An arbitrary string.
        int mX; // The x coordinate of the object in pixels.
        int mY; // The y coordinate of the object in pixels.
        int mWidth; // The width of the object in pixels (defaults to 0).
        int mHeight; // The height of the object in pixels (defaults to 0).
        float mRotation; // The rotation of the object in degrees clockwise (defaults to 0). (on git master)
        int mGid; // An reference to a tile (optional).
        bool mVisible; // Whether the object is shown (1) or hidden (0). Defaults to 1. (since 0.9.0)

        std::string mPoints;
        std::vector<sf::Vertex> mVertices;
};

#endif // OBJECT_HPP
