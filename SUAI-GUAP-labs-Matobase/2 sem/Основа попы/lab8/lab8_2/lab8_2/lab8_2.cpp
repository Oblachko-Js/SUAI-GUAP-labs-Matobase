#include <Windows.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
int main()
{
  setlocale(LC_ALL, "Russian"); 
  SetConsoleCP(1251); // меняем кодировку для корректной работы с кирилицей
  SetConsoleOutputCP(1251);
  FILE *fr;
  if ((fr = fopen("FileForRead.txt","r"))==NULL) // открываем файл для чтения
  {
   printf("Ошибка при открытии файла FileForRead.txt.\n");
   exit(1);
  }
  else   printf("Файл FileForRead.txt открыт.\n");
  FILE *fw;
  if ((fw = fopen("FileForWrite.txt","w"))==NULL) // открываем файл для записи
  {
   printf("Ошибка при открытии файла FileForWrite.txt.\n");
   exit(1);
  }
  else   printf("Файл FileForWrite.txt открыт.\n");
  char s[100][100];
  int i;
  i = 1;
  while (!feof(fr)) // пока не конец файла для чтения
  {
   fgets(s[i],100,fr); // считываем строку из файла для чтения
   i++;
  } 
  i--;
  i--;
  while (i > 0) // перебираем все строки массива и записываем в файл
  {
   fputs(s[i],fw); // записываем строку в файл для записи
   i--;
  } 
  fclose(fr); //закрываем файл для чтения
  fclose(fw); //закрываем файл для записи
  return 0;
}
