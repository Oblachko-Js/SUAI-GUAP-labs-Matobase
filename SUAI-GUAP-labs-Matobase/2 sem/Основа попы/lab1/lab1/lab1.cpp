#include <cmath> // для функции sqrt()
#include "iostream"
using namespace std;

int main() 
{
  setlocale(LC_ALL, "Russian"); //возможность вывода в консоли русских букв
  float a, z1, z2;
  cout << "Введите число a=";
  cin >> a;
  if (a>0 && a!=2)
	  z1 = (((a+2)/sqrt(2*a))-(a/(sqrt(2*a)+2))+(2/(a-sqrt(2*a))))*((sqrt(a)-
           sqrt(2.))/(a+2));
  else 
  {
	  cout << "Заданные значения не входят в ОДЗ \n";
	  return 0;}
  if (a>=0)
	z2 = 1/(sqrt(a)+sqrt(2.));
  else 
  {
    cout << "Заданные значения не входят в ОДЗ \n";
    return 0;
  }
  cout << "z1=" << z1 << '\n';
  cout << "z2=" << z2 << '\n';
  return 0;
 }