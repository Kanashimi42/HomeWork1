#pragma once
#include <string>
using namespace std;
const int maxWorkers = 10;

struct workers
{
	char* name = new char[128];
	char* surname = new char[128];
	char* number = new char[128];
	double paycheck;

};

void ShowMenu();
//bool isValidPhoneNumber(const string& phoneNumber);
void fillInfo(workers& Worker);
void printWorkerInfo(const workers& Worker);
void ShowBook(const workers Worker[], int numWorkers);
void DeleteWorker(workers Worker[], int& numWorkers);
void SaveToFile(const workers Worker[], int numWorkers, const string& filename);
void LoadFromFile(workers Worker[], int& numWorkers, const string& filename);
void SearchBySurName(const workers Worker[], int numWorkers);
void SearchByPaycheck(const workers Worker[], int numWorkers);
void sortBySurName(workers Worker[], int numWorkers);
void Menu(int UserChoice, workers Worker[], int& numWorkers);
