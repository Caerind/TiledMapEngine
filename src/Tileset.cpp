#include "../include/Tileset.hpp"
#include "../include/Map.hpp"

Tileset::Tileset(Map* map)
{
    if (map != nullptr)
    {
        mMap = map;
    }
}


