//                 aboutstring.cpp 2018
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(){
  string s;
//----------------- PART 1 -------------------
 cout<<"PART 1\n";
 for (int i=0;i<20;++i){
     cout <<(void*)s.data()<<" : "<<setw(6)<<s.capacity()<<
      " : " <<setw(2)<<s.size()<<" : "<< s << endl;
     s+="*";
 }
cout<<"\n\n";
s.reserve(s.size());
     cout <<(void*)s.data()<<" : "<<setw(6)<<s.capacity()<<
      " : " <<setw(2)<<s.size()<<" : "<< s << endl;
cout<<"\n\n";
//----------------- PART 2 -------------------
 cout<<"PART 2\n";
 string a(s);
     cout <<(void*)a.data()<<" : "<<setw(6)<<a.capacity()<<
      " : " <<setw(2)<<a.size()<<" : "<< a << endl;
  a+="#";
     cout <<(void*)a.data()<<" : "<<setw(6)<<a.capacity()<<
      " : " <<setw(2)<<a.size()<<" : "<< a << endl;
     cout <<(void*)s.data()<<" : "<<setw(6)<<s.capacity()<<
      " : " <<setw(2)<<s.size()<<" : "<< s << endl;

cin.get();
return 0;
}
