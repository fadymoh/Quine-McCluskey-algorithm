#ifndef binary_format_hpp
#define binary_format_hpp

#include <stdio.h>
#include <string>
using namespace std;
class binary_format{
public:
    binary_format();
    ~binary_format();
    void add_binary(int, int, bool);
    void get_binary(string&);
    bool get_status();
    bool count_stars(int);
    void set_status(bool);
    int get_ones();
    int check_difference(binary_format&);
    void change_binary(binary_format, int);
    void print_binary();
    int get_size();
    int arr[16];
    int top;
    bool minterm[16];
    bool coveredepi[16];
    bool check_if_all_dontcares();
    int count_covered();
private:
    string binary;
    int count;
    bool check;
    void count_ones();
};



#endif /* binary_format_hpp */
