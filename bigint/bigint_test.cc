#include "bigint.hh"
#include <iostream>
using namespace std;

int main(int argc, char *argv[], char *envp[]) { 

  BigInt x("0x123456789"), y("0xaabbccddeeff"), mul("0xc241c38b6c6b35a87f77");
  cout << (((x * y) == mul) ? "True" : "False") << endl;
  return 0; 
}