#ifndef __PCV_CONFIGURE_H__
#define __PCV_CONFIGURE_H__

#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace pcv {

class ConfigVariantBase
{
public:
    typedef std::shared_ptr<ConfigVariantBase> ptr;

    ConfigVariantBase(const std::string &name, const std::string &description = "")
        : m_name(name), m_description(description)
    {
        std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
    }
    virtual ~ConfigVariantBase() = default;

    const std::string &name() const { return m_name; }
    const std::string &description() const { return m_description; }
    virtual std::string toString() = 0;
    virtual bool fromString(const std::string &str) = 0;
    virtual std::string typeName() const = 0;

protected:
    std::string m_name;
    std::string m_description;
};

template<class F, class T>
class LexicalCast
{
public:
    T operator()(const F &v) { return boost::lexical_cast<T>(v); }
};

/**
 * @brief 类型转换模板特例(YAML string 转 std::vector<T>)
 * 
 * @tparam T 
 */
template<class T>
class LexicalCast<std::string, std::vector<T>>
{
public:
    std::vector<T> operator()(const std::string &v)
    {
        YAML::Node node = YAML::Load(v);
        typename std::vector<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i)
        {
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }
};

template<class T>
class LexicalCast<std::vector<T>, std::string>
{
public:
    std::string operator()(const std::vector<T> &v)
    {
        YAML::Node node(YAML::NodeType::Sequence);
        for (auto &it: v) { node.push_back(YAML::Load(LexicalCast<T, std::string>()(it))); }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<class T>
class LexicalCast<std::string, std::list<T>>
{
public:
    std::list<T> operator()(const std::string &v)
    {
        YAML::Node node = YAML::Load(v);
        typename std::list<T> arr;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); i++)
        {
            ss.str("");
            ss << node[i];
            arr.push_back(LexicalCast<std::string, T>()(ss.str()));
        }
        return arr;
    }
};

