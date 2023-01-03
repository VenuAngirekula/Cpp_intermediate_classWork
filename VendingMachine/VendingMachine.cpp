#include "VendingMachine.H"

using namespace std;


/*********Construcor *********************/
VendingMachine::VendingMachine(int colaCount, int chipscount, 
                int candycount):_Cola_count(colaCount), 
                _Chips_count(chipscount),
                _Candy_count(candycount)
{
    Print_Inventory();
    PrintHeader();
}

void VendingMachine::PrintHeader()
{
    cout << "\nAvailable items: \n  \
              COLA  :  $ 1.00 \n \
              CHIPS :  $ 0.50 \n \
              CANDY :  $ 0.65 " << endl;
    
    cout << "\nAccetable Currency: NICKEL, DIME, QUATER " << endl;
    cout << "Ex: 2N 3D 4Q :: 2 NiCKELS + 3 DIMES + 4 QUATER\n\n" << endl;
}

void VendingMachine::InsertCoins()
{
    string coinInput;
    
    cout << "INSERT COINS : ";
    getline(cin, coinInput);
    
    processCoins(coinInput);   
}

void VendingMachine::processCoins(string coin_Input)
{
    int ind = 0;
    regex pat("\\d+");
	smatch result;
    while (std::regex_search(coin_Input, result, pat)) {
        _Entered_coins[ind] = stoi(result.str());
        coin_Input = result.suffix().str();
        ind++;
    }
    float currentAmount = 0.05 * _Entered_coins[0] + 0.1 * _Entered_coins[1] +
                                         0.25 * _Entered_coins[2];
    cout << "Entered value: " << currentAmount << " $ " << endl;

}

void VendingMachine::SelectItem()
{
    std::map<std::string, float> item_and_Rates = {
                {"COLA", 1},
                {"CHIPS", 0.5},
                {"CANDY", 0.65}
                };

    cout << "Please select items: " ;
    string item;
    cin >> item;
    std::transform(item.begin(), item.end(), item.begin(), ::toupper);
    
    if(item_and_Rates.find(item) != item_and_Rates.end()) {
        cout << "selected item : " << item << 
                "\n Price:     : " << item_and_Rates[item] << endl;
    }
    else
    {
        cout << "Please select available items only" << endl;
    }

    check
    
}

void VendingMachine::ReturnCoins()
{
    
}

void VendingMachine::Print_Inventory()
{
    cout << "Inventory details:" << endl;
    cout << " Cola  :" << _Cola_count \
         << "\n Chip  :" << _Chips_count \
         << "\n Candy :" << _Candy_count << endl;
}

VendingMachine::~VendingMachine()
{
    
}