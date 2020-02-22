#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void choice(float a, float b, float d){
    float logoritmo = log2(a)/log2(b); //logb de a
    cout<<"O(n^";
    if (d>logoritmo)
      cout<<d<<")\n";
    else if (d==logoritmo)
      cout<<d<<"log(n))\n";
    else
      cout<<"log"<<b<<"("<<a<<"))\n";
}

int main(){
  float a=-1, b=-1, d=-1;  
  while (a!=0){
    cout<<"Teorema Mestre: A*T(n/b)+n^d\n\n";
    cout<< "A: ";
    cin>>a;
    
    if (a!=0){
      cout << "B: ";
      cin>>b;
      cout << "D: ";
      cin>>d;
      choice(a,b,d);
    }
  }
  cout<<"Programa Terminado!\n";
  return 0;
}
