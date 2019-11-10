// Flyweight
// https://theboostcpplibraries.com/boost.flyweight

#include <string>
// #include <string_view>
#include <vector>
#include <utility>

#include <boost/flyweight.hpp>

struct Person {
	Person(int i, const std::string& c) 
		: id{i}, city{c} {

	}
	
	int id;
	std::string city;
};

void motivation() {
	std::vector<Person> persons;
	// for (int i = 0; i < 1000000; ++i)
	for (int i = 0; i < 1000; ++i)
		persons.emplace_back(i, "City");

	// 1000000 "City"
	// 1000000 person
}


#pragma region (Solution)
struct LightPerson {
	// LightPerson(int i, std::string_view c)	
	// : id{i}, city{c} {
	LightPerson(int i, const char *c)
		: id{i}, city{c} {
	}

	int id;
	boost::flyweights::flyweight<std::string> city;
};

void test_solution() {
	std::vector<LightPerson> persons;
	for (int i = 0; i < 1000; ++i) 
		persons.emplace_back(i, "City");
}
#pragma endregion


#pragma region (SameContainer)
struct LightPersonWithCountry {
	LightPersonWithCountry(int i, const char *ci, const char *co)
		: id{i}, city{ci}, country{co} {
	}

	int id;
	// Both city and country are in the same hash-map
	boost::flyweights::flyweight<std::string> city;
	boost::flyweights::flyweight<std::string> country;
};

void test_solution2() {
	std::vector<LightPersonWithCountry> persons;
	for (int i = 0; i < 1000; ++i) 
		persons.emplace_back(i, "City", "Country");
}
#pragma endregion



#pragma region (DifferentContainers)
struct LightPersonWithCountry2 {
private:
	struct city_t {};
	struct country_t {};

public:
	LightPersonWithCountry2(int i, const char *ci, const char *co)
		: id{i}, city{ci}, country{co} {
	}

	int id;
	boost::flyweights::flyweight<std::string, boost::flyweights::tag<city_t>> city;
	boost::flyweights::flyweight<std::string, boost::flyweights::tag<country_t>> country;
};

void test_solution3() {
	std::vector<LightPersonWithCountry2> persons;
	for (int i = 0; i < 1000; ++i) 
		persons.emplace_back(i, "City", "Country");
}
#pragma endregion


int main() {

	// motivation();
	test_solution();
	test_solution2();
	test_solution3();

	return 0;
}