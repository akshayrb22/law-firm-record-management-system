#include "CaseRecord.h"
#include <iostream>
#include <string.h>
using namespace std;
using namespace LawFirm;
void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}
void scroll_note() //welcome note
{
	system("color 0A");
	int j, i, x, y;
	for (i = 0; i < 46; i++)
	{
		gotoxy(i, 13);
		cout << " ";
		cout << "BUS MANAGEMENT SYSTEM";
		// Sleep(40);
	}
	gotoxy(46, 13);
	cout << "BUS MANAGEMENT SYSTEM";
	gotoxy(116, 20);
	cout << "";
	gotoxy(116, 4);
	cout << "";
	for (int j = 120; j >= 0; j--)
	{
		gotoxy(j, 20);
		cout << "<";
		gotoxy(j, 4);
		cout << "<";
		// Sleep(15);
	}
	for (int j = 19; j >= 5; j--)
	{
		gotoxy(0, j);
		cout << "^";
		gotoxy(119, j);
		cout << "^";
		// Sleep(15);
	}
	gotoxy(86, 23);
	cout << "Gautham G Rao    4SF15IS028";
	gotoxy(86, 24);
	cout << "Mohamadh Suhail  4SF15IS102";
	// Sleep(2000);s
	// getch();
}
main()
{
	// gotoxy(100, 100);
	CaseRecord caseRecord;
	// system("figlet -cf big Law Firm Record Management System");
	caseRecord.create_index();
	int choice, count;
	string key;
	while (1)
	{
		cout << "\nMain Menu\n\n1.Add \t2.Search \t3.Delete\t4.Exit\n";
		cout << "Enter the choice:";
		cin >> choice;
		switch (choice)
		{
			case 1:
				cout << "\nEnter the number of records to insert:";
				cin >> count;
				for (int i = 0; i < count; i++)
				{
					cout << "Data\n";
					caseRecord.read_data();
					caseRecord.pack();
					caseRecord.write_to_file();
				}
				break;
			case 2:
				// system("clear");
				caseRecord.disp();
				cout << "\nEnter the name of the lawyer:";
				cin >> key;
				caseRecord.search(key);
				break;
			case 3:
				cout << "\nEnter the name:";
				cin >> key;
				caseRecord.remove(key);
				break;
			case 4:
				return 0;
			default:
				cout << "\n\nWrong choice\n";
				break;
		}
	}
}