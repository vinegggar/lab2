#include <iostream>
#include <vector>

using namespace std;

class Mult{
public:
    virtual vector<int> multiply(vector<int>&, vector<int>&)=0;
    void carry_res(vector<int>&res){
        for (int i = 0; i < res.size()-1; ++i) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
};

class NaiveMult: public Mult{
public:
    vector<int> multiply(vector<int>&d1, vector<int>&d2);
};

class Karatsuba: public Mult{
public:
    vector<int>multiply(vector<int>&d1, vector<int>&d2);
};


vector <int> NaiveMult:: multiply(vector<int>&d1,vector<int>&d2){
    vector <int> res(d1.size()+d2.size());
    for (int i=0;i<d1.size();++i){
        for(int j=0;j<d2.size();++j){
            res[i+j]+=d1[i]*d2[j];
        }
    }
    carry_res(res);
    return res;
}

vector<int> Karatsuba::multiply(vector<int> &d1, vector<int> &d2) {
    vector<int>res(d1.size()+d2.size());
    if (d1.size()==1 || d2.size()==1){
        res[0]=d1[0]*d2[0];
    }

}


class Lint{
private:
    vector <int> digits;
    string val;
    static Mult* multer;
public:
    Lint()= default;
    Lint(string val){
        for (int i=int(val.size())-1; i>=0;--i){
            digits.push_back(val[i]-'0');
        }
    }

    bool operator==(Lint& other);
    bool operator !=(Lint other);
    bool operator>(Lint& other);
    bool operator <=(Lint& other);
    bool operator >=(Lint other);
    bool operator<(Lint& other);

    static void setMultMode(Mult *newMulter){
        multer = newMulter;
    }

    Lint operator+(Lint other);
    Lint operator-(Lint other);
    Lint operator *(Lint other);

    friend ostream& operator<<(ostream &out, Lint num);
    friend istream& operator>>(istream &in, Lint& num);
};

/*
 * comparison operators
 */
bool Lint:: operator==(Lint& other) {return digits == other.digits;}

bool Lint::operator!=(Lint other){return !(operator==(other));}
bool Lint::operator >(Lint &other) {
    bool res;
    if (digits.size()!=other.digits.size()){
        res = digits.size() > other.digits.size();
    }
    for (int i=int(digits.size())-1;i>=0;--i){
        if (digits[i] > other.digits[i]){
            res = true; break;
        }
        res = false;
    }
    return res;
}

bool Lint::operator<=(Lint &other) {return not(operator>(other));}

bool Lint:: operator>=(Lint other) {return (operator>(other) or operator==(other));}

bool Lint:: operator<(Lint &other) {return not(operator>=(other));}

/*
 * arithmetic operators
 */
Lint Lint::operator+(Lint other){
    Lint sum;
    int carry = 0;
    int max_size = int(max(digits.size(), other.digits.size()));
    for (int i=0;i< max_size;++i){
        int d = 0;

        if (i<digits.size()) d += digits[i];
        if (i<other.digits.size()) d+=other.digits[i];

        sum.digits.push_back((d+carry+10)%10);
        carry = (d+carry)>=0? (d+carry)/10: -1;
    }
    if(carry){
        cout <<carry<<endl;
        sum.digits.push_back(carry);
    }
    return sum;
}

Lint Lint::operator-(Lint other) {
    if (operator>=(other)){
    for (int & digit : other.digits){
        digit *= -1;
    }
    return operator+(other);
    }
    return {};
}

Lint Lint::operator*(Lint other){
    Lint res;
//    if (digits.size()<8 && other.digits.size()<8){
//        setMultMode(new NaiveMult);
//    }
    res.digits=multer->multiply(digits, other.digits);
    return res;
}

/*
 * i/o stream operators
 */
ostream& operator<<(ostream &out, Lint num){
    int i;
    for (i=0;i<num.digits.size();++i){
        if(num.digits[num.digits.size()-1-i]!=0)break;
    }
    if (i==num.digits.size())out<<"0";
    for (int j=int(num.digits.size())-1-i;j>=0;--j){
        out <<num.digits[j];}
    out<<endl;
    return out;
}

istream& operator>>(istream& in, Lint& num){
    string input;
    in >> input;
    num = Lint(input);
    return in;
}
