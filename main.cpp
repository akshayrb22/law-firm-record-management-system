#include "CaseRecord.h"
#include <curses.h>
#include <iostream>
#include <map>
#include <string.h>
#include <unistd.h>
using namespace std;
using namespace LawFirm;

void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}
void scroll_note() //welcome note
{
	system("figlet -cf big -t Law Firm Record Management System");
	std::cout << "Press \'Return\' to continue." << endl;
	std::cin.clear();
	std::cin.get();
	initscr();
	noecho();

	mvprintw(30, 23, "A K Harshith	4SF16IS001");
	mvprintw(31, 23, "Akshay Ram Bhat	4SF16IS011");
	mvprintw(32, 23, "Press Enter to continue");
	getch();
	endwin();
}
main()
{
	scroll_note();

	CaseRecord caseRecord;
	// system("figlet -cf big Law Firm Record Management System");

	caseRecord.create_index();
	int choice, count;
	string key;
	while (1)
	{
		std::cout << "\nMain Menu\n\n1.Add \t2.Search \t3.Delete\t4.Exit\n";
		std::cout << "Enter the choice:";
		cin >> choice;
		switch (choice)
		{
			case 1:
				std::cout << "\nEnter the number of records to insert:";
				cin >> count;
				for (int i = 0; i < count; i++)
				{
					std::cout << "Data\n";
					caseRecord.read_data();
					caseRecord.pack();
					caseRecord.write_to_file();
				}
				break;
			case 2:
				// system("clear");
				caseRecord.disp();
				std::cout << "\nEnter the name of the lawyer:";
				cin >> key;
				caseRecord.search(key);
				break;
			case 3:
				std::cout << "\nEnter the name:";
				cin >> key;
				caseRecord.remove(key);
				break;
			case 4:
				return 0;
			default:
				std::cout << "\n\nWrong choice\n";
				break;
		}
	}
	endwin();
}