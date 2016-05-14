#include <iostream> 
#include <vector> 
#include <string>  

static const int DEBUG = false; 

class BigInt {  
      
  private:  
    vector<unsigned int> numbers;
    static const unsigned int MAX_SIZE = 0xffffffff;

    // Returns bigint represented by a subsequence of the 'digits'.
    BigInt split(unsigned int beg, unsigned int end) const;

    unsigned int get_size() const { return numbers.size(); }

    // remove leading zeros
    void unpad() { this->numbers.resize(this->get_real_size()); }

    // returns size of BigInt while not counting leading zeros.

    
  public:  
    BigInt(unsigned int x) { numbers.push_back(x); }  
    BigInt() { numbers.push_back(0); }
    BigInt(const vector<unsigned int>& nums) { numbers = nums; }  
    BigInt(string s);  
    BigInt(string s, unsigned int radix);

    unsigned int get_real_size() const;

    const bool operator<(const BigInt &b) const;
    const bool operator==(const BigInt &b) const;
    const bool operator>(const BigInt &b) const;
    const BigInt operator+(const BigInt& b) const;  
    const BigInt& operator=(const BigInt &b);
    const BigInt operator-(const BigInt& b) const;
    const BigInt operator*(const BigInt& b) const;
    BigInt operator<<(int n) const;
    friend std::ostream& operator<< (std::ostream& o, const BigInt& fred); 

};  

ostream &operator<<(ostream &os, const BigInt& b);