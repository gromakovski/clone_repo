#include <iostream>


int main(int argc, char const *argv[])
{	
	constexpr short tasksPer5Hours = 12;
	constexpr short tasksPer4Hours = 4.0 / 0.75;
	short  tasksPer1Hours;
	std::cin >> tasksPer1Hours;

	short remainingTasks = tasksPer5Hours - tasksPer1Hours - tasksPer4Hours;
	if (remainingTasks <= 0)
		std::cout << "YES" << "\n";
	else
		std::cout << "NO" << "\n";

	return 0;
}
