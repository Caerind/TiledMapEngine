#ifndef TME_IMAGELAYER_HPP
#define TME_IMAGELAYER_HPP

#include <SFML/Graphics/Vertex.hpp>

#include "ILayer.hpp"
#include "Image.hpp"

namespace tme
{

class Map;

class ImageLayer : public ILayer, public Image
{
    public:
        typedef std::shared_ptr<ImageLayer> Ptr;

    public:
        ImageLayer(Map* map);

        bool loadFromFile(std::string const& filename);

        void render(sf::RenderTarget& target, sf::RenderStates states);

    private:
        sf::Vertex mVertices[4];
};

} // namespace tme

#endif // TME_IMAGELAYER_HPP
