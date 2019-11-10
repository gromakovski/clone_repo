// Fusion
// https://theboostcpplibraries.com/boost.fusion

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/view.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>

struct SomeStruct {
    int i;
    const char * s;
    double d;
    int j;
};

BOOST_FUSION_ADAPT_STRUCT(SomeStruct,
    (int, i)
    (const char *, s)
    (double, d)
    (int, j)
);

int main() {
    // Just get values
    SomeStruct s = {10, "Hello, world!", 3.14, 42};
    std::cout << "indexes:\n";
    std::cout << boost::fusion::front(s) << std::endl;
    std::cout << boost::fusion::at<boost::mpl::int_<1>>(s) << std::endl;
    std::cout << boost::fusion::back(s) << std::endl;
    std::cout << std::endl;

    // Basic for_each
    std::cout << "for_each:\n";
    boost::fusion::for_each(s, [](auto value) { std::cout << value << std::endl; });
    std::cout << std::endl;

    // Integral view
    boost::fusion::filter_view<
      SomeStruct, 
      boost::is_integral<
        boost::mpl::arg<1>
      >
    > integral_view{s};

    std::cout << "integral_view:\n";
    boost::fusion::for_each(integral_view, [](auto value) { std::cout << value << std::endl; });
    std::cout << std::endl;

    // const char * view
    boost::fusion::filter_view<
        SomeStruct, 
        boost::is_same<
            boost::mpl::arg<1>, const char *
        >
    > cchar_view{s};

    std::cout << "cchar_view:\n";
    boost::fusion::for_each(cchar_view, [](auto value) { std::cout << value << std::endl; });
    std::cout << std::endl;


    // Iterators
    std::cout << "iterators:\n";
    auto iter = boost::fusion::begin(s);
    std::cout << *iter << std::endl;

    auto iter2 = boost::fusion::advance<boost::mpl::int_<2>>(iter);
    std::cout << *iter2 << std::endl;  	

    // Out of range. Compile error
    // auto wrongIter = boost::fusion::advance<boost::mpl::int_<2>>(iter2);
    // std::cout << *wrongIter << std::endl;  		
    std::cout << std::endl;

    std::cout << "pair:\n";
    auto pair = std::make_pair(10, "42");
    std::cout << boost::fusion::at<boost::mpl::int_<0>>(pair) << std::endl;
    std::cout << boost::fusion::at<boost::mpl::int_<1>>(pair) << std::endl;
    std::cout << std::endl;

    std::cout << "tuple:\n";
    auto tuple = std::make_tuple(10, "42", "tuple");
    boost::fusion::for_each(tuple, [](auto value) { std::cout << value << std::endl; });
    std::cout << std::endl;


    return 0;
}
