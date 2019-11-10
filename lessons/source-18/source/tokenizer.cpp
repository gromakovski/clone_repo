// Tokenizer

#include <boost/tokenizer.hpp>
#include <iostream>
#include <string>

int main()
{
    const std::string ip = "127.0.0.1";

    boost::tokenizer<boost::char_separator<char>>
            tokenizer{ip, boost::char_separator<char>{"."}};

    for (auto &i: tokenizer) {
        std::cout << i << std::endl;
    }

    return 0;
}
