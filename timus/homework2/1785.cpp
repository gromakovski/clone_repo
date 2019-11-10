
#include <iostream>
#include <map>
#include <algorithm>

//решение нацелено на расширяемость в sizes можно добавлять данные в рантайме например из xml
struct Size {
	Size(short from, short to) : from_(from), to_(to) {}
	short from_ = 1;
	short to_ = 5;
};


const std::map<std::string, Size> sizes = {
	{"few", Size{1, 4}},
	{"several", Size{5, 9}},
	{"pack", Size{10, 19}},
	{"lots", Size{20, 49}},
	{"horde", Size{50, 99}},
	{"throng", Size{100, 249}},
	{"swarm", Size{250, 499}},
	{"zounds", Size{500, 999}},
	{"legion", Size{1000, 2000}},

};

int main(int argc, char const *argv[])
{	
	short numberOfMonsters;
	std::cin >> numberOfMonsters;

	auto it = std::find_if( sizes.begin(), sizes.end(),[&numberOfMonsters]
							(const std::pair<std::string, Size>& v) -> bool
	{
		if ((numberOfMonsters >= v.second.from_) &&  (numberOfMonsters <= v.second.to_))
			return true;
		else
			return false;
	} );


	std::cout << (*it).first << std::endl;
	return 0;
}
