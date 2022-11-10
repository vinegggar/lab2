#include <iostream>
#include "longint.h"

using namespace std;


int main() {
    Lint A("25835"),
    B("351488"), C("33790411487878798256071"), D("341");
    Lint::setMultMode(new NaiveMult);
    Lint G=A*B;
    cout<<A*B;
    Lint::setMultMode(new Karatsuba);
    cout<<A*B;
    Lint::setMultMode(new SchonhageStrassen);
    Lint H = A*B;
    Lint::setMultMode(new ToomCook);
    Lint L = A*B;

    cout<<(G-H)<<" "<<(G-L)<<" "<<(H-L);
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
    cout<<"Fermat:  "<<A.isPrime(5)<<endl;
    clock_t end = clock();
    cout<<"time: "<<float(end-start)/CLOCKS_PER_SEC<<endl;
    Lint::setTestMode(new MillerRabin);
    start = clock();
    cout<<"Miller-Rabin:  "<<A.isPrime(5)<<endl;
    end = clock();
    cout<<"time: "<<float(end-start)/CLOCKS_PER_SEC<<endl;
    Lint::setTestMode(new SolovayStrassen);
    start = clock();
    cout<<"Solovay-Strassen:  "<<A.isPrime(5)<<endl;
    end = clock();
    cout<<"time: "<<float(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}