template<class T>
class LexicalCast<std::list<T>, std::string>
{
public:
    std::string operator()(const std::list<T> &v)
    {
        YAML::Node node(YAML::NodeType::Sequence);
        for (auto &it: v) { node.push_back(YAML::Load(LexicalCast<T, std::string>()(it))); }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<class T>
class LexicalCast<std::string, std::set<T>>
{
public:
    std::set<T> operator()(const std::string &v)
    {
        YAML::Node node = YAML::Load(v);
        typename std::set<T> arr;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i)
        {
            ss.str("");
            ss << node[i];
            arr.insert(LexicalCast<std::string, T>()(ss.str()));
        }
        return arr;
    }
};

template<class T>
class LexicalCast<std::set<T>, std::string>
{
public:
    std::string operator()(const std::set<T> &v)
    {
        YAML::Node node(YAML::NodeType::Sequence);
        for (auto &it: v) { node.push_back(YAML::Load(LexicalCast<T, std::string>()(it))); }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<class T>
class LexicalCast<std::string, std::unordered_set<T>>
{
public:
    std::unordered_set<T> operator()(const std::string &v)
    {
        YAML::Node node = YAML::Load(v);
        typename std::unordered_set<T> arr;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i)
        {
            ss.str("");
            ss << node[i];
            arr.insert(LexicalCast<std::string, T>()(ss.str()));
        }
        return arr;
    }
};

template<class T>
class LexicalCast<std::unordered_set<T>, std::string>
{
public:
    std::string operator()(const std::unordered_set<T> &v)
    {
        YAML::Node node(YAML::NodeType::Sequence);
        for (auto &it: v) { node.push_back(YAML::Load(LexicalCast<T, std::string>()(it))); }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<class T>
class LexicalCast<std::string, std::map<std::string, T>>
{
public:
    std::map<std::string, T> operator()(const std::string &v)
    {
        YAML::Node node = YAML::Load(v);
        typename std::map<std::string, T> arr;
        std::stringstream ss;
        for (auto it = node.begin(); it != node.end(); ++it)
        {
            ss.str("");
            ss << it->second;
            arr.insert(std::make_pair(it->first.Scalar(), LexicalCast<std::string, T>()(ss.str())));
        }
        return arr;
    }
};

template<class T>
class LexicalCast<std::map<std::string, T>, std::string>
{
public:
    std::string operator()(const std::map<std::string, T> &v)
    {
        YAML::Node node(YAML::NodeType::Map);
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            node[it->first] = YAML::Load(LexicalCast<T, std::string>()(it->second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<class T>
class LexicalCast<std::string, std::unordered_map<std::string, T>>
{
public:
    std::unordered_map<std::string, T> operator()(const std::string &v)
    {
        YAML::Node node = YAML::Load(v);
        typename std::unordered_map<std::string, T> arr;
        std::stringstream ss;
        for (auto it = node.begin(); it != node.end(); ++it)
        {
            ss.str("");
            ss << it->second;
            arr.insert(std::make_pair(it->first.Scalar(), LexicalCast<std::string, T>()(ss.str())));
        }
        return arr;
    }
};

template<class T>
class LexicalCast<std::unordered_map<std::string, T>, std::string>
{
public:
    std::string operator()(const std::unordered_map<std::string, T> &v)
    {
        YAML::Node node(YAML::NodeType::Map);
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            node[it->first] = YAML::Load(LexicalCast<T, std::string>()(it->second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

/// @brief
/// @tparam T
template<class T, class FromStr = LexicalCast<std::string, T>,
         class ToStr = LexicalCast<T, std::string>>
class ConfigVariant : public ConfigVariantBase
{
public:
    typedef std::shared_ptr<ConfigVariant> ptr;
    typedef std::function<void(const T &old_val, const T &new_val)> change_callback;

    ConfigVariant(const std::string &name, const T &default_value,
                  const std::string &description = "")
        : ConfigVariantBase(name, description), m_value(default_value)
    {
    }

    std::string toString() override
    {
        try
        {
            return ToStr()(m_value);
        }
        catch (const std::exception &e)
        {
            SV_LOG_ERROR(SV_LOG_ROOT()) << "ConfigVariant::toString exception" << e.what()
                                        << " convert: " << typeToName<T>() << "to string"
                                        << " name=" << m_name;
        }
        return "";
    }

    bool fromString(const std::string &str) override
    {
        try
        {
            setValue(FromStr()(str));
            return true;
        }
        catch (const std::exception &e)
        {
            SV_LOG_ERROR(SV_LOG_ROOT())
                    << "ConfigVariant::fromString exception" << e.what() << " convert: string to"
                    << typeToName<T>() << " name=" << m_name << " - " << str;
        }
        return false;
    }
    const T value() { return m_value; }
    void setValue(const T &v) { m_value = v; }
    std::string typeName() const override { return typeToName<T>(); }

    uint64_t addListener(change_callback cb)
    {
        static uint64_t s_fun_id = 0;
        ++s_fun_id;
        m_callbacks[s_fun_id] = cb;
        return s_fun_id;
    }
    change_callback listener(uint64_t id)
    {
        auto it = m_callbacks.find(id);
        return it == m_callbacks.end() ? nullptr : it->second;
    }
    void clearListener() { m_callbacks.clear(); }

private:
    T m_value;
    std::map<uint64_t, change_callback> m_callbacks;
};


class Config
{
public:
    typedef std::unordered_map<std::string, ConfigVariantBase::ptr> ConfigVariantMap;

    template<class T>
    static typename ConfigVariant<T>::ptr lookup(const std::string &name, const T &default_value,
                                                 const std::string &description = "")
    {
        auto it = s_datas.find(name);
        if (it != s_datas.end())
        {
            auto tmp = std::dynamic_pointer_cast<ConfigVariant<T>>(it->second);
            if (tmp)
            {
                SV_LOG_INFO(SV_LOG_ROOT()) << "lookup name=" << name << " exists";
                return tmp;
            }
            else
            {
                SV_LOG_ERROR(SV_LOG_ROOT())
                        << "lookup name=" << name << " exists but type not match" << typeToName<T>()
                        << ", real type=" << it->second->typeName() << " "
                        << it->second->toString();
                return nullptr;
            }
        }
        constexpr auto match_string = "abcdefghijklmnopqrstuvwxyz._0123456789";
        if (name.find_first_not_of(match_string) != std::string::npos)
        {
            SV_LOG_ERROR(SV_LOG_ROOT()) << "lookup name invalid" << name;
            throw std::invalid_argument(name);
        }

        typename ConfigVariant<T>::ptr v(new ConfigVariant<T>(name, default_value, description));
        s_datas[name] = v;
        return v;
    }

    template<class T>
    static typename ConfigVariant<T>::ptr lookup(const std::string &name)
    {
        auto it = s_datas.find(name);
        if (it == s_datas.end()) { return nullptr; }

        return std::dynamic_pointer_cast<ConfigVariant<T>>(it->second);
    }
    static void loadFromYaml(const YAML::Node &root);
    static void loadFromConfDir(const std::string &path, bool force = false);
    static ConfigVariantBase::ptr lookupBase(const std::string &name);
    static void visit(std::function<void(ConfigVariantBase::ptr)> var);

private:
    static ConfigVariantMap s_datas;
};

}// namespace pcv

#endif//__PCV_CONFIGURE_H__