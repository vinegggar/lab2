#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("3546245297457217493590449191748546458005595187661976371"),
    B("1000000007"), C("331"), D("341");
    Lint::setMultMode(new Karatsuba);
    cout << A*B << endl;
    Lint::setMultMode(new SchonhageStrassen);
    cout << A*B << endl;
    Lint::setMultMode(new ToomCook);
    cout << A*B << endl;
    Lint::setMultMode(new NaiveMult);
    cout<<A*B<<endl;
    cout<<A/C<<endl;
    cout<<A%C;
    B.getInv();
    cout<<endl;
    cout<<B.jacobi(C)<<endl;
    //set clock
    Lint::setTestMode(new Fermat);
    clock_t start = clock();
    cout<<"Fermat:  "<<A.isPrime(1)<<endl;
    clock_t end = clock();
    cout<<"time: "<<float(end-start)/CLOCKS_PER_SEC<<endl;
    Lint::setTestMode(new MillerRabin);
    start = clock();
    cout<<"Miller-Rabin:  "<<A.isPrime(1)<<endl;
    end = clock();
    cout<<"time: "<<float(end-start)/CLOCKS_PER_SEC<<endl;
    Lint::setTestMode(new SolovayStrassen);
    start = clock();
    cout<<"Solovay-Strassen:  "<<A.isPrime(1)<<endl;
    end = clock();
    cout<<"time: "<<float(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
