#ifndef FILTER_H
#define FILTER_H

#include "types.h"
#include <algorithm>

IpVector filter(const IpVector& vec, uint8_t first)
{
	auto filterLambda = [&first](const IpAdress& adress){
		if (adress.at(0) == first)
			return true;
		else
			return false;
	};
	IpVector ip_pool_filtered;
	std::copy_if(vec.begin(), vec.end(), std::back_inserter(ip_pool_filtered),
	filterLambda);
	return ip_pool_filtered;
}

IpVector filter(const IpVector& vec, uint8_t first, uint8_t second)
{
	auto filterLambda = [&first, &second](const IpAdress& adress){
		if (adress.at(0) == first && adress.at(1) == second)
			return true;
		else
			return false;
	};
	IpVector ip_pool_filtered;
	std::copy_if(vec.begin(), vec.end(), std::back_inserter(ip_pool_filtered),
	filterLambda);
	return ip_pool_filtered;
}

IpVector filter_any(const IpVector& vec, uint8_t any)
{
	auto filterLambda = [&any](const IpAdress& adress){
		for (auto byte : adress) {
			if (byte == any)
				return true;
		}
			return false;
	};
	IpVector ip_pool_filtered;
	std::copy_if(vec.begin(), vec.end(), std::back_inserter(ip_pool_filtered),
	filterLambda);
	return ip_pool_filtered;
}


////фозвращает адрес если в его разрядах присутствуют байты перечисленные в  parms
//template <typename ... T>
//IpVector filterT(const IpVector& vec, T ... parms)
//{
//	auto filterLambda = [parms...](const IpAdress& val){
//	//bool result = false;

//	int paramId = 0;
//	for (auto&& x : { parms... }) {
//		bool result = (val.at(paramId) == x);
//		if (!result)
//			return false;
//		paramId++;
//		}

//	return true;
//	};

//	IpVector ip_pool_filtered_by_first;
//	std::copy_if(vec.begin(), vec.end(), std::back_inserter(ip_pool_filtered_by_first),
//	filterLambda);
//	return ip_pool_filtered_by_first;

//}

#endif
