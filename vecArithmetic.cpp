#include<vector>
#include<complex>
using namespace std;

vector<int> naive_multiplication(vector<int>d1,vector<int>d2){
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
        res[i + 1] += res[i]>=0? res[i]/10: -1;
        res[i] = (res[i]+10)%10;//mathematical remainder
    }
}

vector<int> sum(vector<int>&d1,vector<int>&d2){
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

vector<int> diff(vector<int>d1, vector<int>d2){
    for(int &i: d2)i*=-1;
    return sum(d1,d2);
}

/*
 * returns (ac*(10^(2*half)))+((ad+bc)*10^half)+bd
 * ad+bc counts as (a+b)*(c+d)-ac-bd
 */
vector<int> karatsuba_mul(vector<int>d1, vector<int>d2){
    if(d1.size()<=1 && d2.size()<=1) return {d1[0]*d2[0]};

    while (d1.size()!=d2.size())
    {d1.size()>d2.size()?d2.push_back(0):d1.push_back(0);}

    int half = d1.size()/2;

    vector<int> res (2*d1.size()-1);

    vector<int> a(d1.begin()+half,d1.end()), //right part of d1
    b(d1.begin(), d1.begin()+half), //left
    c(d2.begin()+half,d2.end()), //right part of d2
    d(d2.begin(), d2.begin()+half), //left

    ac = karatsuba_mul(a,c), bd = karatsuba_mul(b,d),

    ad_plus_bc = diff(karatsuba_mul(sum(a,b), sum(c,d)), sum(ac,bd));

    for(int i=0;i<bd.size();++i){
        res[i]=bd[i];
    }
    for(int i=0;i<ac.size();++i){
        res[i+res.size()-ac.size()]=ac[i];
    }
    for(int i=0; i < ad_plus_bc.size(); ++i){
        res[i+half]+= ad_plus_bc[i];
    }
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
