// Multi Index

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>


struct User
{
    int id;
    std::string name;
    int age;
};

int main()
{
    boost::multi_index::multi_index_container<
            User,
            boost::multi_index::indexed_by<
                    boost::multi_index::hashed_unique<
                            boost::multi_index::member<
                                    User, int, &User::id
                            >
                    >,
                    boost::multi_index::hashed_non_unique<
                            boost::multi_index::member<
                                    User, std::string, &User::name
                            >
                    >,
                    boost::multi_index::hashed_non_unique<
                            boost::multi_index::member<
                                User, int, &User::age
                            >
                    >
            >
    > staff;

    staff.insert({0, "root", 32});
    staff.insert({0, "sergey", 32});
    staff.insert({1, "oleg", 23});
    staff.insert({2, "andrew", 19});

    auto &index_by_id = staff.get<0>();
    std::cout << index_by_id.count(0) << std::endl;

    auto &index_by_age = staff.get<2>();
    std::cout << index_by_age.count(32) << std::endl;

    auto &index_by_name = staff.get<1>();
    auto iter = index_by_name.find("oleg");
    if (iter != index_by_name.end()) {
        std::cout << "Found!\nid = " << iter->id << "\nname = " << iter->name << "\nage = " << iter->age << std::endl;
    }

    return 0;
}
