#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

//cat
//../1001/test_in.txt | ./1001


int main(int argc, char const *argv[])
{
	std::vector<double>  numbersList;
	long long d;
	while (std::cin >> d)
	{
		numbersList.push_back(d);
	}



	std::cout << std::fixed << std::setprecision(4) ;
	for (auto it = numbersList.rbegin(); it!= numbersList.rend(); it++) {
		double num = *it;
		num = std::sqrt(static_cast<double>(*it));

		std::cout   << num << "\n";
	}
    return 0;
}
