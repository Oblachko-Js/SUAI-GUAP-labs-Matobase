// lab5 - Работа с массивами
// Для обнаружения утечек памяти
#define _CRTDBG_MAP_ALLOC
#include <stdlib>
#include <crtdbg>
#include <ctime>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include <cmath>
#include <iostream>
using namespace std;
double find_sum_after(const double m[], const size_t n, const size_t k);
double find_last_neg(const double m[], const size_t n);
double count_less_c(const double m[], const size_t n, const double c);
void change_array(double m[], const size_t n);
void input_array(double m[], const size_t n);
void input_array_rand(double m[], const size_t n);
void output_array(double m[], const size_t n);
void output_array_line(double m[], const size_t n);

int main() 
{
	setlocale(LC_ALL, "Russian"); //возможность вывода в консоли русских букв
	size_t n;
	double c;
    cout << "Введите размер массива: ";
    cin>>n;
	while (n < 0 || n > 100 || cin.fail())
	 { // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите повторно n: ";
		cin >> n;
	 }
	cout << "Введите число С: "; 
	// Задание №1. Найти количество элементов массива, меньших чем С
    cin>>c;
	while (c < -100 || c > 100 || cin.fail())
	 { // проверка на ввод чисел
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите повторно C: ";
		cin >> c;
	 }
    double *m = new double[n+1];
	input_array_rand(m, n);
	cout << "Количество элементов меньше С равна " << count_less_c(m, n, c) << endl;
	// Задание №2. Найти номер последнего отрицательного элемента и сумму целых частей элементов после этого элемента
	if (find_last_neg(m, n) == 0)
	 {
		cout << "Отрицательные элементы отсутствуют! " << endl;
	 }
	else
	 {
	   cout << "Номер последнего отрицательного элемента: " << find_last_neg(m, n) << endl;
	   cout << "Сумма целых частей элементов после последнего отрицательного элемента: " << find_sum_after(m, n, find_last_neg(m, n)+1) << endl;
	 }
	// выводим массив на экран в строку
  	cout << "Исходный массив: " << endl;
	output_array_line(m, n);
	cout << "Измененный массив: " << endl;
	// Задание №3. Преобразовать массив таким образом, чтобы сначала располагались все элементы,отличающиеся от максимального не более чем на 20%, а потом – все остальные.
	change_array(m, n);
	output_array_line(m, n);
    // если убрать следующую строку, то в конечном итоге ПО выдаст ошибку об утечке памяти
	delete[]m;
   // Для обнаружения утечек памяти
   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
   _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
   _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
   _CrtDumpMemoryLeaks(); 
  return 0;
}

double find_sum_after(const double m[], const size_t n, const size_t k)
 {
	double sum = 0;
	double intpart, fractpart; 
	for (size_t i=k; i<=n; i++)
	{
	  fractpart = modf(m[i], &intpart); 
	  sum += intpart;
	}
    return sum;
 }

double find_last_neg(const double m[], const size_t n)
 {
	int count = 0;
	double sum = 0;
	for (size_t i=1; i<=n; i++)
	  if (m[i] < 0)
        count = i;
    return count;
 }

double count_less_c(const double m[], const size_t n, const double c)
 {
	int count = 0;
	for (size_t i=1; i<=n; i++)
	  if (m[i] < c)
      count++;
    return count;
 }

void change_array(double m[], const size_t n)
 {
	double ar_max = m[1];
	for (size_t i=2; i<=n; i++)
	 if (m[i] > ar_max)
       ar_max = m[i];
	for (size_t i=2; i<=n; i++)
	 if ((abs((m[i]/ar_max) - 1)) <= 0.2)
	  {
     	  m[0] = m[i];	
		  for (size_t j=i; j>=1; j--)
		   m[j] = m[j-1];
      }
 }

void input_array(double m[], const size_t n)
 {
	m[0] = 0;
	for (size_t i=1; i<=n; i++)
     {
      cout << "Введите m[" << i << "]: ";
      cin >> m[i];
	 }
 }

void input_array_rand(double m[], const size_t n)
 {
	 // ввод массива случайным способом в диапазоне от -50 до 50
	m[0] = 0;
	srand((unsigned int)time(NULL));
	// если убрать строчку выше, то будут генерироваться одни и те же числа
    for (size_t i=1; i<=n; i++)
     m[i] = rand() % 101 - 50;
 }

void output_array_line(double m[], const size_t n)
 {
	for (size_t i=1; i<=n; i++)
		cout << m[i] << " ";
	cout << endl;
 }

void output_array(double m[], const size_t n)
 {
	 for (size_t i=1; i<=n; i++)
		cout << "m[" << i << "] = " << m[i] << endl;
 }