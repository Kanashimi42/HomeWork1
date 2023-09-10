#include "Workers.h"
#include "enum.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void ShowMenu()
{
	cout << EXIT << ". Exit" << endl;
	cout << LOAD_FROM_FILE << ". Load from file" << endl;
	cout << LOAD_TO_FILE << ". Upload to file" << endl;
	cout << SHOW_BOOK << ". Show book" << endl;
	cout << SEARCH_SURNAME_AND_SHOW << ". Search surname" << endl;
	cout << SEARCH_PAYCHECK_AND_SHOW << ". Search paycheck" << endl;
	cout << SORT_SURNAME << ". Sort surname" << endl;
	cout << ADD_NEW_WORKER << ". Add new worker" << endl;
	cout << DELETE_WORKER << ". Delete worker" << endl;

}
//Проверка формата номера, НЕ РАБОТАЕТ
//bool isValidPhoneNumber(const string& phoneNumber) {
//	if (phoneNumber.length() != 13 && phoneNumber.length() != 14) {
//		return false;
//	}
//	if (phoneNumber[0] != '(' || phoneNumber[4] != ')' || phoneNumber[5] != ' ') {
//		return false;
//	}
//	for (int i = 1; i < 4; ++i) {
//		if (!isdigit(phoneNumber[i])) {
//			return false;
//		}
//	}
//
//	for (int i = 6; i < 13; ++i) {
//		if (!isdigit(phoneNumber[i])) {
//			return false;
//		}
//	}
//
//	return true;
//}
void fillInfo(workers& Worker)
{
	cout << "Enter name: " << endl;
	cin >> Worker.name;
	cout << "Enter surname: " << endl;
	cin >> Worker.surname;
	cout << "Enter phonenumber: " << endl;
	cin >> Worker.number;
	cout << "Enter paycheck: " << endl;
	cin >> Worker.paycheck;
}
void printWorkerInfo(const workers& Worker) {
	cout << "Name: " << Worker.name << endl;
	cout << "Surname: " << Worker.surname << endl;
	cout << "Number: " << Worker.number << endl;
	cout << "Paycheck: " << Worker.paycheck << endl;
	cout << "---------------------------" << endl;
}
void ShowBook(const workers Worker[], int numWorkers) {
	cout << "List of all workers:" << endl;
	for (int i = 0; i < numWorkers; ++i) {
		cout << "Worker " << i + 1 << ":" << endl;
		printWorkerInfo(Worker[i]);
	}
}
void DeleteWorker(workers Worker[], int& numWorkers) {
	if (numWorkers == 0) {
		cout << "No workers to delete." << endl;
		return;
	}

	int workerNumber;
	cout << "Enter the number of the worker you want to delete (1 to " << numWorkers << "): ";
	cin >> workerNumber;

	if (workerNumber < 1 || workerNumber > numWorkers) {
		cout << "Invalid worker number." << endl;
		return;
	}
	cout << "Do you want to delete worker " << workerNumber << "? (Enter 1 for yes, 0 for no): ";
	int confirmation;
	cin >> confirmation;

	if (confirmation == 1) {
		for (int i = workerNumber - 1; i < numWorkers - 1; ++i) {
			Worker[i] = Worker[i + 1];
		}

		numWorkers--;
		cout << "Worker " << workerNumber << " has been deleted." << endl;
	}
	else {
		cout << "Deletion canceled." << endl;
	}
}
void SaveToFile(const workers Worker[], int numWorkers, const string& filename) {
	ofstream outputFile(filename.c_str());

	if (!outputFile) {
		cout << "Error opening the file for writing." << endl;
		return;
	}

	for (int i = 0; i < numWorkers; ++i) {
		outputFile << Worker[i].name << endl;
		outputFile << Worker[i].surname << endl;
		outputFile << Worker[i].number << endl;
		outputFile << Worker[i].paycheck << endl;
	}

	outputFile.close();
	cout << "Data saved to " << filename << endl;
}
void LoadFromFile(workers Worker[], int& numWorkers, const string& filename) {
	ifstream inputFile(filename.c_str());
	if (!inputFile) {
		cout << "Error opening the file for reading." << endl;
		return;
	}

	numWorkers = 0;

	while (numWorkers < maxWorkers &&
		inputFile >> Worker[numWorkers].name >>
		Worker[numWorkers].surname >>
		Worker[numWorkers].number >>
		Worker[numWorkers].paycheck) {
		numWorkers++;
	}

	inputFile.close();
	cout << "Data loaded from " << filename << endl;
}
void SearchBySurName(const workers Worker[], int numWorkers) {
	string key;
	cout << "Enter the surname to search for: ";
	cin.ignore();
	getline(cin, key);

	bool found = false;
	for (int i = 0; i < numWorkers; i++) {
		if (Worker[i].surname == key) {
			printWorkerInfo(Worker[i]);
			found = true;
		}
	}

	if (!found) {
		cout << "No matching surnames found." << endl;
	}
}
void SearchByPaycheck(const workers Worker[], int numWorkers) {
	double key;
	cout << "Enter the paycheck to search for: ";
	cin >> key;

	bool found = false;
	for (int i = 0; i < numWorkers; i++) {
		if (Worker[i].paycheck == key) {
			printWorkerInfo(Worker[i]);
			found = true;
		}
	}

	if (!found) {
		cout << "No matching records found." << endl;
	}
}
void sortBySurName(workers Worker[], int numWorkers) {
	for (int i = 1; i < numWorkers; ++i) {
		workers currentWorker = Worker[i];
		int j = i - 1;
		while (j >= 0 && _stricmp(Worker[j].surname, currentWorker.surname) > 0) {
			Worker[j + 1] = Worker[j];
			j--;
		}
		Worker[j + 1] = currentWorker;
	}
}
void Menu(int UserChoice, workers Worker[], int& numWorkers)
{
	string filename;
	switch (UserChoice)
	{

	case EXIT:
		break;
	case LOAD_FROM_FILE:
		cout << "Loading from file..." << endl;
		cout << "Enter the filename to load data from: ";
		cin >> filename;
		LoadFromFile(Worker, numWorkers, filename);
		break;
	case LOAD_TO_FILE:
		cout << "Uploading to file..." << endl;
		cout << "Enter the filename to save data to: ";
		cin >> filename;
		SaveToFile(Worker, numWorkers, filename);
		break;
	case SHOW_BOOK:
		cout << "Showing book..." << endl;
		ShowBook(Worker, numWorkers);
		break;
	case SEARCH_SURNAME_AND_SHOW:
		cout << "Searching by surname..." << endl;
		SearchBySurName(Worker, numWorkers);
		break;
	case SEARCH_PAYCHECK_AND_SHOW:
		cout << "Searching by paycheck..." << endl;
		SearchByPaycheck(Worker, numWorkers);
		break;
	case SORT_SURNAME:
		cout << "Sorting by surname..." << endl;
		sortBySurName(Worker, numWorkers);
		cout << "Workers sorted by surname." << endl;
		break;
	case ADD_NEW_WORKER:
		if (numWorkers < maxWorkers) {
			cout << "Adding new worker..." << endl;
			fillInfo(Worker[numWorkers]);
			numWorkers++;
		}
		else {
			cout << "Cannot add more workers! Maximum workers." << endl;
		}
		break;
	case DELETE_WORKER:
		DeleteWorker(Worker, numWorkers);
	}
}
