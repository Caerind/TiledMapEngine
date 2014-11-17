#ifndef ILAYER_HPP
#define ILAYER_HPP

#include <memory>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Properties.hpp"

class ILayer : public Properties
{
    public:
        typedef std::shared_ptr<ILayer> Ptr;

    public:
        ILayer();

        virtual void render(sf::RenderTarget& target, sf::RenderStates states) = 0;
};

#endif // ILAYER_HPP
