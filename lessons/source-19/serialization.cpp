
#include <iostream>
#include <string>

#include <boost/mpl/range_c.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/mpl.hpp>

namespace fusion=boost::fusion;
namespace mpl=boost::mpl;

struct  MyStructType
{
    double val1;
    double val2;
    char letter;
    int number;
}; 

BOOST_FUSION_ADAPT_STRUCT(
    MyStructType,
    (double, val1)
    (double, val2)
    (char, letter)
    (int, number)
)   



template <typename Sequence>
struct XmlFieldNamePrinter
{
    XmlFieldNamePrinter(const Sequence& seq)
        :seq_(seq) {

        }
    template <typename Index>
    void operator() (Index idx) const
    {
        const std::string field_name = 
            fusion::extension::struct_member_name<Sequence, Index::value>::call();

        std::cout
            << '<' << field_name << '>'
            << fusion::at<Index>(seq_)
            << "</" << field_name << '>'
            ;
    }
private:
    const Sequence& seq_;
};
template<typename Sequence>
void printXml(Sequence const& v)
{
    typedef mpl::range_c<unsigned, 0, fusion::result_of::size<Sequence>::value > Indices; 
    fusion::for_each(Indices(), XmlFieldNamePrinter<Sequence>(v));
}

int main()
{
    MyStructType saveMe = { 3.4, 5.6, 'g', 9};
    printXml(saveMe);
}

