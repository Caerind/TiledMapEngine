#include "../include/Image.hpp"
#include "../include/Map.hpp"

////////////////////////////////////////////////////////////
Image::Image(Map* map) : mMap(map), mTexture(nullptr)
{
}

////////////////////////////////////////////////////////////
bool Image::load(std::string const& filename)
{
    mSource = filename;

    sf::Image img;
    if (!img.loadFromFile(mSource))
    {
        return false;
    }
    mFormat = Image::getFormat(mSource);

    if (mTrans != "")
    {
        img.createMaskFromColor(Image::getColor(mTrans));
    }

    mWidth = static_cast<int>(img.getSize().x);
    mHeight = static_cast<int>(img.getSize().y);

    mTexture = std::shared_ptr<sf::Texture>(new sf::Texture());
    if (mTexture == nullptr)
    {
        return false;
    }

    if (!mTexture->loadFromImage(img, sf::IntRect(0,0,mWidth,mHeight)))
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////
Image::TexturePtr Image::getTexture() const
{
    return mTexture;
}

////////////////////////////////////////////////////////////
std::string Image::getFormat() const
{
    return mFormat;
}

////////////////////////////////////////////////////////////
std::string Image::getSource() const
{
    return mSource;
}

////////////////////////////////////////////////////////////
std::string Image::getTrans() const
{
    return mTrans;
}

////////////////////////////////////////////////////////////
int Image::getWidth() const
{
    return mWidth;
}

////////////////////////////////////////////////////////////
int Image::getHeight() const
{
    return mHeight;
}

////////////////////////////////////////////////////////////
void Image::setTexture(TexturePtr texture)
{
    mTexture = texture;
}

////////////////////////////////////////////////////////////
void Image::setFormat(std::string const& format)
{
    mFormat = format;
}

////////////////////////////////////////////////////////////
void Image::setSource(std::string const& source)
{
    mSource = source;
}

////////////////////////////////////////////////////////////
void Image::setTrans(std::string const& trans)
{
    mTrans = trans;
}

////////////////////////////////////////////////////////////
void Image::setWidth(int width)
{
    mWidth = width;
}

////////////////////////////////////////////////////////////
void Image::setHeight(int height)
{
    mHeight = height;
}

////////////////////////////////////////////////////////////
std::string Image::getFormat(std::string const& filename)
{
    return (filename.rfind(".") != std::string::npos) ? filename.substr(filename.rfind(".")+1,filename.size()) : "";
}

////////////////////////////////////////////////////////////
sf::Color Image::getColor(std::string const& hexColor)
{
    sf::Color color;
    std::stringstream ss;
    std::string hex = hexColor;

    // If the value as a # as first char
    if (hex.front() == '#')
    {
        hex.erase(0,1);
    }

    for (unsigned int i = 0; i < hexColor.size() / 2; i++)
    {
        ss << std::hex << hex.substr(0,2);
        hex.erase(0,2);
        switch (i)
        {
            case 0: ss >> color.r; break;
            case 1: ss >> color.g; break;
            case 2: ss >> color.b; break;
            case 3: ss >> color.a; break;
            default: break;
        }
        ss.clear();
    }

    return color;
}

////////////////////////////////////////////////////////////
std::string Image::getString(sf::Color rgbColor)
{
    std::stringstream ss;
    ss << std::hex << rgbColor.r;
    ss << std::hex << rgbColor.g;
    ss << std::hex << rgbColor.b;
    return ss.str();
}

