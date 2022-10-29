#include<complex>
using namespace std;
typedef vector<complex<double>> vcd;
typedef complex<double> cd;
vector<int> naive_multiplication(vector<int>d1,vector<int>d2);
void carry_res(vector<int>&res);
vector<int> sum(vector<int>&d1, vector<int>&d2);
vector<int> diff(vector<int>d1, vector<int>d2);
vector<int> karatsuba_mul(vector<int>d1, vector<int>d2);
int next_pow2(int n);
vector<complex<double>> to_complex(vector<int>&d);
vector<int> to_int(vector<complex<double>>&d);
vcd fft(vcd d, cd w);
vcd evaluate(vcd d);
vcd interpolate(vcd d);
vector<int> fft_mul(vector<int>d1, vector<int>d2);

