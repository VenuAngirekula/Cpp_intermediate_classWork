#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <cmath>
#include <unordered_map>

class VendingMachine
{
    private:
        float _cashVault;
        float _currentAmount = 0.0;

        int _Treasury_Nickels;
        int _Treasury_Dimes  ;
        int _Treasury_Quaters;
        std::array<int,3> _Treasury_Coins;
        
        std::unordered_map<std::string, float> _Rates = {
                {"COLA", 1},
                {"CHIPS", 0.5},
                {"CANDY", 0.65}
                };
        std::unordered_map<std::string, int> _Inventory = {
                {"COLA", 0},
                {"CHIPS", 0},
                {"CANDY", 0}
                };
        std::unordered_map<std::string, float> _CoinValue = {
                {"Nickel", 0.05},
                {"Dime", 0.1},
                {"Quater", 0.25}
                };
    
    public:
        std::array<int,3> _Entered_coins;
        std::array<int,3> _Return_coins;
        std::string _selectedItem;
        float _balanceAmount;

        VendingMachine(int colaCount, int chipscount, int candycount);

        VendingMachine(std::array<int,3> Inventory);

        VendingMachine(std::array<int,3> Inventory, std::array<int,3> Treasury);

        ~VendingMachine();

        float coinToCurrency(std::array<int,3> coins);

        void SetInventory(std::array<int,3> Inventory);

        void SetTreasurycoins(std::array<int,3> InitialCoins);

        float GetTreasuryAmount()
        {
             return  _Treasury_Nickels * _CoinValue["Nickel"] + \
                     _Treasury_Dimes   * _CoinValue["Dime"] + \
                     _Treasury_Quaters * _CoinValue["Quater"] ;
        }

        bool InsertCoins();

        void ProcessCoins(std::string s);

        void Makechange(float _balanceAmount,std::string whichcoins);

        std::pair <int, float> get_Coins(float balanceAmount,std::string coinName);

        void PrintHeader();

        void Print_Inventory();

        std::string SelectItem();

        void Dispatch_Reinsert_Makechange(std::string item);

        void ReInsertCoins(std::string item);

        bool ReturnCoins();

        bool checkReturnCoins();

        void DischargeItem(std::string item);
        
        void CheckInventory(std::string item);

        void SoldOut();

};



#endif