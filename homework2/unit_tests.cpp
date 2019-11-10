#include <string>
#include <fstream>
#include <iostream>

#include "split.h"
#include "sort.h"
#include "filter.h"

//add custom build step
//command - ctest
//arguments -VV


#include <gtest/gtest.h>
namespace {
class Test1 : public ::testing::Test
{
public:
	void SetUp() override {
		std::ifstream infile("ip.tsv");
		for(std::string line; std::getline(infile, line);)
		{
			std::vector<std::string> v{split(line, '\t')};          //отделяем часть строки с айпи адресом
			std::vector<std::string> ip = split(v.at(0), '.');

			ip_pool.push_back(IpAdress{static_cast<uint8_t>(std::stoi(ip.at(0))),
									   static_cast<uint8_t>(std::stoi(ip.at(1))),
									   static_cast<uint8_t>(std::stoi(ip.at(2))),
									   static_cast<uint8_t>(std::stoi(ip.at(3))),
							  });  //разбиваем айпи адрес на вектор байт (каждая содержит часть адреса)
		}
		sort(ip_pool);
	}
	IpVector ip_pool;
};


TEST_F(Test1, filterOne )
{
	IpVector filteredexcepted{
		{1,231,69,33},
		{1,87,203,225},
		{1,70,44,170},
		{1,29,168,152},
		{1,1,234,8}
	};
	EXPECT_TRUE(filteredexcepted == filter(ip_pool, 1));
}

TEST_F(Test1, filterTwo )
{
	IpVector filteredexcepted{
		{46,70,225,39},
		{46,70,147,26},
		{46,70,113,73},
		{46,70,29,76}
	};
	EXPECT_TRUE((filteredexcepted == filter(ip_pool, 46, 70)));
}

TEST_F(Test1, sort )
{
	IpVector ip_pool{
		{1,29,168,152},
		{185,69,186,168},
		{166,88,193,116},
		{185,70,193,116}
	};
	IpVector reversSortedexcepted{
		{185,70,193,116},
		{185,69,186,168},
		{166,88,193,116},
		{1,29,168,152}
	};

	sort(ip_pool);
	EXPECT_TRUE(reversSortedexcepted == ip_pool);
}


//Тесты по технологии  DDT в интерпретации гугла называются Value-Parameterized Tests
//наследуем его от шаблонного класса параметризованного типом в котором будут содержаться тестовые параметры
//Тестовые случаи храним в std::vector так как его принимает функция ValuesIn
//Для тестирования функции split(..)  нам для каждого тестового случая нужен тип
//std::tuple<std::string, std::vector<std::string>> (где 1 элемент тапла исхолдная строка , 2 элемент ожидаемый рез-т )
class Test2 :
		public ::testing::TestWithParam<::std::tuple<std::string, std::vector<std::string>> > {
  // You can implement all the usual fixture class members here.
  // To access the test parameter, call GetParam() from class
  // TestWithParam<T>.
};

using ::testing::Bool;
using ::testing::Values;
using ::testing::ValuesIn;
using ::testing::Combine;

//Входные наборы данных для split
std::vector<std::tuple<std::string, std::vector<std::string>> > v{
	{"1.2.3.4", {{"1"},{"2"},{"3"},{"4"}}},
	{"11", {{"11"}}},
	{"..", {{""}, {""}, {""}}},
	{"11.", {{"11"}, {""}}},
	{".11", {{""}, {"11"}}},
	{"11.22", {{"11"}, {"22"}}},
};
INSTANTIATE_TEST_SUITE_P(InstantiationName,
												Test2,
												 ValuesIn(v));

TEST_P(Test2, split) {
	std::string input;
	std::vector<std::string> splittedExcepted;
	std::tie(input, splittedExcepted) = GetParam();
	std::vector<std::string> splitted = split(input, '.');
	EXPECT_EQ(splittedExcepted, splitted);
}



}  // namespace
