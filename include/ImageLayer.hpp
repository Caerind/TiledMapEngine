#ifndef TME_IMAGELAYER_HPP
#define TME_IMAGELAYER_HPP

#include <SFML/Graphics/Vertex.hpp>

#include "ILayer.hpp"
#include "Image.hpp"

class Map;

class ImageLayer : public ILayer, public Image
{
    public:
        typedef std::shared_ptr<ImageLayer> Ptr;

    public:
        ImageLayer(Map* map);

        bool loadFromFile(std::string const& filename);

        void render(sf::RenderTarget& target, sf::RenderStates states);

        void setX(int x);
        void setY(int y);

    private:
        void update();

    private:
        sf::Vertex mVertices[4];
};

#endif // TME_IMAGELAYER_HPP
