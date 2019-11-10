#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <tuple>

#include "split.h"
#include "sort.h"
#include "filter.h"

//Run/executable              cat
//Run/Command Line Arguments ../homework2/ip.tsv | ./ip_filter > out.tsv


int main(int argc, char const *argv[])
{
	//Lambdas
	auto outputLambda = [](const IpVector& ip_pool){
		for(const auto& ip : ip_pool)
		{
			auto it = std::begin(ip); //приходиться запоминать итератор на начало списка, а потом приращивать его в цикле
									  //для того чтобы иметь возможность доступа по индексу (может лучше использовать обычный for в данном случае?)
			for(auto ip_part : ip)
			{
				if (it != ip.cbegin())
					std::cout << ".";
				std::cout << static_cast<int>(ip_part); //static_cast<int> нужен для того чтобы в поток вывода выводились числа а не иероглифы
				it++;
			}
			std::cout << std::endl;
		}
	};



	//Code
    try
    {
		IpVector ip_pool;

		for(std::string line; std::getline(std::cin, line);)
		{
			std::vector<std::string> v{split(line, '\t')};          //отделяем часть строки с айпи адресом
			std::vector<std::string> ip = split(v.at(0), '.');


			ip_pool.push_back(IpAdress{static_cast<uint8_t>(std::stoi(ip.at(0))),
									   static_cast<uint8_t>(std::stoi(ip.at(1))),
									   static_cast<uint8_t>(std::stoi(ip.at(2))),
									   static_cast<uint8_t>(std::stoi(ip.at(3))),
							  });  //разбиваем айпи адрес на вектор байт (каждая содержит часть адреса)
		}


		//reverse lexicographically sort
		sort(ip_pool);
		outputLambda(ip_pool);

		//filter by first byte and output
		IpVector ip_pool_filtered= filter(ip_pool, 1);
		outputLambda(ip_pool_filtered);

		//filter by first and second bytes and output
		ip_pool_filtered = filter(ip_pool, 46, 70);
		outputLambda(ip_pool_filtered);

		//filter by any byte and output
		ip_pool_filtered = filter_any(ip_pool, 46);
		outputLambda(ip_pool_filtered);

		//filterT
//		std::cout << "filterT" << std::endl;
//		ip_pool_filtered = filterT(ip_pool, "5");
//		outputLambda(ip_pool_filtered);
//		ip_pool_filtered = filterT(ip_pool, "46", "70");
//		outputLambda(ip_pool_filtered);
		//outputLambda(ip_pool_filtered);


    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}




//
// ip = filter(1)

// 1.231.69.33
// 1.87.203.225
// 1.70.44.170
// 1.29.168.152
// 1.1.234.8

// TODO filter by first and second bytes and output
// ip = filter(46, 70)

// 46.70.225.39
// 46.70.147.26
// 46.70.113.73
// 46.70.29.76

// TODO filter by any byte and output
// ip = filter_any(46)

// 186.204.34.46
// 186.46.222.194
// 185.46.87.231
// 185.46.86.132
// 185.46.86.131
// 185.46.86.131
// 185.46.86.22
// 185.46.85.204
// 185.46.85.78
// 68.46.218.208
// 46.251.197.23
// 46.223.254.56
// 46.223.254.56
// 46.182.19.219
// 46.161.63.66
// 46.161.61.51
// 46.161.60.92
// 46.161.60.35
// 46.161.58.202
// 46.161.56.241
// 46.161.56.203
// 46.161.56.174
// 46.161.56.106
// 46.161.56.106
// 46.101.163.119
// 46.101.127.145
// 46.70.225.39
// 46.70.147.26
// 46.70.113.73
// 46.70.29.76
// 46.55.46.98
// 46.49.43.85
// 39.46.86.85
// 5.189.203.46
