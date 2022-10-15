#include <iostream>
#include "longint.h"
using namespace std;


int main() {
    Lint A("3548"), B;
    cin>>B;
    cout<<A+B;
    bool expr = (A+B)<=A;
    cout<<expr;
    return 0;
}
