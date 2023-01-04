
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
        Testing_Acceptcoins(VM,"0N0Q0D");
        assert((VM._Entered_coins==testcoins));
    }

    {
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {1, 1, 1};
        Testing_Acceptcoins(VM,"1N1Q1D");
        assert((VM._Entered_coins==testcoins));
    }
    
    {
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {1, 2, 3};
        Testing_Acceptcoins(VM,"1N2Q3D"); 
        assert((VM._Entered_coins==testcoins));
    }
    /***********Item selection testing ****************/    
    std::vector<std::string> testItemNames = {"Cola", "Chips", "Candy"};
    for (auto testItem: testItemNames)
    {
        VendingMachine VM(5,5,5);
        std::string itemSelected = Testing_ItemSelection(VM,"20N10Q4D",testItem);
        std::transform(testItem.begin(),testItem.end(), testItem.begin(), ::toupper);
        assert(itemSelected==testItem);
        cout << "Test passed for :"  << testItem << endl;
    }

    /***********Item processing testing******************/
    // Case:  collectedamount == Item price
    
    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "0N0Q4D";
    //     std::string itemTobeSelected = "Cola"; float TestBalance = 0.0;
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( ((balanceAmount-TestBalance)<1e-06) );
    // }

    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "0N5Q0D";
    //     std::string itemTobeSelected = "Chips"; float TestBalance = 0.0;
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( ((balanceAmount-TestBalance)<1e-06) );
    // }

    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "3N5Q0D";
    //     std::string itemTobeSelected = "Candy"; float TestBalance = 0.0;
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( ((balanceAmount-TestBalance)<1e-06) );
    // }

    // Case:  collectedamount < Item price
    // {
    //     VendingMachine VM(5,5,5);
    //     std::string coinsinserted = "0N0Q3D";
    //     std::string itemTobeSelected = "Cola"; 
    //     float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
    //                                 itemTobeSelected);
    //     assert( (balanceAmount<0) );
    // }

    {
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N0Q3D\n0N0Q1D";
        std::string itemTobeSelected = "Cola";
        float balanceAmount =  Testing_ItemProcessing(VM,coinsinserted,\
                                    itemTobeSelected);
        
        assert( (balanceAmount<0) );
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
    cin.seekg(coinstream.tellg(), std::ios_base::beg);
    cout << "After marker pos: " << coinstream.tellg() << endl; 
    for(auto i : VM._Entered_coins)
        cout << i ;
    cout << "After after marker pos: " << coinstream.tellg() << endl; 
    float balanceAmount = VM.ProcessItem(itemSelected);
    std::cin.rdbuf(cin_backup);

    return balanceAmount;
    
    
}