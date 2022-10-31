#include<vector>
#include<complex>

using namespace std;

vector<int> operator*(vector<int>d1,vector<int>d2){
    vector <int> res(d1.size()+d2.size());
    for (int i=0;i<d1.size();++i){
        for(int j=0;j<d2.size();++j){
            res[i+j]+=d1[i]*d2[j];
        }
    }
    return res;
}

void carry_res(vector<int>&res){
    for (int i = 0; i < res.size()-1; ++i) {
        res[i+1]+=res[i]>=0? res[i]/10: -((-res[i]+9)/10);
        res[i] = (res[i]+10)%10;//mathematical remainder
    }
}

vector<int> operator+(vector<int>d1,vector<int>d2){
    vector<int> res;
    int max_size = int(max(d1.size(), d2.size()));
    for (int i=0;i<max_size;++i){
        int d = 0;

        if (i<d1.size()) d += d1[i];
        if (i<d2.size()) d+=d2[i];

        res.push_back(d);
    }
    return res;
}

vector<int> operator-(vector<int>d1, vector<int>d2){
    for(int &i: d2)i*=-1;
    return d1+d2;
}

/*
 * returns (ac*(10^(2*half)))+((ad+bc)*10^half)+bd
 * ad+bc counts as (a+b)*(c+d)-ac-bd
 */
vector<int> karatsuba_mul(vector<int>d1, vector<int>d2){
    if(d1.size()<=1 && d2.size()<=1) return {d1[0]*d2[0]};

    while (d1.size()!=d2.size())
    {d1.size()>d2.size()?d2.push_back(0):d1.push_back(0);}

    vector<int> res (2*d1.size()-1);

    int half = d1.size()/2;

    vector<int> a(d1.begin()+half,d1.end()), //right part of d1
    b(d1.begin(), d1.begin()+half), //left
    c(d2.begin()+half,d2.end()), //right part of d2
    d(d2.begin(), d2.begin()+half), //left

    ac = karatsuba_mul(a,c), bd = karatsuba_mul(b,d),

    ad_plus_bc = karatsuba_mul(a+b, c+d)-(ac+bd);

    for(int i=0;i<bd.size();++i) res[i]=bd[i];
    for(int i=0; i < ad_plus_bc.size(); ++i) res[i+half]+= ad_plus_bc[i];
    for(int i=0;i<ac.size();++i) res[i+2*half]+=ac[i];

    return res;
}

typedef vector<complex<double>> vcd;
typedef complex<double> cd;

//returns the smallest power of 2 greater than n
int next_pow2(int n){
    int res = 1;
    while (res<n) res*=2;
    return res;
}

vcd to_complex(vector<int>&d){
    vcd res;
    for(int i:d) res.push_back(complex<double>(i,0));
    return res;
}

vector<int> to_int(vcd&d){
    vector<int> res;
    for(cd &i:d) res.push_back(round(i.real()));
    return res;
}

vcd fft(vcd d, cd w){
    if(d.size()==1) return d;
    vcd even, odd;
    for(int i=0;i<d.size();++i){
        if(i%2==0) even.push_back(d[i]);
        else odd.push_back(d[i]);
    }
    vcd even_fft = fft(even, w*w); vcd odd_fft = fft(odd, w*w);
    vcd res(d.size());
    cd wp(1,0);
    for(int i=0;i<d.size()/2;++i){
        res[i]=even_fft[i]+wp*odd_fft[i];
        res[i+d.size()/2]=even_fft[i]-wp*odd_fft[i];
        wp*=w;
    }
    return res;
}

vcd evaluate(vcd d){
    cd w(cos(2*M_PI/d.size()), sin(2*M_PI/d.size()));
    return fft(d, w);
}

vcd interpolate(vcd d){
    cd w(cos(2*M_PI/d.size()), -sin(2*M_PI/d.size()));
    vcd coefs = fft(d, w);
    for(cd&i:coefs) i/=d.size();
    return coefs;
}

//trim leading zeros
void trim(vector<int>&d){
    while(d.size()>1 && d.back()==0) d.pop_back();
}

vector<int> fft_mul(vector<int>d1, vector<int>d2){
    int prod_size = d1.size()+d2.size()-1;
    d1.resize(next_pow2(prod_size));d2.resize(next_pow2(prod_size));

    vcd vals1 = evaluate(to_complex(d1)), vals2 = evaluate(to_complex(d2));
    vcd vals_prod(vals1.size());
    for(int i=0;i<vals1.size();++i){
        vals_prod[i]=vals1[i]*vals2[i];
    }
    vcd coefs_complex = interpolate(vals_prod);
    vector<int> coefs = to_int(coefs_complex);
    return coefs;
}

//this function is needed to use toom_cook_mul
vector<int> divn(vector<int>d, int n){
    vector<int> res;
    int carry = 0;
    for(int i=d.size()-1;i>=0;--i){
        int cur = d[i]+carry*10;
        res.push_back(cur/n);
        carry = cur%n;
    }
    for(int i=0;i<res.size()/2;++i){
        swap(res[i], res[res.size()-1-i]);
    }
    trim(res);
    return res;
}

/*
 * procedure is quite analogous to karatsuba_mul,
 * but we have to divide by 3 instead of 2,
 * and we have to add 5 times instead of 3
 */
vector<int> toom_cook_mul(vector<int>d1, vector<int>d2){
    while (d1.size()!=d2.size())
    {d1.size()>d2.size()?d2.push_back(0):d1.push_back(0);}
    if (d1.size()<3 && d2.size()<3) return karatsuba_mul(d1,d2);

    vector<int> res(2*d1.size()-1);

    int third = d1.size()/3;

    vector<int> x0(d1.begin(), d1.begin()+third),//left part of d1
    x1(d1.begin()+third, d1.begin()+2*third),//middle
    x2(d1.begin()+2*third, d1.end()),//right part of d1
    y0(d2.begin(), d2.begin()+third),//left part of d2
    y1(d2.begin()+third, d2.begin()+2*third),//middle
    y2(d2.begin()+2*third, d2.end()),//right part of d2

    //product of evaluated polynomials
    v0 = toom_cook_mul(x0,y0),//args are evaluated polynomials at fixed points
    v1 = toom_cook_mul(x0+x1+x2, y0+y1+y2),
    v_1 = toom_cook_mul(x0-x1+x2, y0-y1+y2),
    two ={2}, four = {4}, three={3},
    v2 = toom_cook_mul(x0+two*x1+four*x2,y0+two*y1+four*y2),
    v_inf = toom_cook_mul(x2,y2),

    //interpolation process...
    t1 = divn((three*v0+two*v_1+v2),6)-two*v_inf,
    t2 = divn((v1+v_1),2);

    vector<vector<int>> coefs = {v0, v1-t1, t2-v0-v_inf, t1-t2, v_inf};//interpolated values

    //res = c0*x^0 + c1*x^1 + c2*x^2 + c3*x^3 + c4*x^4
    for(int i=0;i<5;++i){
        for(int j=0;j<coefs[i].size();++j){
            res[i * third + j] += coefs[i][j];
        }
    }

    return res;
}