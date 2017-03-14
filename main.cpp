#include <iostream>
#include <string>
#include <cmath>
#include "binary_format.hpp"

#include <vector>
using namespace std;
void create_EPI(vector<binary_format> pushing,binary_format* EPI, int & indexepi)
{
    int x;
    bool no_difference;
    cout << endl << " The EPIs are :  " << endl;
    for (int i = 0; i < pushing.size(); i++) {
        for (int z = 0; z < pushing.at(i).get_size(); z++ {
           if (pushing.at(i).minterm[z]){
                x = pushing.at(i).arr[z];
                no_difference = true;
                for (int k = 0; k < pushing.size(); k++){
                    if (k != i)  {
                        for (int j = 0; j < pushing.at(k).get_size(); j++){
                            if (x == pushing.at(k).arr[j]) {
                                no_difference = false;
                                break;
                            }
                            
                        }
                    }
                    if (!no_difference)
                        break;
                }
                if (no_difference)
                {
                    EPI[indexepi++] = pushing.at(i);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < indexepi; i++)
        EPI[i].print_binary();
}
void remove_dublicates(vector<binary_format> &pushing)
{
    string check;
    string checking_upon;
    for (int k = 0; k < 3; k++)
        for (int i = 0; i < pushing.size() - 1; i++) {
            pushing.at(i).get_binary(check);
            for (int j = i + 1; j < pushing.size(); j++){
                pushing.at(j).get_binary(checking_upon);
                if (check == checking_upon) {
                    pushing.erase(pushing.begin() + j);
                }
            }
        }
}
void print_PI(vector<binary_format> pushing)
{
    cout << " PIs in binary format:  " << endl;
    for (int i = 0; i < pushing.size(); i++) {
        pushing.at(i).print_binary();
    }
}
void sort(binary_format* &all_array, int max_index)
{
    binary_format temp;
    for (int i = 0; i< max_index; i++)
        for (int j = 0; j < max_index - 1; j++)
            if (all_array[j].get_ones()>all_array[j + 1].get_ones()){
                temp = all_array[j];
                all_array[j] = all_array[j + 1];
                all_array[j + 1] = temp;
            }
}
void create_PI(binary_format* all_array, int max_index, vector<binary_format> &pushing, int num_variables, bool &n_star)
{
    binary_format temp;
    bool found_difference = false;
    int save_index;
    int index = 0;
    binary_format* temp_array;
    temp_array = new binary_format[max_index*2 + 10];
    for (int i = 0; i < max_index - 1; i++) {
        temp = all_array[i];
        if (temp.count_stars(num_variables)){
            cout << "The solution is :   " ;
            cout << "1" << endl;
            n_star=false;
            return;
        }
        for (int j = i + 1; j < max_index; j++) {
            if (all_array[j].get_ones() > temp.get_ones() + 1)
                break;
            if (all_array[j].get_ones() > temp.get_ones()){
                save_index = temp.check_difference(all_array[j]);
                if (save_index != -1) {
                    found_difference = true;
                    all_array[j].set_status(1);
                    all_array[i].set_status(1);
                    temp_array[index].change_binary(temp, save_index);
                    for (int i = 0; i < temp.get_size(); i++) {
                        temp_array[index].arr[i] = temp.arr[i];
                        temp_array[index].minterm[i] = temp.minterm[i];
                    }
                    for (int i = 0; i < all_array[j].get_size(); i++){
                        temp_array[index].arr[temp.top+i] = all_array[j].arr[i];
                        temp_array[index].minterm[temp.top + i] = all_array[j].minterm[i];
                    }
                    temp_array[index].top = temp.top + all_array[j].top;
                    index++;
                }
            }
        }
    }
    if (found_difference == true)
        create_PI(temp_array, index, pushing, num_variables, n_star);
    for (int i = 0; i < max_index; i++)
        if (!all_array[i].check_if_all_dontcares())
            if (!all_array[i].get_status())
                pushing.push_back(all_array[i]);
}

void create_all_variables_array(binary_format* minterms, int max_index, binary_format* dont_cares, int combinations, int number_of_variables, binary_format* &all_array, int index_minterms)
{
    int index = 0;
    for (int i = 0; i < index_minterms; i++)
        all_array[i] = minterms[i];
    for (int i = index_minterms; i <max_index; i++)
        all_array[i] = dont_cares[index++];
}

void find_subset(vector<binary_format> &pushing,binary_format* EPI, int index_epi)
{
    int index_nonessential = 0;
    binary_format* non_essential;
    non_essential = new binary_format[pushing.size()];
    bool flag = false;
    for (int i =0; i < index_epi; i++){
        for (int j = 0; j < EPI[i].get_size();j++){
            if (EPI[i].minterm[j]) {
                for (int z = 0; z < pushing.size(); z++){
                    for (int k = 0; k < pushing.at(z).get_size(); k++){
                        if (EPI[i].arr[j]==pushing.at(z).arr[k]){
                            pushing.at(z).coveredepi[k] = 1;
                        }
                    }
                }
            }
        }
    }
    while(!flag)
    {
   
    int max = 0;
    int index = -1;
        flag = true;
    for (int i = 0; i < pushing.size(); i++){
        if (pushing.at(i).count_covered() > max) {
            max = pushing.at(i).count_covered();
            index = i;
        }
    }
        for (int i = 0; i < pushing.size(); i++) {
            for (int j = 0; j < pushing.at(i).get_size(); j++) {
                if (pushing.at(i).count_covered() != 0) {
                    flag = false;
                    break;
                }
            }
            if (!flag)
                break;
        }
        if (index != -1) {
            for (int i = 0; i < pushing.at(index).get_size(); i++)  {
                for (int j = 0; j < pushing.size(); j++) {
                    for (int k = 0; k < pushing.at(j).get_size(); k++)
                        if (pushing.at(index).arr[i] == pushing.at(j).arr[k]) {
                            pushing.at(j).coveredepi[k] = 1;
                        }
                }
            }
            non_essential[index_nonessential++] = pushing.at(index);
        }
    }
    cout << "The PIs included in the solution are:  " << endl;
    for (int i = 0; i < index_nonessential; i++){
        non_essential[i].print_binary();
    }
}
int main()
{
    bool n_star=true;
    binary_format* minterms;
    binary_format* all_array;
    binary_format* dont_cares;
    vector<binary_format> pushing;
    bool enter_minterms = true;
    int number_of_variables;
    int input;
    int index_minterms = 0;
    int index_dontcares = 0;
    int combinations;
    int indexepi = 0;
    cout << " Enter the number of variables " << endl;
    cin >> number_of_variables;
    while (number_of_variables < 2 || number_of_variables > 16){
        cout << " invalid input. range is 2-16" << endl;
        cin >> number_of_variables;
    }
    combinations = pow(2, number_of_variables);
    minterms = new binary_format[combinations];
    dont_cares = new binary_format[combinations];
    cout << " Enter the number of minterms you have in your function, press -2 to start entering the dont cares, to stop entering press -1, and -3 if you want to enter the minterms again " << endl;
    cin >> input;
    while (input != -1){
        while (input >= combinations || input < -3) {
            cout << " invalid input the number of minterm is incorrect";
            cin >> input;
        }
        if (input == -2)
            enter_minterms = false;
        else
            if (input == -3)
                enter_minterms = true;
            else
                if (enter_minterms){
                    minterms[index_minterms].add_binary(input, number_of_variables, 1);
                    minterms[index_minterms].arr[0]=input;
					index_minterms++;
                }
                else {
                    dont_cares[index_dontcares].add_binary(input, number_of_variables, 0);
                    index_dontcares++;
                }
        cin >> input;
    }
    if (index_dontcares>0&&index_minterms==0){
        cout << "The solution is : 0 or 1" << endl;
        n_star=false;}
	else   
		if (index_minterms==0){
			cout << "The solution is : 0" << endl;
			n_star=false;
		}
    int index_max = index_minterms + index_dontcares;
    all_array = new binary_format[index_max];
    create_all_variables_array(minterms, index_max, dont_cares, combinations, number_of_variables, all_array, index_minterms);
    sort(all_array, index_max);
    create_PI(all_array, index_max, pushing, number_of_variables, n_star);
   if (n_star==true){
    remove_dublicates(pushing);
    print_PI(pushing);
     binary_format* EPI = new binary_format[pushing.size()];
    create_EPI(pushing, EPI, indexepi);
    find_subset(pushing, EPI, indexepi);
  /* for (int i = 0; i < pushing.size(); i++)
    {
        for (int j = 0; j < pushing.at(i).get_size(); j++)
        {
            cout << pushing.at(i).arr[j] << ",";
            
        }
        cout << endl;
        for (int j = 0; j < pushing.at(i).get_size(); j++)
            cout << pushing.at(i).minterm[j] << ",";
        cout << endl;
        for (int j = 0; j < pushing.at(i).get_size();j++)
            cout << pushing.at(i).coveredepi[j] << ",";
        cout << endl;
    }*/
   }
    system("pause");
    return 0;
}


