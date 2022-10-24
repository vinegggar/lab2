#include<vector>
using namespace std;

vector<int> naive_multiplication(vector<int>&d1,vector<int>&d2){
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

vector<int> diff(vector<int>&d1, vector<int>&d2){
    for(int &i: d2)i*=-1;
    return sum(d1,d2);
}

/*
 * returns (ac*(10^(2*half)))+((ad+bc)*10^half)+bd
 * ad+bc counts as (a+b)*(c+d)-ac-bd
 */
vector<int> karatsuba_mul(vector<int>&d1, vector<int>&d2){
    if(d1.size()<=1 && d2.size()<=1) return {d1[0]*d2[0]};

    while (d1.size()!=d2.size())
    {d1.size()>d2.size()?d2.push_back(0):d1.push_back(0);}

    int half = d1.size()/2;

    vector<int> res (2*d1.size()-1);

    vector<int> a = {d1.begin()+half,d1.end()}, //right part of d1
    b = {d1.begin(), d1.begin()+half}, //left
    c = {d2.begin()+half,d2.end()}, //right part of d2
    d = {d2.begin(), d2.begin()+half}, //left

    ac = karatsuba_mul(a,c), bd = karatsuba_mul(b,d),

    ac_plus_bd= sum(ac, bd),
    a_plus_b = sum(a,b), c_plus_d = sum(c, d),
    sum_prod = karatsuba_mul(a_plus_b, c_plus_d),
    ad_plus_bc = diff(sum_prod, ac_plus_bd);

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

