#include"Bus.h"


int main()
{
	int count = 0;
	
	FixConsoleWindow();
	BusStation a;
	a.AdminMenu();
	a.CustomerMenu();
	system("pause");
}