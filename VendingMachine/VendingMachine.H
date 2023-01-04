#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <cmath>

class VendingMachine
{
    private:
        float _cashVault;
        float _currentAmount = 0.0;
        int _Cola_count;
        int _Chips_count;
        int _Candy_count;
        
        std::map<std::string, float> _Rates = {
                {"COLA", 1},
                {"CHIPS", 0.5},
                {"CANDY", 0.65}
                };
        std::map<std::string, float> _Inventory = {
                {"COLA", _Cola_count},
                {"CHIPS", _Chips_count},
                {"CANDY", _Candy_count}
                };
        std::map<std::string, float> _CoinValue = {
                {"Nickel", 0.05},
                {"Dime", 0.1},
                {"Quater", 0.25}
                };
        std::array<int,3> _Entered_coins;
        
    public:
        VendingMachine(int colaCount, int chipscount, int candycount);

        ~VendingMachine();

        void InsertCoins();

        void processCoins(std::string s);

        void ReturnCoins(float balanceAmount);

        std::pair <int, float> get_Coins(float balanceAmount,std::string coinName);

        void PrintHeader();

        void Print_Inventory();

        void SelectItem();

        void ProcessItem(std::string item);
};



#endif