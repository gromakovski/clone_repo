// Посредник (Mediator)

#include <iostream>
#include <map>
#include <set>
#include <string>

enum class Role {
    user, admin
};

struct User {
    std::string name;
    Role role;   // It is a mediator
};

class Permissions
{
    std::map<std::string, Role> ops = {
        {"drop", Role::admin},  
        {"create", Role::admin},
        {"select", Role::user}
    };

public:
    bool isPermit(const std::string &op, Role role)
    {
        auto i = ops.find(op);
        if (i != std::end(ops)) {
            return i->second == role;
        }
        return false;
    }
};

int main(int, char *[])
{
    Permissions perm;

    auto v = User{"Vasia", Role::user};
    auto p = User{"Petia", Role::admin};

    std::cout << perm.isPermit("drop", v.role) << std::endl;
    std::cout << perm.isPermit("drop", p.role) << std::endl;

    return 0;
}
