#include <iostream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
static const int DEBUG = false;
typedef unsigned long long ull;

class BigInt { 
     
  private: 
   
  protected: 

    static const unsigned int MAX_SIZE = 0xffffffff; 
   
    BigInt(const vector<unsigned int>& nums) { numbers = nums; } 
   
  public: 
    friend std::ostream& operator<< (std::ostream& o, const BigInt& fred);
    vector<unsigned int> numbers; 
   
    BigInt split(unsigned int beg, unsigned int end) const { 
        /*  
          Returns bigint represented by a subsequence of the 'digits'. 
        */ 
         if (beg > this->get_size() || beg == end)
           return BigInt(0);
        BigInt res (vector<unsigned int>(numbers.begin() + beg, numbers.begin() + min(end, this->get_size())));
       // cout << "splitting " << this->get_size() << " " << beg << " " << end << " " << res.get_size() << endl;
        return res;
    } 
  
    BigInt(unsigned int x) { 
      numbers.push_back(x); 
    } 

    BigInt() { 
      numbers.push_back(0); 
    } 

      
    BigInt(string s) { 
      //assert (s[0] == '0' && s[1] == 'x');
     // unsigned int x = 0;
      //cout << "S_size " << s.size() << endl;
      char *b = (char *)s.c_str()+s.size()-8;
      //b += 2;

      for (int i = s.size()-8; i > 2; i-=8) {  
        char tmp = b[8];
        b[8] = 0;
        this->numbers.push_back(strtoul(b, 0,16));
        b[8] = tmp;
        b -= 8;
      }
      b = (char *)s.c_str() + 2;
      unsigned int leftover = (s.size()-2) % 8;
      if (!leftover) {
        leftover = 8;
      }
      b[leftover] = 0;
      this->numbers.push_back(strtoul(b, 0,16));
      
    } 
   
    BigInt(string s, unsigned int radix) { 
      //TODO: Implement 
    } 
   
    unsigned int get_size() const { return numbers.size(); } 
   
    unsigned int get_real_size() const {
      int i;
      for (i = get_size()-1; i >= 0 && this->numbers[i] == 0;i--) ;
      if (i+1 == 0)
        i++;
      return i+1;
    }

    void unpad() {
      // delete unimportant zeros
      //cout << "unpadding: " << *this << endl;
      //cout << "RealSize: " << this->get_real_size() << " Size:" << this->get_size() << endl;
      this->numbers.resize(this->get_real_size());
      //cout << "unpadding_outcome: " << *this << endl;
    }

    const bool operator<(const BigInt &b) const { 
      //cout << "B is " << b << " and its' real size is " << b.get_real_size() << endl;
      //cout << "this is " << *this << " and its' real size is " << this->get_real_size() << endl;
      if (b.get_real_size() != this->get_real_size()) {

          return this->get_size() < b.get_size(); 
      }
       
        for (int i = this->get_size() - 1;i >= 0;i--) 
          if (this->numbers[i] != b.numbers[i]) 
            return this->numbers[i] < b.numbers[i]; 
         
        return false; // they are equal 
    } 
   
  const bool operator==(const BigInt &b) const { 
      if (b.get_size() != this->get_size()) 
          return false; 
         
        for (int i = this->get_size() - 1;i >= 0;i--) 
          if (this->numbers[i] != b.numbers[i]) 
            return false; 
         
        return true; // they are equal 
    } 
   
  const bool operator>(const BigInt &b) const { return b < *this;  } 
   
  const BigInt operator+(const BigInt& b) const{ 

      BigInt ret;
      ret.numbers.clear();
      unsigned int carry = 0;
      unsigned int dig = 0;
      unsigned int d1 = 0, d2 = 0;
      unsigned int max_size = max(b.get_size(), this->get_size());
      for (unsigned int i=0; i < max_size; i++) {
        d1 = (i < this->get_size()) ? this->numbers[i] : 0;  
        d2 = (i < b.get_size()) ? b.numbers[i] : 0;
        dig = d1 + d2 + carry;
        ret.numbers.push_back(dig);
        carry = (d1 + d2 + carry < d1);
      }
      if (carry)
        ret.numbers.push_back(carry);
    
      return ret;
    } 
   
