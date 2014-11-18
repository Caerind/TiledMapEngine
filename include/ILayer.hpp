#ifndef ILAYER_HPP
#define ILAYER_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Properties.hpp"

class ILayer : public Properties, public sf::Transformable
{
    public:
        typedef std::shared_ptr<ILayer> Ptr;

    public:
        ILayer();

        virtual void render(sf::RenderTarget& target, sf::RenderStates states);

        virtual std::string getName() const;
        virtual void setName(std::string const& name);

        virtual int getX() const;
        virtual void setX(int x);

        virtual int getY() const;
        virtual void setY(int y);

        virtual float getOpacity() const;
        virtual void setOpacity(float opacity);

        virtual bool isVisible() const;
        virtual void setVisible(bool visible);

    protected:
        std::string mName;
        int mX;
        int mY;
        float mOpacity;
        bool mVisible;
};

#endif // ILAYER_HPP
