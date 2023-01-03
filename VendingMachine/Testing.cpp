
#include "VendingMachine.H"

int main(int argc, char const *argv[])
{
    VendingMachine VM(50,100,50);
    
    VM.InsertCoins();

    while(1)
    {
        VM.SelectItem();
    }


    return 0;
}
