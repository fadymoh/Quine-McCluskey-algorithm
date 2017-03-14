#include "binary_format.hpp"
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
binary_format::binary_format()
{
    binary = "0000000000000000";
    count = 0;
    check = false;
    top = 0;
}
void binary_format::add_binary(int x, int number_of_variables, bool isminterms)
{
    int d, counter;
    counter = number_of_variables - 1;
    arr[top] = x;
    minterm[top] = isminterms;
    top++;
    while (x != 0)
    {
        d = x % 2;
        binary.at(counter) = char(d + '0');
        x /= 2;
        counter--;
    }
    
    binary.erase(number_of_variables, 15);
    count_ones();
}
bool binary_format::get_status()
{
    return check;
}
int binary_format::get_ones()
{
    return count;
}
void binary_format::get_binary(string& val)
{
    val = binary;
}
void binary_format::set_status(bool status)
{
    check = status;
}
binary_format::~binary_format()
{
}
void binary_format::count_ones()
{
    count = 0;
    for (int i = 0; i < binary.length(); i++)
    {
        char d = binary[i];
        if (d == '1')
            count++;
    }
}
int binary_format::check_difference(binary_format& x)
{
    int count_differences = 0;
    int save_index=0;
    string temp1 = binary;
    string temp2;
    char first;
    char second;
    x.get_binary(temp2);
    for (int i = 0; i < temp1.length(); i++)
    {
        first = temp1[i];
        second = temp2[i];
        if (first != second)
        {
            save_index = i;
            count_differences++;
        }
    }
    if (count_differences > 1)
        save_index = -1;
    return save_index;
}
void binary_format::change_binary(binary_format bin, int index)
{
    string x;
    bin.get_binary(x);
    x.replace(index, 1, "*");
    binary = x;
    count_ones();
}
void binary_format::print_binary()
{
    cout << binary << endl;
}
int binary_format::get_size()
{
    return top;
}
bool binary_format::check_if_all_dontcares()
{
    for (int i = 0; i < top; i++)
        if (minterm[i])
            return false;
    return true;
}
int binary_format::count_covered()
{
    int count = 0;
    for (int i = 0; i < top; i++)
        if (!coveredepi[i])
            count++;
    return count;
            
}
bool binary_format::count_stars(int num_variables)
{
    int counter_stars =0;
   
    for (int i=0; i < binary.size(); i++)
    {
        if (binary[i]=='*')
            counter_stars++;
        
    }
    if (counter_stars==num_variables)
        return true;
    else
        return false;
}
