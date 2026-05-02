#include <iostream>
#include <string>
#include <algorithm>
int main(){ long long n; if(!(std::cin>>n)) n=42; const char* digits="0123456789ABCDEF"; auto conv=[&](long long x,int b){ if(x==0) return std::string("0"); std::string s; while(x>0){s.push_back(digits[x%b]); x/=b;} std::reverse(s.begin(),s.end()); return s;}; std::cout << "binary " << conv(n,2) << "\nhex " << conv(n,16) << "\n"; }
