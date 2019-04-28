#include<iostream>
#include<string.h>
#include <ctime>
#include<fstream>
using namespace std;
class CaseRecord
{
private:
	string record_title;
	string record_number;
	string lawyer;
	string timestamp;
	string description;
	string timestamp_list[100];
	int address_list[100];
	string buffer;
	char timestamp_arr[30];
	time_t now;
	int count;
public:
	void read_data();
	void pack();
	void write_to_file();

	void disp();
	void remove(string);
	void delete_from_file(int);
	void search(string);
	int search_index(string);
	void read_from_file(int);
	void sort_index();

public:
	CaseRecord(string, string, string, string, string);
};
void CaseRecord::read_data()
{
	cout << "Record Title:";
	cin >> record_title;
	cout << "Record Number:";
	cin >> record_number;
	cout << "Lawyer:";
	cin >> lawyer;
	cout << "Description:";
	cin >> description;
	now = time(0);
	timestamp = to_string(now);

}

void CaseRecord::pack()
{
	buffer.erase();
	buffer += timestamp + "|" + record_title + "|" + record_number + "|" + lawyer + "|" + description + "$\n";
}

void CaseRecord::write_to_file()
{
	int pos;
	fstream file;
	file.open("case_file.txt", ios::out | ios::app);
	pos = file.tellp();
	file << buffer;
	file.close();
	timestamp_list[++count] = timestamp;
	address_list[count] = pos;
	sort_index();
}
void CaseRecord::sort_index()
{
	int i, j, temp_address;
	string temp_Name;

	for (int i = 0; i <= count; i++)
	{
		for (int j = i + 1; j <= count; j++)
		{
			if (timestamp_list[i] > timestamp_list[j])
			{
				temp_Name = timestamp_list[i];
				timestamp_list[i] = timestamp_list[j];
				timestamp_list[j] = temp_Name;

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

		if (timestamp_list[mid] == key)
		{
			flag = 1;
			break;
		}
		if (timestamp_list[mid] > key)
			high = mid - 1;
		if (timestamp_list[mid] < key)
			low = mid + 1;
	}
	if (flag)
		return mid;
	else
		return -1;
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
		timestamp_list[i] = timestamp_list[i + 1];
		address_list[i] = address_list[i + 1];
	}
	count--;
}