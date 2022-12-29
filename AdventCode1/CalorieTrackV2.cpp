#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

void printTotalCalories(multimap<int, int>& ElfCalorieList)
{
    for(auto i:ElfCalorieList)
    {
        cout <<  i.first  << " : "<< i.second << endl;
    }
}

int main(int argc, char const *argv[])
{
    fstream f {"InputList.txt"};
    multimap<int, int> ElfCalorieList;
    if (f.is_open())
    {
        string item;
        int sum = 0;
        int Elf =1;
        while (getline(f, item))
        {
            if(item.empty() ){
                ElfCalorieList.insert(make_pair(sum, Elf));
                sum = 0;
                Elf++;
            }
            else{ 
            sum += stoi(item);
            }
        }
        ElfCalorieList.insert(make_pair(sum, Elf));

    }
    // printTotalCalories(ElfCalorieList);

    cout << "Elf " << ElfCalorieList.rbegin()->second << " has most number of  calories : "<< ElfCalorieList.rbegin()->first << endl;

    return 0;
}
