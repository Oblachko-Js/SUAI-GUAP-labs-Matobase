int main (void) 
{
		volatile unsigned char a1=0xB3;
		volatile unsigned char b1=0xB3;
		volatile unsigned char c1=0xB3;
		volatile unsigned char d1=0xB3;
		volatile unsigned short a2=0xB3B3;
		volatile unsigned short b2=0xB3B3;
		volatile unsigned short c2=0xB3B3;
		volatile unsigned short d2=0xB3B3;
		volatile unsigned int a4=0xB3B3B3B3;
		volatile unsigned int b4=0xB3B3B3B3;
		volatile unsigned int c4=0xB3B3B3B3;
		volatile unsigned int d4=0xB3B3B3B3;
		volatile unsigned long long a8=0xB3B3B3B3B3B3B3B3;
		volatile unsigned long long b8=0xB3B3B3B3B3B3B3B3;
		volatile unsigned long long c8=0xB3B3B3B3B3B3B3B3;
		volatile unsigned long long d8=0xB3B3B3B3B3B3B3B3;
		volatile char name1[]="Andrey";
		volatile char name2[]="Panchenko";
		volatile char name3[]="4236";
		for(;;){}
		return 0;
}