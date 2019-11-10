// Fusion
// Hana, MPL

#include <iostream>

#include <boost/fusion/tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/iterator.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits.hpp>
#include <iostream>
#include <string>
#include <tuple>


int main() {
    boost::fusion::tuple<int, float, std::string, long> ip{127, 1.0f, "0", 2};

    // Does not work with std::tuple
    // std::tuple<int, float, std::string, long> ip{127, 1.0f, "0", 2};

    std::cout << "for_each with tuple:" << std::endl;
    boost::fusion::for_each(ip, [](auto i) { std::cout << i << std::endl; });
    std::cout << std::endl;

    auto iter = boost::fusion::begin(ip);
    auto iter2 = boost::fusion::advance<boost::mpl::int_<2>>(iter);
    std::cout << "*iter = " << *iter << std::endl;
    std::cout << "*iter2 = " << *iter2 << std::endl;
    std::cout << std::endl;

    boost::fusion::filter_view<decltype(ip), boost::is_integral<boost::mpl::arg<1>>> view{ip};

    std::cout << "for_each with filter_view:" << std::endl;
    boost::fusion::for_each(view, [](auto i) { std::cout << i << std::endl; });
    std::cout << std::endl;

    return 0;
}
