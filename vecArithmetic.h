#include<complex>
using namespace std;
typedef vector<complex<double>> vcd;
typedef complex<double> cd;
vector<int> operator*(vector<int>d1,vector<int>d2);
void carry_res(vector<int>&res);
vector<int> operator+(vector<int>d1, vector<int>d2);
vector<int> operator-(vector<int>d1, vector<int>d2);
vector<int> karatsuba_mul(vector<int>d1, vector<int>d2);
int next_pow2(int n);
vector<complex<double>> to_complex(vector<int>&d);
vector<int> to_int(vector<complex<double>>&d);
vcd fft(vcd d, cd w);
vcd evaluate(vcd d);
vcd interpolate(vcd d);
vector<int> fft_mul(vector<int>d1, vector<int>d2);
void trim(vector<int>&d);
vector<int> divn(vector<int>d1, int n);
vector<int> toom_cook_mul(vector<int>d1, vector<int>d2);
vector<int> add_zeroes(vector<int>d, int n);