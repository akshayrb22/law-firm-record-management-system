
// main()
// {
// 	while(1)
// 	{
// 		system("figlet -cf big Law Firm Record Management System");
// 		cout << "Press \'Return\' to continue." << endl;
// 		cin.clear();
// 		cin.get();

// 		initscr();
// 		noecho();
// 		cbreak();
// 		getch();
// 		int yMax, xMax, count;
// 		CaseRecord caseRecord;
// 		string key;
// 		getmaxyx(stdscr, yMax, xMax);

// 		WINDOW *menuWindow = newwin(10, 30, 5, 5);
// 		box(menuWindow, 0, 0);
// 		refresh();
// 		wrefresh(menuWindow);
// 		keypad(menuWindow, true);

// 		string choices[4] = {"ADD", "SEARCH", "DELETE", "EXIT"};
// 		int choice;
// 		int highlight = 0;
// 		while (1)
// 		{
// 			for (int i = 0; i < 4; i++)
// 			{
// 				if (i == highlight)
// 				{
// 					wattron(menuWindow, A_REVERSE);
// 				}
// 				mvwprintw(menuWindow, i + 1, 1, choices[i].c_str());
// 				wattroff(menuWindow, A_REVERSE);
// 			}
// 			choice = wgetch(menuWindow);
// 			switch (choice)
// 			{
// 				case KEY_UP:
// 					highlight--;
// 					if (highlight == -1) highlight = 0;
// 					break;
// 				case KEY_DOWN:
// 					highlight++;
// 					if (highlight == 4) highlight = 3;
// 				default:
// 					break;
// 			}
// 			if (choice == 10) break;
// 		}
// 		printw("Your choice is: %s", choices[highlight].c_str());

// 		WINDOW *choiceWindow = newwin(30, 70, 0, 0);
// 		system("clear");
// 		switch (highlight)
// 		{
// 			case 0:
// 				mvwprintw(choiceWindow, 1, 1, "\nEnter the number of records to insert:");
// 				count = wgetch(choiceWindow);
// 				for (int i = 0; i < count; i++)
// 				{
// 					mvwprintw(choiceWindow, 1, 1, "Data\n");
// 					clear();
// 					caseRecord.read_data();
// 					caseRecord.pack();
// 					caseRecord.write_to_file();
// 				}
// 				break;
// 			case 1:
// 				clear();
// 				caseRecord.disp();
// 				mvwprintw(choiceWindow, 1, 1, "\nEnter the name of the lawyer you want to search:");
// 				key = wgetch(choiceWindow);
// 				caseRecord.search(key);
// 				break;
// 			case 2:
// 				mvwprintw(choiceWindow, 1, 1, "\nEnter the name whose details you want to remove:");
// 				key = wgetch(choiceWindow);
// 				caseRecord.remove(key);
// 				break;
// 			case 3:
// 				return 0;
// 			default:
// 				std::cout << "\n\nWrong choice\n";
// 				break;
// 		}
// 		getch();
// 		endwin();
// 	}
// 	return 0;
// }