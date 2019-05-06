#include <iostream>
#include <string.h>
#include <ctime>
#include <fstream>
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
	string record_number_list[100];
	int address_list[100];

public:
	void read_data();
	void pack();
	void write_to_file();
	string extract_timestamp();
	void disp();
	void create_index();
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
	buffer += timestamp + "|" + record_number + "|" + record_title + "|" + lawyer + "|" + description + "$\n";
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
string CaseRecord::extract_timestamp()
{

	string timestamp;
	int i = 0;

	timestamp.erase();
	while (buffer[i] != '|')
		timestamp += buffer[i++];
	return timestamp;
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
		file.open("5.txt");
		address = address_list[pos];
		file.seekp(address, ios::beg);
		getline(file, buffer);
		cout << "Record found....\n"
			 << buffer;
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
		timestamp_list[i] = timestamp_list[i + 1];
		address_list[i] = address_list[i + 1];
	}
	count--;
}

void CaseRecord::create_index()
{
	fstream file;
	int pos;
	string time_stamp;
	count = -1;
	file.open("case_record.txt", ios::in);
	while (!file.eof())
	{
		pos = file.tellg();
		buffer.erase();
		getline(file, buffer);

		if (buffer[0] != '*')
		{
			if (buffer.empty())
				break;

			time_stamp = extract_timestamp();
			timestamp_list[++count] = time_stamp;
			address_list[count] = pos;
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
		file.open("5.txt", ios::out | ios::in);
		address = address_list[pos];
		file.seekp(address, ios::beg);
		file.put('*');
		file.close();
		cout << "\nRecord Deleted: ";

		for (i = pos; i < count; i++)
		{
			record_number_list[i] = record_number_list[i + 1];
			address_list[i] = address_list[i + 1];
		}
		count--;
	}
	else
		cout << "Record not found\n";
}