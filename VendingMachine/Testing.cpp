
#include "VendingMachine.H"
#include <sstream>
#include <cassert>

using namespace std;

void Testing_Acceptcoins(VendingMachine& VM, 
                            std::string coins);

void Testing_ItemSelection(VendingMachine& VM, std::string Insertedcoins,\
                        std::string selecteditem);

float Testing_Dispatch_Reinsert_Makechange(VendingMachine& VM, std::string Insertedcoins,\
                               std::string selecteditem);

float Testing_Repeat_itemSelection(VendingMachine& VM, std::string Insertedcoins,\
                               std::string selecteditem);

int main(int argc, char const *argv[])
{
    /***********Testing Acceting coins*****************/
    {
        cout << "\nTest case 1" << endl;
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {0, 0, 0};
        Testing_Acceptcoins(VM,"0N0D0Q");
        assert((VM._Entered_coins==testcoins));
    }

    {
        cout << "\nTest case 2" << endl;
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {1, 1, 1};
        Testing_Acceptcoins(VM,"1N1D1Q");
        assert((VM._Entered_coins==testcoins));
    }
    
    {
        cout << "\nTest case 3" << endl;
        VendingMachine VM(1,2,3);
        std::array<int,3> testcoins = {1, 3, 2};
        Testing_Acceptcoins(VM,"1N3D2Q"); 
        assert((VM._Entered_coins==testcoins));
    }
    /***********Item selection testing ****************/    
    cout << "\nTest case 4" << endl;
    std::vector<std::string> testItemNames = {"Cola", "Chips", "Candy"};
    for (auto testItem: testItemNames)
    {
        VendingMachine VM(5,5,5);
        Testing_ItemSelection(VM,"20N4D10Q",testItem);
        std::transform(testItem.begin(),testItem.end(), testItem.begin(), ::toupper);
        assert(VM._selectedItem==testItem);
        cout << "Test passed for :"  << testItem << endl;
    }

    /***********Item processing testing******************/
    // Case:  collectedamount == Item price
    
    {
        cout << "\nTest case 5" << endl;
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N0D4Q";
        std::string itemTobeSelected = "Cola"; float TestBalance = 0.0;
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);
        assert( ((balanceAmount-TestBalance)<1e-06) );
    }

    {
        cout << "\nTest case 6" << endl;
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N5D0Q";
        std::string itemTobeSelected = "Chips"; float TestBalance = 0.0;
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);
        assert( ((balanceAmount-TestBalance)<1e-06) );
    }

    {
        cout << "\nTest case 7" << endl;
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "3N5D0Q";
        std::string itemTobeSelected = "Candy"; float TestBalance = 0.0;
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);
        assert( ((balanceAmount-TestBalance)<1e-06) );
    }

    // Case:  collectedamount < Item price
    {
        cout << "\nTest case 8" << endl;
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N3D0Q";
        std::string itemTobeSelected = "Cola"; 
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);
        assert( (balanceAmount<0) );
    }
    // Case:  collectedamount < Item price and Reinserted coins till price reached
    {
        cout << "\nTest case 9" << endl;
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N0D1Q\n 0N0D1Q\n 0N0D1Q\n 0N0D1Q";
        std::string itemTobeSelected = "Cola";
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);
        
        assert( (balanceAmount<1e-06) );
    }

    {
        cout << "\nTest case 10" << endl;
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "1N0D0Q\n 2N0D0Q\n 0N0D1Q\n 0N2D0Q\n 1N0D0Q";
        std::string itemTobeSelected = "Candy";
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);        
        assert( (balanceAmount<1e-06));
    }
    // Case:  collected amount > Item price
    {
        cout << "\nTest case 11" << endl;
        std::array<int,3> expectedRetCoins = {0,1,1};

        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N0D4Q\n";
        std::string itemTobeSelected = "Candy";
        Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);        
        assert( expectedRetCoins == VM._Return_coins);
    }

    {
        cout << "\nTest case 12" << endl;
        std::array<int,3> expectedRetCoins = {0,1,0};

        VendingMachine VM(5,5,5);
        std::string coinsinserted = "7N0D1Q\n";
        std::string itemTobeSelected = "Chips";
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);        
        assert( expectedRetCoins == VM._Return_coins);
    }   

    {
        cout << "\nTest case 13" << endl;
        std::array<int,3> expectedRetCoins = {0,2,1};

        VendingMachine VM(5,5,5);
        std::string coinsinserted = "7N1D4Q\n";
        std::string itemTobeSelected = "Cola";
        float balanceAmount =  Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);        
        assert( expectedRetCoins == VM._Return_coins);
    }
    // Case: Customer presses Return coins
    {
        cout << "\nTest case 14" << endl;
        std::array<int,3> expectedRetCoins = {0,5,2};
        
        VendingMachine VM(5,5,5);
        std::string coinsinserted = "0N5D2Q\nN";
        std::string itemTobeSelected = "Cola";
        Testing_Dispatch_Reinsert_Makechange(VM,coinsinserted,\
                                    itemTobeSelected);        

        assert( expectedRetCoins == VM._Return_coins);
    }
    /***********Sold out testing******************/
    // Case: If item is out of stock
    {
        cout << "\nTest case 15" << endl;
        std::array<int,3>  Inventory = {0,1,1};
        VendingMachine VM(Inventory);
        std::string coinsinserted = "0N5D2Q";
        std::string itemTobeSelected = "Cola";
        Testing_Repeat_itemSelection(VM,coinsinserted,\
                                    itemTobeSelected);        
        assert( VM._selectedItem.empty());
    }

    // Case: item is out of stock + New item entered
    {
        cout << "\nTest case 16" << endl;
        std::array<int,3>  Inventory = {0,1,1};
        VendingMachine VM(Inventory);
        std::string coinsinserted = "0N5D2Q";
        std::string itemTobeSelected = "Cola\nChips";
        Testing_Repeat_itemSelection(VM,coinsinserted,\
                                    itemTobeSelected);        

        assert( VM._selectedItem == "CHIPS");
    }

    // Case: item is out of stock + New item entered
    {
        cout << "\nTest case 17" << endl;
        std::array<int,3>  Inventory = {0,0,1};
        VendingMachine VM(Inventory);
        std::string coinsinserted = "0N4D0Q\n1N2D0Q";
        std::string itemTobeSelected = "Cola\nChips\nCandy";
        Testing_Repeat_itemSelection(VM,coinsinserted,\
                                    itemTobeSelected);        

        assert( VM._selectedItem == "CANDY");
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

void Testing_ItemSelection(VendingMachine& VM, std::string Insertedcoins,\
                        std::string selecteditem)
{
    Testing_Acceptcoins(VM,Insertedcoins);
    std::stringstream Itemstream(selecteditem);
    streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(Itemstream.rdbuf());
    string itemSelected = VM.SelectItem();
    std::cin.rdbuf(cin_backup);

}

float Testing_Dispatch_Reinsert_Makechange(VendingMachine& VM, std::string Insertedcoins,\
                               std::string selecteditem)
{
    
    std::stringstream itemstream(selecteditem);
    std::stringstream coinstream(Insertedcoins);
    
    streambuf* cin_backup = std::cin.rdbuf();
    //Inset first coin
    std::cin.rdbuf(coinstream.rdbuf());
    VM.InsertCoins();
    //Select item
    std::cin.rdbuf(itemstream.rdbuf());
    string itemSelected = VM.SelectItem();
    //Reinsert coin
    std::cin.rdbuf(coinstream.rdbuf());
    VM.Dispatch_Reinsert_Makechange(itemSelected);
    
    std::cin.rdbuf(cin_backup);    
    return VM._balanceAmount;

}

float Testing_Repeat_itemSelection(VendingMachine& VM, std::string Insertedcoins,\
                               std::string selecteditem)
{
    std::stringstream itemstream(selecteditem);
    std::stringstream coinstream(Insertedcoins);
    
    streambuf* cin_backup = std::cin.rdbuf();
    //Inset first coin
    std::cin.rdbuf(coinstream.rdbuf());
    VM.InsertCoins();
    //Select item
    std::cin.rdbuf(itemstream.rdbuf());
    string itemSelected = VM.SelectItem();
    //Reinsert coin
    std::cin.rdbuf(coinstream.rdbuf());
    VM.Dispatch_Reinsert_Makechange(itemSelected);
    
    std::cin.rdbuf(cin_backup);    
    return VM._balanceAmount;

}