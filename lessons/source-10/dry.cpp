#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


#pragma region (Evident)
void getConfiguration(const std::string& path) {
    const std::string pathToMainConfig = 
        path + "/conf/main.conf";

    const std::string pathToConnectionConfig = 
        path + "/conf/connection.conf";

    const std::string pathToUIConfig = 
        path + "/conf/UI.conf";

    // do something with pathToMainConfig
    // do something with pathToConnectionConfig
    // do something with pathToUIConfig
}
#pragma endregion


#pragma region (Homework)
void ip_filter() {

    using IP = std::vector<uint8_t>;
    using IPList = std::vector<IP>;

    IPList sourceIPList; // = readFromStream

    // sorting
    // std::sort(sourceIPList.begin(), sourceIPList.end());
    for (auto& ip : sourceIPList) {
        for(auto iter = ip.begin(); iter != ip.end(); ++iter) {
            if (iter != ip.begin())
                std::cout << '.';
            std::cout << *iter;
        }
        std::cout << std::endl;
    }

    // first filtration
    // filter_by_first(sourceIPList, 1);
     for (auto& ip : sourceIPList) {
        for(auto iter = ip.begin(); iter != ip.end(); ++iter) {
            if (iter != ip.begin())
                std::cout << '.';
            std::cout << *iter;
        }
        std::cout << std::endl;
    }

    // second filtration
    // ...   

}
#pragma endregion

int main() {
    getConfiguration("/dev/null");
    ip_filter();
    return 0;
}