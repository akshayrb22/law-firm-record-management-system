#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <ncurses.h>

using namespace std;
namespace LawFirm
{
class CaseRecord
{
public:
	string lawyer;
	string title;
	string code;
	string description;
	string buffer;

	string lawyer_list[100];
	int address_list[100];
	int count;

	void read_data();
	void pack();
	void write_to_file();

	void create_index();

	void remove(string);
	void search(string);
	int search_index(string);
	string extract_lawyer();
	void sort_index();
	void disp();
	void unpack();
};
void CaseRecord::read_data()
{
	std::cin.get();
	std::cin.clear();
	std::cout << "Lawyer: ";
	getline(cin, lawyer, '\n');
	std::cout << "Title: ";
	getline(cin, title, '\n');
	std::cout << "Code: ";
	getline(cin, code, '\n');
	std::cout << "Description: ";
	getline(cin, description, '\n');
}

void CaseRecord::pack()
{
	buffer.erase();
	buffer += lawyer + "|" + title + "|" + code + "|" + description + "$\n";
}

void CaseRecord::write_to_file()
{
	int pos;
	fstream file;
	file.open("case_file.txt", ios::out | ios::app);
	pos = file.tellp();
	file << buffer;
	file.close();

	lawyer_list[++count] = lawyer;
	address_list[count] = pos;
	sort_index();
}

string CaseRecord::extract_lawyer()
{
	string lawyer;
	int i = 0;

	lawyer.erase();
	while (buffer[i] != '|')
		lawyer += buffer[i++];
	return lawyer;
}
void CaseRecord::unpack()
{
	int i = 0;
	lawyer.erase();
	while (buffer[i] != '|')
		lawyer += buffer[i++];

	title.erase();
	i++;
	while (buffer[i] != '|')
		title += buffer[i++];

	code.erase();
	i++;
	while (buffer[i] != '|')
		code += buffer[i++];

	description.erase();
	i++;
	while (buffer[i] != '$')
		description += buffer[i++];
}
void CaseRecord::create_index()
{
	fstream file;
	int pos;
	string lawyer;
	count = -1;
	file.open("case_file.txt", ios::in);
	while (!file.eof())
	{
		pos = file.tellg();
		buffer.erase();
		getline(file, buffer);

		if (buffer[0] != '*')
		{
			if (buffer.empty())
				break;
			lawyer = extract_lawyer();
			lawyer_list[++count] = lawyer;
			address_list[count] = pos;
		}
	}
	file.close();
	sort_index();
	buffer.erase();
}

void CaseRecord::sort_index()
{
	int i, j, temp_address;
	string temp_lawyer;

	for (int i = 0; i <= count; i++)
	{
		for (int j = i + 1; j <= count; j++)
		{
			if (lawyer_list[i] > lawyer_list[j])
			{
				temp_lawyer = lawyer_list[i];
				lawyer_list[i] = lawyer_list[j];
				lawyer_list[j] = temp_lawyer;

				temp_address = address_list[i];
				address_list[i] = address_list[j];
				address_list[j] = temp_address;
			}
		}
	}
	for (i = 0; i <= count; i++)
	{
		std::cout << lawyer_list[i] << "\t" << address_list[i] << "\n";
	}
}

int CaseRecord::search_index(string key)
{
	int low = 0, high = count, mid = 0, flag = 0, pos;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (lawyer_list[mid] == key)
		{
			flag = 1;
			break;
		}
		if (lawyer_list[mid] > key)
			high = mid - 1;
		if (lawyer_list[mid] < key)
			low = mid + 1;
	}

	if (flag)
		return mid;
	else
		return -1;
}

void CaseRecord::search(string key)
{
	int pos = 0, address;
	fstream file;
	buffer.erase();
	pos = search_index(key);
	if (pos == -1)
		std::cout << endl
			 << "Record not found." << endl;
	else if (pos >= 0)
	{
		file.open("case_file.txt");
		address = address_list[pos];
		file.seekp(address, ios::beg);
		getline(file, buffer);
		unpack();
		std::cout << "Record found" << endl
			 << "Lawyer: 	" << lawyer << endl
			 << "Title: 		" << title << endl
			 << "Case Code: 	" << code << endl
			 << "Description: 	" << description << endl;
		file.close();
	}
}

void CaseRecord::remove(string key)
{
	int pos = 0, i, address;
	fstream file;
	pos = search_index(key);
	if (pos >= 0)
	{
		file.open("case_file.txt", ios::out | ios::in);
		address = address_list[pos];
		file.seekp(address, ios::beg);
		file.put('*');
		file.close();
		std::cout << "\nRecord Deleted: ";

		for (i = pos; i < count; i++)
		{
			lawyer_list[i] = lawyer_list[i + 1];
			address_list[i] = address_list[i + 1];
		}
		count--;
	}
	else
		std::cout << "Record not found\n";
}
void CaseRecord::disp()
{
	int i;
	std::cout << endl
		 << "INDEX FILE " << endl
		 << "LAWYER\tADDRESS";
	for (i = 0; i <= count; i++)
		std::cout << endl
			 << lawyer_list[i] << "\t" << address_list[i];
	std::cout << "\n";
}

} // namespace LawFirm