#include "../include/Image.hpp"

////////////////////////////////////////////////////////////
Image::Image()
{
    mTexture = nullptr;
    mFormat = "";
    mSource = "";
    mTrans = "";
    mWidth = 0;
    mHeight = 0;
}

////////////////////////////////////////////////////////////
bool Image::load(std::string const& filename)
{
    if (filename == "")
    {
        filename = mSource;
    }

    sf::Image img;
    if (!img.loadFromFile(filename))
    {
        return false;
    }
    mFormat = Image::getFormat(filename);
    mSource = filename;

    if (mTrans != "")
    {
        img.createMaskFromColor(Image::getColor(mTrans));
    }

    mWidth = static_cast<int>(img.getSize().x);
    mHeight = static_cast<int>(img.getSize().y);

    mTexture = std::make_shared<sf::Texture>(new sf::Texture());
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
TexturePtr Image::getTexture() const
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
    if (filename.rfind(".") != std::string::npos)
    {
        return filename.substr(filename.rfind(".")+1;filename.size());
    }
    else
    {
        return "";
    }
}

////////////////////////////////////////////////////////////
sf::Color Image::getColor(std::string const& hexColor);
{
    return sf::Color::Transparent;
}

