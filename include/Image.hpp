#ifndef TME_IMAGE_HPP
#define TME_IMAGE_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>

class Image
{
    public:
        std::shared_ptr<Image> Ptr;
        std::shared_ptr<sf::Texture> TexturePtr;

    public:
        Image();

    private:
};

#endif // TME_IMAGE_HPP
