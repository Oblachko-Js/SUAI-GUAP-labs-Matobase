#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <Windows.h>
using namespace std;
int main()
{
  setlocale(LC_ALL, "Russian"); 
  fstream fr("FileForRead.txt", ios::out | ios::in); // открываем файл для чтения
  fstream fw("FileForWrite.txt", ios::out); // открываем файл для записи
  if (!fr.is_open()) // проверка открытия файла для чтения
  {
		cout << "Ошибка открытия файла для чтения!" << endl;
  }
  else 
  {
	 	cout << "Файл FileForRead открыт!" << endl;
  }
  if (!fw.is_open()) // проверка открытия файла для записи
  {
		cout << "Ошибка открытия файла для записи!" << endl;
  }
  else 
  {
	 	cout << "Файл FileForWrite открыт!" << endl;
  }
  string s[50];
  int i;
  i = 0;
  SetConsoleCP(1251); // меняем кодировку для корректной работы с кирилицей
  SetConsoleOutputCP(1251);
  while (!fr.eof()) // пока не конец файла для чтения
	{
	  getline(fr,s[i]); // считываем инфу (построчно) из файла для чтения
	  i ++;
	}
  i--;
  while (i >= 0)
	{
	  fw << s[i] << "\n"; // записываем считанные строки в файл для записи в обратном порядке
	  i --;
	}
  SetConsoleCP(866); // возвращаем кодировку как было до начала выполнения этой программы
  SetConsoleOutputCP(866);
  fr.close(); //закрываем файл для чтения
  fw.close(); //закрываем файл для записи
  if (!fr.is_open()) // проверка открытия файла для чтения
  {
		cout << "Файл FileForRead закрыт!!" << endl;
  }
  else 
  {
	 	cout << "Файл FileForRead открыт!" << endl;
  }
  if (!fw.is_open()) // проверка открытия файла для чтения
  {
		cout << "Файл FileForWrite закрыт!!" << endl;
  }
  else 
  {
	 	cout << "Файл FileForWrite открыт!" << endl;
  }
  return 0;
}