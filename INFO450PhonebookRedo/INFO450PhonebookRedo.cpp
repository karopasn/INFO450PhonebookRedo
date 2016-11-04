// INFO450PhonebookRedo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
class phoneBook
{
	char fullName[50];
	char homePhone[15];
	char mobilePhone[15];

public:
	phoneBook();
	void enterphoneBook(char fn[], char hp[], char mp[]);
	void displayphoneBook();
	friend class enterList;
};
phoneBook::phoneBook()
{
	strcpy_s(fullName, "");
	strcpy_s(homePhone, "");
	strcpy_s(mobilePhone, "");
}
void phoneBook::displayphoneBook()
{
	printf("--------------------\n");
	printf("Full name:\n%s\n", fullName);
	printf("Home Phone:\n%s\n", homePhone);
	printf("Mobile Phone\n%s\n: ", mobilePhone);
	printf("--------------------\n");
}
void phoneBook::enterphoneBook(char fn[], char hp[], char mp[])
{
	strcpy_s(fullName, fn);
	strcpy_s(homePhone, hp);
	strcpy_s(mobilePhone, mp);
}
class enterList
{
	char filename[100];
	phoneBook **myList;
	int bookCount;

public:
	void checkList();
	enterList();
	int getCount();
	~enterList();
	void setfileName(char f[]);
	void addList(phoneBook *p);
	void displayList();
	int saveList();
	void readList();
};
enterList::enterList()
{
	myList = new phoneBook*[100];
	bookCount = 0;
}
enterList::~enterList()
{
	delete myList;
}
int enterList::getCount()
{
	return bookCount;
}
void enterList::setfileName(char f[])
{
	strcpy_s(filename, f);
}

void enterList::addList(phoneBook *p)
{
	myList[bookCount] = p;
	bookCount++;
}

void enterList::displayList()
{
	int line = 0;
	int bookNumber = 1;
	for (int i = 0; i < bookCount; i++)
	{
		if (line == 5)
		{
			system("pause");
			system("cls");
			myList[i]->displayphoneBook();
			line = 1;
			bookNumber++;
		}
		else
		{
			myList[i]->displayphoneBook();
			line++;
		}
	}
}
void enterList::checkList()
{
	int i;
	ifstream infile(filename);
	for (i = 1; i <= (bookCount - 1); i++)
	{
		if (strcmp(myList[bookCount - 1]->fullName, myList[(bookCount - 1) - i]->fullName))
		{
			system("pause");
			system("cls");
			cout << "This phonebook entry already exists." << endl;
			cout << "____________________________________" << endl;
			cout << " " << endl;
			bookCount--;
		}
	}
	return;
}
int enterList::saveList()
{
	ofstream outfile(filename);
	if (outfile.bad())
	{
		cout << "Unable to open file" << endl;
		return -1;
	}

	for (int i = 0; i < bookCount; i++)
	{
		outfile << myList[i]->fullName << ",";
		outfile << myList[i]->homePhone << ",";
		outfile << myList[i]->mobilePhone << "," << endl;
	}
	outfile.close();
	return 0;
}

void enterList::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		cout << "File is unreadable." << endl;
		return;
	}

	while (!infile.eof())
	{
		phoneBook *ptr;
		char fullname[50];
		char homephone[15];
		char mobilephone[15];

		infile.getline(fullname, 50, '|');
		if (strlen(fullname))
		{
			infile.getline(homephone, 15, '|');
			infile.getline(mobilephone, 15);
			ptr = new phoneBook();
			ptr->enterphoneBook(fullname, homephone, mobilephone);
			addList(ptr);
		}
	}
	infile.close();
}

int main()
{
	char answer = 'y';
	char fullName[50];
	char homePhone[15];
	char mobilePhone[15];
	char fileName[50];

	enterList *eList = new enterList();
	cout << "Enter the full path file name(Case sensitive)" << endl;
	gets_s(fileName);
	eList->setfileName(fileName);

	eList->readList();
	if (eList->getCount() == 0)
	{
		cout << "File is empty" << endl;
	}
	else
	{
		cout << "There are:" << eList->getCount() << "  entries." << endl;
	}
	cout << "Do you wish to enter a new phonebook entry? Press Y or y to add a new entry." << endl;
	cin >> answer;

	while (answer == 'Y' || answer == 'y')
	{
		if (eList->getCount() >= 100)
		{
			system("pause");
			system("cls");
			cout << "Phonebook is full";
			return 0;
		}
		
		cin.ignore();
		cin.clear();
		system("pause");
		system("cls");
		cout << "New phonebook entry" << endl;
		cout << "___________________" << endl;
		cout << "Enter full name" << endl;
		gets_s(fullName);
		cout << "Enter home phone" << endl;
		gets_s(homePhone);
		cout << "Enter mobile phone" << endl;
		gets_s(mobilePhone);

		phoneBook *myPhoneList = new phoneBook();
		myPhoneList->enterphoneBook(fullName,homePhone, mobilePhone);
		eList->addList(myPhoneList);
		cout << "Would you like to enter another entry?" << endl;
		cout << "Click Y or y to enter another person." << endl;
		cin >> answer;
	}

	eList->displayList();
	eList->saveList();

	return 0;
}