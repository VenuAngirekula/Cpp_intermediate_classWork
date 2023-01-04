
#include "VendingMachine.H"
#include <sstream>
#include <cassert>

using namespace std;

void Testing_Acceptcoins(VendingMachine& VM, 
                            std::string coins);

std::string Testing_ItemSelection(VendingMachine& VM, std::string Insertedcoins,\
                        std::string selecteditem);

float Testing_ItemProcessing(VendingMachine& VM, std::string Insertedcoins,\
                               std::string selecteditem);

int main(int argc, char const *argv[])
{
    /***********Testing Acceting coins*****************/
    {
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {0, 0, 0};
        Testing_Acceptcoins(VM,"0N0D0Q");
        assert((VM._Entered_coins==testcoins));
    }

    {
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {1, 1, 1};
        Testing_Acceptcoins(VM,"1N1D1Q");
        assert((VM._Entered_coins==testcoins));
    }
    
    {
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {1, 3, 2};
        Testing_Acceptcoins(VM,"1N3D2Q"); 
        assert((VM._Entered_coins==testcoins));
    }
    /***********Item selection testing ****************/    
    std::vector<std::string> testItemNames = {"Cola", "Chips", "Candy"};
    for (auto testItem: testItemNames)
    {
        VendingMachine VM(5,5,5);
        std::string itemSelected = Testing_ItemSelection(VM,"20N4D10Q",testItem);
        std::transform(testItem.begin(),testItem.end(), testItem.begin(), ::toupper);
        assert(itemSelected==testItem);
        cout << "Test passed for :"  << testItem << endl;
    }

    /***********Item processing testing******************/
    // Case:  collectedamount == Item price
    
    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "0N4D0Q";
    //     std::string itemTobeSelected = "Cola"; float TestBalance = 0.0;
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( ((balanceAmount-TestBalance)<1e-06) );
    // }

    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "0N0D5Q";
    //     std::string itemTobeSelected = "Chips"; float TestBalance = 0.0;
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( ((balanceAmount-TestBalance)<1e-06) );
    // }

    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "3N0D5Q";
    //     std::string itemTobeSelected = "Candy"; float TestBalance = 0.0;
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( ((balanceAmount-TestBalance)<1e-06) );
    // }

    // Case:  collectedamount < Item price
    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "0N3D0Q";
    //     std::string itemTobeSelected = "Cola"; 
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( (balanceAmount<0) );
    // }

    {
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N0D1Q\n 0N0D1Q\n 0N0D1Q\n 0N0D1Q";
        std::string itemTobeSelected = "Cola";
        float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
                                    itemTobeSelected);
        
        assert( (balanceAmount==0) );
    }

    return 0;
}

void Testing_Acceptcoins(VendingMachine& VM, 
                    std::string Insertedcoins)
{
    std::stringstream coinstream(Insertedcoins);
    streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(coinstream.rdbuf());
    VM.InsertCoins();
    std::cin.rdbuf(cin_backup);
}

std::string Testing_ItemSelection(VendingMachine& VM, std::string Insertedcoins,\
                        std::string selecteditem)
{
    Testing_Acceptcoins(VM,Insertedcoins);
    std::stringstream Itemstream(selecteditem);
    streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(Itemstream.rdbuf());
    string itemSelected = VM.SelectItem();
    std::cin.rdbuf(cin_backup);
    return itemSelected;
}

float Testing_ItemProcessing(VendingMachine& VM, std::string Insertedcoins,\
                               std::string selecteditem)
{
    
    std::stringstream itemstream(selecteditem);
    std::stringstream coinstream(Insertedcoins);
    
    streambuf* cin_backup = std::cin.rdbuf();

    std::cin.rdbuf(coinstream.rdbuf());
    // int coinMarker = coinstream.tellg();
    
    cout << "Before marker pos: " << coinstream.tellg() << endl; 
    VM.InsertCoins();
    for(auto i : VM._Entered_coins)
        cout << i ;
    
    
    std::cin.rdbuf(itemstream.rdbuf());
    string itemSelected = VM.SelectItem();


    std::cin.rdbuf(coinstream.rdbuf());
    // cin.seekg(6);
    VM.ProcessItem(itemSelected);
    // for(auto i : VM._Entered_coins)
    //     cout << i ;

    // cin.seekg(12);
    // balanceAmount = VM.ProcessItem(itemSelected);
    // for(auto i : VM._Entered_coins)
    //     cout << i ;

    // cin.seekg(18);
    // balanceAmount = VM.ProcessItem(itemSelected);
    // for(auto i : VM._Entered_coins)
    //     cout << i ;
    cout << "balanceAmount in testing: " << VM._balanceAmount;

    std::cin.rdbuf(cin_backup);
    return VM._balanceAmount;
    
    
}