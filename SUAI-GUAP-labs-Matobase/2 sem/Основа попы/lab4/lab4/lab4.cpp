// lab4.cpp : Defines the entry point for the console application.
//
#include <cmath> // для функции sqrt()
#include "iostream"
using namespace std;

int main() 
{
	setlocale(LC_ALL, "Russian"); //возможность вывода в консоли русских букв
	float x, x0, x1, dx, a, b, c, f;
	int i;
	cout << "Введите левую границу интервала x0=";
	cin >> x0;
	while (cin.fail())
	{ // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите значение повторно x0: ";
		cin >> x0;
	}
	cout << "Введите правую границу интервала x1=";
	cin >> x1;
	while (cin.fail())
	{ // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите значение повторно x1: ";
		cin >> x1;
	}
	cout << "Введите шаг dx=";
	cin >> dx;
	while (cin.fail())
	{ // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите значение повторно dx: ";
		cin >> dx;
	}
	cout << "Введите параметр а=";
	cin >> a;
	while (cin.fail())
	{ // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите значение повторно a: ";
		cin >> a;
	}
	cout << "Введите параметр b=";
	cin >> b;
	while (cin.fail())
	{ // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите значение повторно b: ";
		cin >> b;
	}
	cout << "Введите параметр c=";
	cin >> c;
	while (cin.fail())
	{ // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите значение повторно c: ";
		cin >> c;
	}
	x = x0;
	i = 0;
	cout << " X      F" << endl;
	while ( x < (x1 + dx/2))   
    { // (x1 + dx/2) - при использовании шага 0,1 или меньше вещественные числа не равны 0,100000000, а на одну миллиардную(или еще меньше) больше
	 if ((x < 0) && (b != 0)) 
	  {  // первый вариант функции
       f = a*x*x + b*x*x;
       printf("%.2f", x);
	   cout << " ";
	   printf("%.2f", f);
	   cout << "" << endl;
      } 
	  else if ((x > 0) && (b == 0))
	          { // второй вариант функции

               if ((x == c) || (abs(x - c) < (dx/100)))
			    { // (abs(x - c) < (dx/100)) - при использовании шага 0,1 или меньше условие x == c не всегда корректно отрабатывало. Поэтому добавили второе условие: (х-с) по модулю стремится к 0
					printf("%.2f", x); 
					cout << " НЗ" << endl;
			    }
			   else 
			     {
				   f = (x - a)/(x - c);
                   printf("%.2f", x);
				   cout << " ";
				   printf("%.2f", f);
				   cout << "" << endl;
			     }
              } 
	         else 
			   {  // все остальные варианты
				   if ((c == 0) || (x == 10)) 
					{
						printf("%.2f", x); 
						cout << " НЗ" << endl;
				    }
				   else 
				    {
					  f = (x + 5)/(c*(x - 10));
                      printf("%.2f", x);
				      printf("%.2f", f);
	                  cout << "" << endl;
                    }
	           }
     x = x + dx;
	 i++;
	 if( i >= 100)
	  {  break;
      }
   }
	return 0;
}