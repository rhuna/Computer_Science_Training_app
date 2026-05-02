#include <iostream>
#include <string>
int main(){ long long n=42; if(!(std::cin>>n)) n=42; std::string b; for(long long x=n;x>0;x/=2) b=char(48+x%2)+b; if(b.empty()) b="0"; std::cout<<b<<"\n"; const char* h="0123456789ABCDEF"; std::string hx; for(long long x=n;x>0;x/=16) hx=h[x%16]+hx; if(hx.empty()) hx="0"; std::cout<<hx<<"\n"; }
