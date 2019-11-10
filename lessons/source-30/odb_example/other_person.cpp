#include "other_person.hxx"

other_person::other_person() {

}

const std::string& other_person::email () const {
	return email_;
}

void other_person::email (const std::string& email) {
	email_ = email;
}

const std::string& other_person::get_name () const {
	return name_;
}

std::string& other_person::set_name () {
	return name_;
}

unsigned short other_person::getAge () const {
	return age_;
}

void other_person::setAge (unsigned short age) {
	age_ = age;
}

