#include "protobuf.pb.h"

#include <fstream>


int main(int, char *[]) {
    tutorial::AddressBook address_book;

    auto person = address_book.add_people();
    person->set_id(1);
    person->set_name("admin");
    person->set_email("admin@example.com");


    std::fstream output("protobuf.dat", std::ios::out | std::ios::trunc | std::ios::binary);
    address_book.SerializeToOstream(&output);


    std::fstream input("protobuf.dat", std::ios::in | std::ios::binary);
    address_book.ParseFromIstream(&input);

    for (int i = 0; i < address_book.people_size(); i++) {
        const auto &person = address_book.people(i);

        std::cout << "id: " << person.id() << std::endl;
        std::cout << "name: " << person.name() << std::endl;
        if (person.has_email()) {
            std::cout << "email: " << person.email() << std::endl;
        }
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}