#ifndef SORT_H
#define SORT_H
#include <algorithm>
#include "types.h"

void sort(IpVector& ip_pool) {

	auto lexicographicalSortLambda = [](const IpAdress& left, const IpAdress& right) -> bool {
		return std::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end(),[](const uint8_t& left, const uint8_t& right){
			return left > right;
		});
	};
	std::sort(ip_pool.begin(), ip_pool.end(), lexicographicalSortLambda);
}


#endif
