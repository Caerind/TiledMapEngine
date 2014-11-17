#ifndef TME_IMAGELAYER_HPP
#define TME_IMAGELAYER_HPP

#include <string>

#include <SFML/Graphics/Vertex.hpp>

#include "ILayer.hpp"
#include "Image.hpp"

/*

To Do :

-Opacity

*/

class Map;

class ImageLayer : public ILayer, public Image
{
    public:
        typedef std::shared_ptr<ImageLayer> Ptr;

    public:
        ImageLayer(Map* map);

        bool loadFromFile(std::string const& filename);

        void render(sf::RenderTarget& target, sf::RenderStates states);

        std::string getName() const;
        int getX() const;
        int getY() const;
        float getOpacity() const;
        bool isVisible() const;

        void setName(std::string const& name);
        void setX(int x);
        void setY(int y);
        void setOpacity(float opacity);
        void setVisible(bool visible);

    private:
        void update();

    private:
        sf::Vertex mVertices[4];

        std::string mName; // The name of the image layer.
        int mX; // The x position of the image layer in pixels.
        int mY; // The y position of the image layer in pixels.
        float mOpacity; // The opacity of the layer as a value from 0 to 1. Defaults to 1.
        bool mVisible; // Whether the layer is shown (1) or hidden (0). Defaults to 1.
};

#endif // TME_IMAGELAYER_HPP
