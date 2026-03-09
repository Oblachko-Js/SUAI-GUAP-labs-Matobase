#include<iostream>
#include<locale>
using namespace std;
int main()
{
  setlocale(LC_ALL, "Russian"); //возможность вывода в консоли русских букв
 // char text[] = "This is the string, where we will find out necessary symbol!!!!";
  char text[100];
  char text_f[] = "";
  cout << "¬ведите исходную строку:";
  cin.getline(text,100);
  cout << "¬ведите символ, который нужно удалить:";
  cin>>text_f[0];
  int i = 0;
  int j = 0;
  int len = sizeof(text);
  cout << "»сходный текст:";
  for (i=0; i<=len; i++)
  {
    cout << text[i];
	if ((int)(text[i]) == 0)
		{
		  len = i;
	      break;
		}
  }
  cout << endl;
  cout << endl;
  bool find_from_begin = false;
  bool find_from_end = false;
  for (i=0; i<=len; i++)
	if (text[i] == text_f[0])
	{
      for (j=i; j<=(len-1); j++)
		  text[j] = text [j+1];
	  len--;
	  find_from_begin = true;
	  break;
	}
  if (find_from_begin == true)
   {
	 for (i=len; i>=0; i--)
      if (text[i] == text_f[0])
	    {
		  for (j=i; j<=(len-1); j++)
		    text[j] = text [j+1];
	      len--;
	      find_from_end = true;
	      break;
	    }
   }
  if (find_from_begin == true)
    if (find_from_end == false)  
     {
		cout << "¬веденный символ в исходной строке встречаетс€ только 1 раз!" << endl;
		cout << endl;
		cout << "»змененный текст:";
		for (i=0; i<=len; i++)
			cout << text[i];
		cout << endl;
      } 
	else 
      {
		cout << "»змененный текст:";
		for (i=0; i<=len; i++)
			cout << text[i];
		cout << endl;
      } 
   else
    cout << "¬веденный символ в исходной строке отсутствует!" << endl;
  return 0;
}