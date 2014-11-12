#include "../include/Properties.hpp"

////////////////////////////////////////////////////////////
Properties::Properties()
{
}

////////////////////////////////////////////////////////////
int Properties::getInt(std::string const& name)
{
    return toNumber(mProperties[name]);
}

////////////////////////////////////////////////////////////
float Properties::getFloat(std::string const& name)
{
    return toNumber(mProperties[name]);;
}

////////////////////////////////////////////////////////////
std::string Properties::getString(std::string const& name)
{
    return mProperties[name];
}

////////////////////////////////////////////////////////////
bool Properties::getBool(std::string const& name)
{
    return toBool(mProperties[name]);
}

////////////////////////////////////////////////////////////
std::map<std::string,std::string> Properties::getProperties() const
{
    return mProperties;
}

////////////////////////////////////////////////////////////
bool Properties::hasProperty(std::string const& name) const
{
    return mProperties.find(name) != mProperties.end();
}

////////////////////////////////////////////////////////////
bool Properties::isEmpty() const
{
    return mProperties.empty();
}

////////////////////////////////////////////////////////////
void Properties::setProperty(std::string const& name, int value)
{
    mProperties[name] = toString<int>(value);
}

////////////////////////////////////////////////////////////
void Properties::setProperty(std::string const& name, float value)
{
    mProperties[name] = toString<float>(value);
}

////////////////////////////////////////////////////////////
void Properties::setProperty(std::string const& name, std::string value)
{
    mProperties[name] = value;
}

////////////////////////////////////////////////////////////
void Properties::setProperty(std::string const& name, bool value)
{
    mProperties[name] = toString(value);
}

////////////////////////////////////////////////////////////
void Properties::setProperties(std::map<std::string,std::string> properties)
{
    mProperties = properties;
}

////////////////////////////////////////////////////////////
bool Properties::toBool(std::string const& value)
{
    (value == "true") ? return true : return false;
}

////////////////////////////////////////////////////////////
std::string Properties::toString(bool boolean)
{
    (boolean) ? return "true" : return "false";
}

