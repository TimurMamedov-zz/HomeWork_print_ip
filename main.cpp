#include "print_ip.h"

int main(int argc, char *argv[])
{
    std::vector<int> vec;
    std::list<int> list;
    std::string str;

    std::tuple<int, int, ints> tup(0, 1, 2);

    int i;
    float f;
    char c;

    print_ip(i);
    print_ip(c);
    print_ip(str);
    print_ip(list);
    print_ip(vec);
    print_ip(tup);
    return 0;
}
