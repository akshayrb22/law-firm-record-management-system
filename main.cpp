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
int main()
{
	scroll_note();

	CaseRecord caseRecord;
	caseRecord.create_index();
	int choice, count, mod_choice;
	string key;
	while (1)
	{
		std::cout << "\nMain Menu\n\n1. Add\t2. Search\t3. Delete\t4. Modify\t5. Exit\n";
		std::cout << "Enter the choice:";
		cin >> choice;
		switch (choice)
		{
			case 1:
				std::cout << "Data Entry\n";
				caseRecord.read_data();
				caseRecord.pack();
				caseRecord.write_to_file();
				break;
			case 2:
				caseRecord.disp();
				std::cout << "\nEnter the name of the lawyer whose details you want to view: ";
				cin >> key;
				caseRecord.search(key);
				break;
			case 3:
				std::cout << "\nEnter the name of the lawyer whose details you want to delete: ";
				cin >> key;
				if(caseRecord.remove(key)) std::cout << "Record deleted.";
				else std::cout << "Record not found.";
				break;
			case 4:
				std::cout << "Enter the name of the lawyer whose details you want to modify: ";
				cin >> key;
				caseRecord.modify(key);
				std::cout << "Case Record modified.";
				break;
			case 5:
				return 0;
			default:
				std::cout << "\n\nWrong choice\n";
				break;
		}
	}
}