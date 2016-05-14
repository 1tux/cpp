#include "bigint.hh"
#include <iostream>
#include <string>

using namespace std;
typedef unsigned long long ull;

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