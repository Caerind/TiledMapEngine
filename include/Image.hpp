#ifndef TME_IMAGE_HPP
#define TME_IMAGE_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

/*

To Do :

-Understand Data
-Conversion sf::Color <-> std::string(Trans)

*/


class Image
{
    public:
        typedef std::shared_ptr<Image> Ptr;
        typedef std::shared_ptr<sf::Texture> TexturePtr;

        /*
        struct Data
        {

        };
        */

    public:
        Image();

        bool load(std::string const& filename = "");

        TexturePtr getTexture() const;
        std::string getFormat() const;
        std::string getSource() const;
        std::string getTrans() const;
        int getWidth() const;
        int getHeight() const;

        void setTexture(TexturePtr texture);
        void setFormat(std::string const& format);
        void setSource(std::string const& source);
        void setTrans(std::string const& trans);
        void setWidth(int width);
        void setHeight(int height);

    public:
        static std::string getFormat(std::string const& filename);
        static sf::Color getColor(std::string const& hexColor);

    protected:
        TexturePtr mTexture;

        std::string mFormat; // Used for embedded images, in combination with a data child element. Valid values are file extensions like png, gif, jpg, bmp, etc. (since 0.9.0)
        std::string mSource; // The reference to the tileset image file (Tiled supports most common image formats).
        std::string mTrans; // Defines a specific color that is treated as transparent (example value: "#FF00FF" for magenta). Up until Tiled 0.10, this value is written out without a # but this is planned to change.
        int mWidth; // The image width in pixels (optional, used for tile index correction when the image changes)
        int mHeight; // The image height in pixels (optional)
};

#endif // TME_IMAGE_HPP
