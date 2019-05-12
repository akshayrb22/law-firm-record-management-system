#include <ctime>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

namespace LawFirm
{
class CaseRecord
{
private:
	string record_title;
	string record_number;
	string lawyer;
	// string timestamp;
	string description;
	// string timestamp_list[100];
	int address_list[100];
	string buffer;
	char timestamp_arr[30];
	time_t now;
	int count;
	string record_number_list[100];
	string lawyer_name_list[100];

public:
	void read_data();
	void pack();
	void write_to_file();
	void unpack();
	void extract_lawyer();
	void disp();
	void create_index();
	void remove(string);
	void delete_from_file(int);
	void search(string);
	int search_index(string);
	void read_from_file(int);
	void sort_index();
};

void CaseRecord::read_data()
{
	cin.ignore();
	cout << "Record Number: ";
	getline(cin, record_number, '\n');
	cout << "Record Title: ";
	getline(cin, record_title, '\n');
	cout << "Lawyer: ";
	getline(cin, lawyer, '\n');
	cout << "Description: ";
	getline(cin, description, '\n');
	// now = time(0);
	// timestamp = to_string(now);
}

void CaseRecord::pack()
{
	buffer.erase();
	buffer += record_number + "|" + record_title + "|" + lawyer + "|" + description + "$\n";
}

void CaseRecord::write_to_file()
{
	int pos;
	fstream file;
	file.open("case_file.txt", ios::out | ios::app);
	pos = file.tellp();
	file << buffer;
	file.close();
	record_number_list[++count] = record_number;
	address_list[count] = pos;
	lawyer_name_list[count] = lawyer;
	sort_index();
}
void CaseRecord::unpack()
{
	int ch = 1, i = 0;

	record_number.erase();
	i++;
	while (buffer[i] != '|')
		record_number += buffer[i++];

	record_title.erase();
	i++;
	while (buffer[i] != '|')
		record_title += buffer[i++];

	lawyer.erase();
	i++;
	while (buffer[i] != '|')
		lawyer += buffer[i++];
	
	description.erase();
	while (buffer[i] != '$')
		description += buffer[i++];
	
}
void CaseRecord::extract_lawyer()
{
	lawyer.erase();
	buffer.erase();
	int i = 0, count = 1;
	while(buffer[i++] != '|');
	while(buffer[i++] != '|');
	while(buffer[i] != '|')
		lawyer += buffer[i++];
}
void CaseRecord::sort_index()
{
	int i, j, temp_address;
	string temp;

	for (int i = 0; i <= count; i++)
	{
		for (int j = i + 1; j <= count; j++)
		{
			if (lawyer_name_list[i] > lawyer_name_list[j])
			{
				temp = lawyer_name_list[i];
				lawyer_name_list[i] = lawyer_name_list[j];
				lawyer_name_list[j] = temp;

				temp_address = address_list[i];
				address_list[i] = address_list[j];
				address_list[j] = temp_address;
			}
		}
	}
}

int CaseRecord::search_index(string key)
{
	int low = 0, high = count, mid = 0, flag = 0, pos;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (lawyer_name_list[mid] == key)
		{
			flag = 1;
			break;
		}
		if (lawyer_name_list[mid] > key)
			high = mid - 1;
		if (lawyer_name_list[mid] < key)
			low = mid + 1;
	}
	if (flag)
		return address_list[mid];
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
		cout << endl
			 << "Record not found" << endl;
	else if (pos >= 0)
	{
		file.open("case_file.txt");
		address = address_list[pos];
		file.seekp(address, ios::beg);
		getline(file, buffer);
		cout << "Record found:\n";
		unpack();
		cout << "Record Number: " << record_number <<endl;
		cout << "Record Tile: " << record_title <<endl;
		cout << "Lawyer: " << lawyer << endl;
		cout << "Description: " << description << endl;
		file.close();
	}
}
void CaseRecord::delete_from_file(int pos)
{
	int i, address;
	fstream file;
	file.open("case_file.txt");
	address = address_list[pos];
	file.seekp(address, ios::beg);
	file.put('*');
	cout << "\nRecord Deleted: ";

	for (i = pos; i < count; i++)
	{
		// record_number_list[i] = record_number_list[i + 1];
		address_list[i] = address_list[i + 1];
		lawyer_name_list[i] = lawyer_name_list[i + 1];
	}
	count--;
}

void CaseRecord::create_index()
{
	fstream file;
	int pos;
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
			// unpack();
			extract_lawyer();
			address_list[++count] = pos;
			// record_number_list[count] = record_number;
			lawyer_name_list[count] = lawyer;

		}
	}
	file.close();
	sort_index();
	buffer.erase();
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
		cout << "\nRecord Deleted: ";

		for (i = pos; i < count; i++)
		{
			lawyer_name_list[i] = lawyer_name_list[i + 1];
			address_list[i] = address_list[i + 1];
		}
		count--;
	}
	else
		cout << "Record not found\n";
}
void CaseRecord::disp()
{
	int i;
	cout << endl
		 << "INDEX FILE " << endl
		 << "LAWYER\tADDRESS";
	for (i = 0; i <= count; i++)
		cout << endl
			 << lawyer_name_list[i] << "\t" << address_list[i];
	cout << "\n";
	system("cat case_file.txt");
}
} // namespace LawFirm
