
#include "VendingMachine.H"

using namespace std;

int main(int argc, char const *argv[])
{
    
    VendingMachine VM(50,100,50);
    string coinInput;

    for (size_t i = 0; i < 5; i++)
    {
        
        VM.InsertCoins();
        VM.SelectItem();
    }

    


    return 0;
}
