// Bimap

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>


// This is a message type
enum class EType {
    Critical,
    Error,
    Warning,
    Debug
};

std::ostream& operator<<(std::ostream& os, const EType type) {
    os << static_cast<int>(type);
    return os;
}

struct Message {
    // many other fields
    EType type;
};


#pragma region (SwitchCase)
std::string typeToString_1(const EType type) {
    switch(type) {
        case EType::Critical:
            return "Critical";
        case EType::Error:
            return "Error";
        case EType::Warning:
            return "Warning";
        case EType::Debug:
            return "Debug";
        default:
            throw std::logic_error("No such type!");
    }
}

EType typeFromString_1(const std::string& type) {
    if (type == typeToString_1(EType::Critical))
        return EType::Critical;
    if (type == typeToString_1(EType::Error))
        return EType::Error;
    if (type == typeToString_1(EType::Warning))
        return EType::Warning;
    if (type == typeToString_1(EType::Debug))
        return EType::Debug;
    throw std::logic_error("No such type!");
}


void test_serialization_1() {
    Message msg;
    msg.type = EType::Warning;

    const std::string serialized = typeToString_1(msg.type) /*+ otherFields*/;
}

void test_deserialization_1() {
    Message msg;
    const std::string serialized = "Critical";
    msg.type = typeFromString_1(serialized);
}
#pragma endregion (SwitchCase)



#pragma region (Map)

const std::map<EType, std::string> typeNamesMap = {
    {EType::Critical, "Critical"},
    {EType::Error, "Error"},
    {EType::Warning, "Warning"},
    {EType::Debug, "Debug"}
};

const std::string& typeToString_2(const EType type) {
    auto iter = typeNamesMap.find(type);
    if (iter == typeNamesMap.end())
        throw std::logic_error("No such type!");
    return iter->second;
}

EType typeFromString_2(const std::string& type) {
    if (type == typeToString_2(EType::Critical))
        return EType::Critical;
    if (type == typeToString_2(EType::Error))
        return EType::Error;
    if (type == typeToString_2(EType::Warning))
        return EType::Warning;
    if (type == typeToString_2(EType::Debug))
        return EType::Debug;
    throw std::logic_error("No such type!");
}

#pragma endregion (Map)


#pragma region (Bimap)

// Compile error - no initializer-list constructor :(
// const boost::bimap<EType, std::string> typeNamesBimap = {
//     {EType::Critical, "Critical"},
//     {EType::Error, "Error"},
//     {EType::Warning, "Warning"},
//     {EType::Debug, "Debug"}
// };


// Make it!
template <typename L, typename R>
boost::bimap<L, R>
makeBimap(std::initializer_list<typename boost::bimap<L, R>::value_type> list)
{
    return boost::bimap<L, R>(list.begin(), list.end());
}

const boost::bimap<EType, std::string> typeNamesBimap = makeBimap<EType, std::string>({
    {EType::Critical, std::string("Critical")},
    {EType::Error, std::string("Error")},
    {EType::Warning, std::string("Warning")},
    {EType::Debug, std::string("Debug")}
});

const std::string& typeToString_3(const EType type) {
    auto iter = typeNamesBimap.left.find(type);
    if (iter == typeNamesBimap.left.end())
        throw std::logic_error("No such type!");
    return iter->second;
}

EType typeFromString_3(const std::string& type) {
    auto right = typeNamesBimap.right;
    auto iter = typeNamesBimap.right.find(type);
    if (iter == typeNamesBimap.right.end())
        throw std::logic_error("No such type!");
    return iter->second;
}

void testBimap() {
    std::cout << "EType::Critical = " << EType::Critical << " <-> " << typeToString_3(EType::Critical) << std::endl;
    std::cout << "Warning <-> EType::Warning = " << typeFromString_3("Warning") << std::endl;
}

#pragma endregion(Bimap)



void test_words() {
    boost::bimap<
            boost::bimaps::multiset_of<std::string>,
            std::string
    > translation;

    translation.insert({"Word1", "translation_1_1"});
    translation.insert({"Word1", "translation_1_2"});
    translation.insert({"Word1", "translation_1_3"});

    translation.insert({"Word2", "translation_2_1"});

    translation.insert({"Word3", "translation_3_1"});

    for (auto& word : translation) {
        std::cout << word.left << " - " << word.right << std::endl;
    }
    std::cout << std::endl;

    auto i = translation.left.find("Word3");
    std::cout << i->first << " -> " << i->second << std::endl;

    auto pair = translation.left.equal_range("Word1");
    for(auto k = pair.first; k != pair.second; ++k)
        std::cout << k->second << std::endl;

}


int main() {
    testBimap();

    std::cout << std::endl;

    test_words();

    return 0;
}
