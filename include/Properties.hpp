#ifndef TME_PROPERTIES_HPP
#define TME_PROPERTIES_HPP

#include <map>
#include <string>
#include <sstream>

class Properties
{
    public:
        Properties();

        int getInt(std::string const& name);
        float getFloat(std::string const& name);
        std::string getString(std::string const& name);
        bool getBool(std::string const& name);
        std::map<std::string,std::string> getProperties() const;

        bool hasProperty(std::string const& name) const;
        bool isEmpty() const;

        void setProperty(std::string const& name, int value);
        void setProperty(std::string const& name, float value);
        void setProperty(std::string const& name, std::string value);
        void setProperty(std::string const& name, bool value);
        void setProperties(std::map<std::string,std::string> properties);

    private:
        std::map<std::string,std::string> mProperties;
};

#endif // TME_PROPERTIES_HPP
