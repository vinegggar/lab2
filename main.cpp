#include <iostream>
#include "longint.h"
#include "vecArithmetic.h"
using namespace std;


int main() {
    Lint A("85053461164796801949539541639542805770666392330682673302530819774105141531698707146930307290253537320447270457"),
    B("14693679385278593849609206715278070972733319459651094018859396328480215743184089660644531"),
    C("1234567890"), D("1000000007"), E("567707");
    Lint::setMultMode(new SchonhageStrassen());
    cout << A*B << endl;
    cout << (C-D)*E << endl;
    Lint::setMultMode(new Karatsuba());
    cout << A*B << endl;
    cout << (C-D)*E << endl;
    Lint::setMultMode(new ToomCook());
    cout << A*B << endl;
    cout << (C-D)*E << endl;
    Lint::setMultMode(new NaiveMult());
    cout << A*B << endl;
    cout << (C-D)*E << endl;
    C.get_inv();
    cout<<endl<<C/E;
    cout<<C%E;
    Lint::setTestMode(new MillerRabin());
    cout <<"does A pass Miller-Rabin test? "<< A.primeCheck() << endl;
    cout <<"does B pass Miller-Rabin test? "<< B.primeCheck() << endl;
    cout <<"does C pass Miller-Rabin test? "<< C.primeCheck() << endl;
    cout <<"does D pass Miller-Rabin test? "<< D.primeCheck() << endl;
    Lint::setTestMode(new Fermat());
    cout <<"does A pass Fermat test? "<< A.primeCheck() << endl;
    cout <<"does B pass Fermat test? "<< B.primeCheck() << endl;
    cout <<"does C pass Fermat test? "<< C.primeCheck() << endl;
    cout <<"does D pass Fermat test? "<< D.primeCheck() << endl;
    return 0;
}
