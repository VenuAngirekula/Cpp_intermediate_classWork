#include "VendingMachine.H"

using namespace std;


/*********Construcor *********************/
VendingMachine::VendingMachine(int colaCount, int chipscount,int candycount)
:_Cola_count(colaCount), 
_Chips_count(chipscount),
_Candy_count(candycount)
{
   // PrintHeader();
}

void VendingMachine::PrintHeader()
{
    cout << "\nAvailable items:\n " \
         << "COLA : $ 1.00 |  CHIPS : $ 0.50 |   CANDY : $ 0.65 " << endl;
    
    cout << "\nAccetable Currency: NICKEL, DIME, QUATER " << endl;
    cout << "Ex: 2N 3D 4Q :: 2 NiCKELS + 3 DIMES + 4 QUATER\n\n" << endl;
}

void VendingMachine::InsertCoins()
{
    string coinInput;
    // cout << "INSERT COINS : ";
    cin >> coinInput;
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
    _currentAmount += _CoinValue["Nickel"] * _Entered_coins[0] + 
                      _CoinValue["Dime"]   * _Entered_coins[1] +
                      _CoinValue["Quater"] * _Entered_coins[2];

    #if PRINT
    cout << _Entered_coins[0] << " Nickels; "  \
         << _Entered_coins[1] << " Dimes; "  \
         << _Entered_coins[2] << " Quaters; " << endl;
    cout << "Entered value: " << _currentAmount << " $ " << endl;
    #endif

}

std::string VendingMachine::SelectItem()
{
    // cout << "Please select items: " ;
    string item;
    cin >> item;
    std::transform(item.begin(), item.end(), item.begin(), ::toupper);
    if(_Rates.find(item) != _Rates.end()) {
       // ProcessItem(item);
        return item;
    }
    else
    {
        // cout << "Please select available items only" << endl;
        return "Invaid item";
    }    

}

float VendingMachine::ProcessItem(std::string item)
{
    float balanceAmount =  _currentAmount - _Rates[item];

    if(_Rates[item] > _currentAmount)
    {
        cout << "PRICE of selected item: " << _Rates[item] << \
                " | Amount Entered : " << _currentAmount << endl;
        InsertCoins();
    }
    else if (_Rates[item] < _currentAmount)
    {
        // ReturnCoins(balanceAmount);
    }
    else
    {   
        cout << "Thank you!!!" << endl;
        _currentAmount = 0.0; 
        _Inventory[item]--;
        //Print_Inventory();
    }
    return balanceAmount;
}

void VendingMachine::ReturnCoins(float balanceAmount)
{
        
    std::pair<int, float> getquaters= get_Coins(balanceAmount,"Quater");
    int Quater_coins = getquaters.first; balanceAmount = getquaters.second;

    std::pair<int, float> getDimes= get_Coins(balanceAmount,"Dime");
    int Dime_coins = getDimes.first; balanceAmount = getDimes.second;
    
    std::pair<int, float> getNickels= get_Coins(balanceAmount,"Nickel");
    int Nickel_coins = getNickels.first; balanceAmount = getNickels.second;

    
    cout << "Please check return coin tray: " \
            << Nickel_coins << " Nickels;  "  \
            << Dime_coins   << " Dimes  ;  "  \
            << Quater_coins << " Quater ;  "  << endl;
}

std::pair <int, float> VendingMachine::get_Coins(float balanceAmount, string coinName)
{
    
    int coins = 0;    
    float diff = balanceAmount - _CoinValue[coinName];    
    if(diff > 0)
    {
        coins = balanceAmount / _CoinValue[coinName];
        balanceAmount = fmod(balanceAmount, _CoinValue[coinName]);
    }
    else if( std::abs(diff) < 1e-06)
    {
        coins = 1;
        balanceAmount = 0.0;
    }
    else {}
    return make_pair(coins, balanceAmount);
}

void VendingMachine::Print_Inventory()
{
    cout << "\n\n/////////////////////////////////////////////////////" << endl;
    cout << "Inventory details:" << endl;
    for(auto row : _Inventory)
    {
        cout << row.first << " : " << row.second  << endl;
    }
    cout << "/////////////////////////////////////////////////////\n\n" << endl;
}

VendingMachine::~VendingMachine()
{
    
}