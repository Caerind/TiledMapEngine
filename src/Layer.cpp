#include "../include/Layer.hpp"
#include "../include/Map.hpp"

Layer::Layer(Map* map)
{
    if (map != nullptr)
    {
        mMap = map;
    }
}