  const BigInt& operator=(const BigInt &b) { 
      this->numbers.resize(b.get_size()); 
      for (unsigned int i = 0; i < b.get_size(); i++) 
        this->numbers[i] = b.numbers[i]; 
      return *this; 
    } 

  const BigInt operator-(const BigInt& b) const {
      BigInt this_copy = *this; 
      BigInt b_copy = b; 
      this_copy.unpad();
      //b_copy.unpad();
      //cout << "Minus :) " << this_copy << " - " << b << endl;
      if (this_copy < b_copy)
      {
        cout << "Negative value is not supported " << this_copy << " - " << b_copy << endl;
      }
      //unsigned int min_size = min(b_copy.get_size(), this->get_size()); 
      for (unsigned int i = 0; i < b_copy.get_size(); i++) { 

        if (b_copy.numbers[i] > this_copy.numbers[i]) { 

          if (i+1 < this_copy.get_size()) {  
            this_copy.numbers[i+1] -= 1; 
          } else  { 
            cout << "Not implemented" << i << this_copy.get_size() << endl; 
           // this_copy.numbers.push_back(1); 
          } 

        } 
        this_copy.numbers[i] -= b_copy.numbers[i];  

      } 
      this_copy.unpad(); 
     // cout << "Minus outcome: " << this_copy << endl;
      return this_copy;
  }
  
  
  const BigInt operator*(const BigInt& b) const{ 
      /*  
        Kartsuba Algorithm. 
      */
      //cout << "in mult" << endl;

      BigInt this_copy = *this;
      BigInt b_copy = b;


      this_copy.unpad();
      b_copy.unpad();  
      const BigInt *max = &this_copy, *min = &b_copy;
      if (*min > *max)
      {
        max = &b_copy;
        min = &this_copy;
      }
      if (max->get_size() == 1) {
        unsigned long long mult = ((unsigned long long) max->numbers[0]) * ((unsigned long long)min->numbers[0]);
        this_copy.numbers[0] = mult & 0xffffffff;
        if (mult >> 32)
            this_copy.numbers.push_back(mult >> 32);
        return this_copy;
      }
      
      unsigned int mid = (max->get_size()+1) / 2;
      BigInt max_m = max->split(mid, max->get_size());
      BigInt max_l = max->split(0, mid); 
      BigInt min_m = min->split(mid, min->get_size());
      BigInt min_l = min->split(0, mid); 

      BigInt z1 = max_m * min_m;
      BigInt z2 = max_l * min_l;
      BigInt z3 = (max_m + max_l) * (min_m + min_l);
      //cout << "z3=" << z3 << ", " << "z2=" << z2 << " z1=" << z1 << endl;
      BigInt ans = (z1 << (2*mid)) + (z2) + ((z3 - (z2 + z1)) << mid);
      ans.unpad();

      //cout << "mult: " << *this << " * " << b << " = " << ans << endl;

      return ans;
    } 

    BigInt operator<<(int n) const {
        BigInt this_copy = *this;
        for (int i = 0; i < n;i++)
            this_copy.numbers.insert(this_copy.numbers.begin(), 0);
         return this_copy;
    }

}; 

ostream &operator<<(ostream &os, const BigInt& b) {
  //for (int i = b.get_size()-1; i >= 0;i--)
  //    os << hex << b.numbers[i];
  //return os;

  bool padding_zeros = true; 
    cout << "0x"; 
    for (int i = b.get_size() - 1;i >= 0;i--)  
    { 
      for (int j = 28; j >= 0; j-=4) { 
        unsigned int new_digit = ((b.numbers[i] >> j) & 0x0f); 
        padding_zeros = padding_zeros | new_digit; 
        if (padding_zeros) 
          os << hex << new_digit; 
      } 
    } 
    if (!padding_zeros) // number is 0 
      os << 0;
    return os; 
}

