#include "VendingMachine.H"

using namespace std;


/*********Construcor *********************/
VendingMachine::VendingMachine(int colaCount, int chipscount,int candycount)
{
    SetInventory(std::array<int,3> {colaCount, chipscount, candycount});
   // PrintHeader();
}


VendingMachine::VendingMachine(std::array<int,3> Initial_Inventory)
{
    SetInventory(Initial_Inventory);
   // PrintHeader();
}

VendingMachine::VendingMachine(std::array<int,3> Initial_Inventory,
                               std::array<int,3> Initial_Treasury)
{
    SetInventory(Initial_Inventory);
    SetTreasurycoins(Initial_Treasury);
   // PrintHeader();
}

void VendingMachine::SetInventory(std::array<int,3> Initial_Inventory)
{
    _Inventory["COLA"]  = Initial_Inventory[0]; 
    _Inventory["CHIPS"]  = Initial_Inventory[1]; 
    _Inventory["CANDY"]  = Initial_Inventory[2];     
}

void VendingMachine::SetTreasurycoins(std::array<int,3> Initial_Treasury)
{
    _Treasury_Nickels = Initial_Treasury[0];
    _Treasury_Dimes   = Initial_Treasury[1];
    _Treasury_Quaters = Initial_Treasury[2];
    _Treasury_Coins = Initial_Treasury;
}

void VendingMachine::PrintHeader()
{
    cout << "\nAvailable items:\n " \
         << "COLA : $ 1.00 |  CHIPS : $ 0.50 |   CANDY : $ 0.65 " << endl;
    
    cout << "\nAccetable Currency: NICKEL, DIME, QUATER " << endl;
    cout << "Ex: 2N 3D 4Q :: 2 NiCKELS + 3 DIMES + 4 QUATER\n\n" << endl;
}

float VendingMachine::coinToCurrency(std::array<int,3> coins)
{
    return (_CoinValue["Nickel"] * coins[0] +
            _CoinValue["Dime"]   * coins[1] +
            _CoinValue["Quater"] * coins[2]);
}

bool VendingMachine::InsertCoins()
{
    string coinInput;
    #if PROD
    // cout << "INSERT COINS : ";
    #endif
    cin >> coinInput;
    if(coinInput.empty())
    {
        cerr << "No coins inserted" << endl;
        return false;
    }
    ProcessCoins(coinInput);   
    return true;    
}

void VendingMachine::ProcessCoins(string coinInput)
{
    int ind = 0;
    regex pat("\\d+");
	smatch result;
    while (std::regex_search(coinInput, result, pat)) {
        _Entered_coins[ind] = stoi(result.str());
        coinInput = result.suffix().str();
        ind++;
    }
    _currentAmount += coinToCurrency(_Entered_coins);

    #if DEBUG
    cout << _Entered_coins[0] << " Nickels; "  \
         << _Entered_coins[1] << " Dimes; "  \
         << _Entered_coins[2] << " Quaters; " << endl;
    cout << "Entered value: " << _currentAmount << " $ " << endl;
    #endif

}



std::string VendingMachine::SelectItem()
{
    #if PROD
    cout << "Please select items: " ;
    #endif

    string item;
    cin >> item;
    std::transform(item.begin(), item.end(), item.begin(), ::toupper);
    if(_Rates.find(item) != _Rates.end())
    {
        _selectedItem = item;
        CheckInventory(item);
        #if PROD
            Dispatch_Reinsert_Makechange(item);
        #endif
    }
    else
    {
        #if PROD
            cout << "Please select available items only" << endl;
        #endif
        _selectedItem = "";
    }   
    return _selectedItem;
}

void VendingMachine::CheckInventory(std::string item)
{
    if (_Inventory[item]==0 && !item.empty())
    {
        _selectedItem = "";
        cout << "\t!!! "<< item << " - SOLD OUT" << endl;
        SelectItem();
    }
}
void VendingMachine::SoldOut()
{

}

void VendingMachine::Dispatch_Reinsert_Makechange(std::string item)
{
    _balanceAmount =  _currentAmount - _Rates[item];
    
    if(_Rates[item] > _currentAmount)
    {
        ReInsertCoins(item); 
    }
    else if (std::fabs(_balanceAmount) < 1e-06)
    {  
        if(ReturnCoins())
            return;
        DischargeItem(item);
              
    }
    else if (_Rates[item] < _currentAmount )
    {
        Makechange(_balanceAmount,"Treasury");
        DischargeItem(item);
    }
    
}

void VendingMachine::DischargeItem(std::string item)
{
    cout << item << " Dispatched. " << "Thank you!!!"  << endl;
    _currentAmount = 0.0; 
    _Inventory[item]--;  
}

bool VendingMachine::ReturnCoins()
{
    if(checkReturnCoins())
    {
        _balanceAmount = _currentAmount;
        Makechange(_balanceAmount,"Nontreasury");
        return  true;

        #if PROD
            InsertCoins();
        #endif    
    }
    return false;

}

void VendingMachine::ReInsertCoins(std::string item)
{
    _Entered_coins = {0,0,0};
    if (InsertCoins())
    {
        Dispatch_Reinsert_Makechange(item);
        return;
    }
}

bool VendingMachine::checkReturnCoins()
{
    cout << "Select Proceed (Y) or Return coins(N)" << endl;
    string RetcoinUserInput;
    cin >> RetcoinUserInput;
    std::transform(RetcoinUserInput.begin(), RetcoinUserInput.end(),
            RetcoinUserInput.begin(), ::toupper);
    if(RetcoinUserInput=="N")
        return true;

    return false;
}

void VendingMachine::Makechange(float amount ,std::string whichcoins)
{
    int Return_Nickels, Return_Dimes, Return_Quaters;

    if(whichcoins == "Nontreasury")
    {
        _Return_coins  = _Entered_coins;
        Return_Nickels = _Return_coins[0];
        Return_Dimes   = _Return_coins[1];
        Return_Quaters = _Return_coins[2];   
    }
    else
    {    
        std::pair<int, float> getquaters= get_Coins(amount,"Quater");
        Return_Quaters = getquaters.first; amount = getquaters.second;

        std::pair<int, float> getDimes= get_Coins(amount,"Dime");
        Return_Dimes = getDimes.first; amount = getDimes.second;
        
        std::pair<int, float> getNickels= get_Coins(amount,"Nickel");
        Return_Nickels = getNickels.first; amount = getNickels.second;

        _Return_coins = {Return_Nickels, Return_Dimes, Return_Quaters };
    }
    cout << "Please check return coin tray: " \
            << Return_Nickels << " Nickels;  "  \
            << Return_Dimes   << " Dimes  ;  "  \
            << Return_Quaters << " Quater ;  "  << endl;

    cout << "\tAmount inserted : " << _currentAmount << " $" <<
            "\tAmount returned : " << _balanceAmount << " $" << endl;
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