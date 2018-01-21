#include "print_ip.h"

int main(int argc, char *argv[])
{
    std::ostringstream os;

    char c(-1);
    short s(0);
    int i(2130706433);
    long l(8875824491850138409);

    std::string str = "127.0.0.1";

    std::vector<int> vec{123, 2, 777};
    std::list<int> list({13, 11, 44, 55, 66});

    std::tuple<int, int, int, int> tup(198, 162, 0, 1);

    print_ip(c, os);
    print_ip(s, os);
    print_ip(i, os);
    print_ip(l, os);

    print_ip(str, os);

    print_ip(vec, os);
    print_ip(list, os);

    print_ip(tup, os);
    std::cout << os.str();
    return 0;
}
