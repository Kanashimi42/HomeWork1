#include "workers.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	workers Worker[maxWorkers];
	int numWorkers = 0;

	int UserChoice;
	do
	{
		ShowMenu();
		cin >> UserChoice;
		Menu(UserChoice, Worker, numWorkers);
	} while (UserChoice != 0);
}