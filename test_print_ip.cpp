#define BOOST_TEST_MODULE print_ip_test

#include <boost/test/unit_test.hpp>
#include "print_ip.h"

#include "version.h"

BOOST_AUTO_TEST_CASE(version_test)
{
    BOOST_CHECK( version() > 0 );
}

BOOST_AUTO_TEST_SUITE(Test_PRINT_IP)

BOOST_AUTO_TEST_CASE(test_integral_print_ip)
{
    std::ostringstream os;

    std::string str_char("255\n");
    std::string str_short("0.0\n");
    std::string str_int("127.0.0.1\n");
    std::string str_long("123.45.67.89.101.112.131.41\n");
    char c(-1);
    short s(0);
    int i(2130706433);
    long l(8875824491850138409);

    print_ip(c, os);
    BOOST_CHECK( os.str() == str_char);
    os.str("");

    print_ip(s, os);
    BOOST_CHECK( os.str() == str_short);
    os.str("");

    print_ip(i, os);
    BOOST_CHECK( os.str() == str_int);
    os.str("");

    print_ip(l, os);
    BOOST_CHECK( os.str() == str_long);
}

BOOST_AUTO_TEST_CASE(test_container_print_ip)
{
    std::ostringstream os;

    std::vector<int> vec{123, 2, 777};
    std::list<int> list({13, 11, 44, 55, 66});

    std::string str_vec("123.2.777\n");
    std::string str_list("13.11.44.55.66\n");

    print_ip(vec, os);
    BOOST_CHECK( os.str() == str_vec);
    os.str("");

    print_ip(list, os);
    BOOST_CHECK( os.str() == str_list);
}

BOOST_AUTO_TEST_CASE(test_tuple_print_ip)
{
    std::ostringstream os;

    std::tuple<int, int, int, int> tup(198, 162, 0, 1);

    std::string str_tup("198.162.0.1\n");

    print_ip(tup, os);
    BOOST_CHECK( os.str() == str_tup);
}

BOOST_AUTO_TEST_SUITE_END()
