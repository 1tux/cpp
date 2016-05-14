#include "bigint.hh"

BigInt BigInt::split(unsigned int beg, unsigned int end) const {  
    if (beg > this->get_size() || beg == end) 
        return BigInt(0); 
    BigInt res (vector<unsigned int>(numbers.begin() + beg, numbers.begin() + min(end, this->get_size()))); 
    return res; 
}

// constructing BitInt from hexstr
BigInt::BigInt(string s) {
   
      char *b = (char *)s.c_str()+s.size()-8; 

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

unsigned int BigInt::get_real_size() const {
  // skips zeros 
  int i;
  for (i = get_size()-1; i >= 0 && this->numbers[i] == 0;i--) ; 
  if (i+1 == 0) i++; 
  return i+1; 
}

const bool BigInt::operator>(const BigInt &b) const { return b < *this;  }

const bool BigInt::operator<(const BigInt &b) const {  

    if (b.get_real_size() != this->get_real_size()) { 
        return this->get_size() < b.get_size();  
    } 
      
    for (int i = this->get_size() - 1;i >= 0;i--)  
      if (this->numbers[i] != b.numbers[i])  
          return this->numbers[i] < b.numbers[i];  
        
      return false; // they are equal  
}

const bool BigInt::operator==(const BigInt &b) const {  
  if (b.get_size() != this->get_size())  
      return false;  
      
    for (int i = this->get_size() - 1;i >= 0;i--)  
      if (this->numbers[i] != b.numbers[i])  
        return false;  
      
    return true; // they are equal  
}

const BigInt BigInt::operator+(const BigInt& b) const{  

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

const BigInt& BigInt::operator=(const BigInt &b) {  
  this->numbers.resize(b.get_size());  
  for (unsigned int i = 0; i < b.get_size(); i++)  
    this->numbers[i] = b.numbers[i];  
  return *this;  
}


    
  
const BigInt BigInt::operator-(const BigInt& b) const { 
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
   
   
const BigInt BigInt::operator*(const BigInt& b) const{  
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

BigInt BigInt::operator<<(int n) const { 
    BigInt this_copy = *this; 
    for (int i = 0; i < n;i++) 
        this_copy.numbers.insert(this_copy.numbers.begin(), 0); 
     return this_copy; 
} 

ostream &operator<<(ostream &os, const BigInt& b) { 


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

  