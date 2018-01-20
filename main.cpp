#include "print_ip.h"
#include "CustomAllocator.h"

int main(int argc, char *argv[])
{
    std::ostringstream os;
    std::vector<int, CustomAllocator<int> > vec;
    vec.push_back(123);
    vec.push_back(2);
    vec.push_back(777);
    std::list<int> list;
    list.push_back(13);
    list.push_back(11);
    list.push_back(44);
    std::string str = "127.0.0.1";

    std::tuple<int, int, int, int> tup(198, 162, 0, 1);

    int i = 900000000;
    float f;
    char c;

    print_ip(i, os);
//    print_ip(c, os);
    print_ip(str, os);
    print_ip(list, os);
    print_ip(vec, os);
//    print_ip(tup, os);
    std::cout << os.str();
    return 0;
}
