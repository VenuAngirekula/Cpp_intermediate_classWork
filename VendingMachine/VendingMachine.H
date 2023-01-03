#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

class VendingMachine
{
    private:
        float _cashVault;
        float _currentAmount;
        int _Cola_count;
        int _Chips_count;
        int _Candy_count;
        enum _Items {COLA, CHIPS, CANDY };
        std::array<int,3> _Entered_coins;
        
    public:
        VendingMachine(int colaCount, int chipscount, int candycount);

        ~VendingMachine();

        void InsertCoins();

        void processCoins(std::string s);

        void ReturnCoins();

        void PrintHeader();

        void Print_Inventory();

        void SelectItem();
};



#endif