class Mat22{

  protected:
    BigInt a11,a12, a21 ,a22;

  public:
    Mat22() {
      a11 = 0;
      a12 = 1;
      a21 = 1;
      a22 = 1;
    }

    Mat22(BigInt a11, BigInt a12, BigInt a21, BigInt a22) {
      this->a11 = a11;
      this->a12 = a12;
      this->a21 = a21;
      this->a22 = a22;
    }


    Mat22 operator=(const Mat22 &b) {
      if (DEBUG)
        cout << "Copy Construcor()" << endl;
      this->a11 = b.a11;
      this->a12 = b.a12;
      this->a21 = b.a21;
      this->a22 = b.a22;
      return *this;

    }
    Mat22 operator*(const Mat22 &b) {
      if (DEBUG) {
        cout << "Multiplying matricies" << endl;
        this->print_mat(false);
        b.print_mat();
      }
      Mat22 new_mat(a11 * b.a11 + a12 * b.a21, a11 * b.a12 + a12 * b.a22, a21 * b.a11 + a22 * b.a21, a21 * b.a12 + a22 * b.a22);
      return *this = new_mat;
    }

    BigInt mul(BigInt x, BigInt y) {
      if (DEBUG)
      {
        cout << "Multiplying matrix with a vector(" << x << ", " << y << ")" << endl;
        cout << "a11: " << a11 << endl;
              cout << "a12: " << a12 << endl;
              cout << "x: " << x << endl;
              cout << "y: " << y << endl;
      }
      BigInt new_x = (a11 * x) + (a12 * y);
      BigInt new_y = a21 * x + a22 * y;
            
      return new_x;
    }
    Mat22 pow2() {
      if (DEBUG)
        cout << "Powering by 2" << endl;
      *this = *this * *this;
      return *this;
    }

    void print_mat(bool flag=1) const {
      cout << "|" << this->a11 << " " << this->a12 << "|" << endl;
      cout << "|" << this->a21 << " " << this->a22 << "|" << endl;
      if (flag)
        cout << endl;
    }

    Mat22 pow(int n) {
      if (n <= 1)
        return *this;
      if (n%2) {
        Mat22 bkp_mat = *this;
        return *this = pow(n-1)*bkp_mat;
      } else {
        pow2();
        return pow(n/2);
      }
    }

};

BigInt fib(int n) {
  Mat22 a(0, 1, 1, 1);
  a.pow(n);
  //a.print_mat();
  //cout << "The " << dec << n << "# fib number is: " << a.mul(0, 1) << endl;
  return a.mul(0, 1);
}

void dbg() {
  BigInt a11 = 1; //2971215073;
  BigInt a12 = 2; // 2807526976;
  a12 = a12 + 2000000000;
  BigInt x = 0;
  BigInt y = 1;
  BigInt tmp1 = a11 * x;
  BigInt tmp2 = a12 * y;
  cout << "a12:" << a12 << endl;
  cout << "tmp1 + tmp2: " << tmp1 + tmp2 << endl;
  cout << "tmp:" << tmp1 << " tmp2:" << tmp2 << endl;
  cout << "RealSize:"<< tmp1.get_real_size();
}

int main(int argc, char *argv[], char *envp[]) {
  //long long max_longlong = 1;
  //max_longlong = ((max_longlong << 63)-1);
  //cout << max_longlong << endl;
  /*BigInt x, y, z, z2;

  x = 150;
  y = 2500000;
  z = y * y;
  cout << z << endl;
  z = z * z;
    z2 = y * y * y * y;
  cout << z << endl;
  cout << z2 << endl;
  */

  //fib(47);
  cout << fib(20000) << endl;
  //BigInt x = string("0x000000019523a14f41e24f1bf8be54931aab3e85");
  //BigInt y = string("0xfa63c8d9fa216a8fc8a7213b333270f8");
  //cout << x << endl;
  //cout << y << endl;
  //cout << x + y << endl;
  return 0;
}