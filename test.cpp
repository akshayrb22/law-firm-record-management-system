#include <ctime>
#include <string.h>
#include <iostream>
#include <typeinfo>
using namespace std;
int main(int argc, char const *argv[])
{
	// char timestamp_arr[1s
	// time_t now = time(0);
	// cout << now << endl;
	// cout << typeid(now).name() << endl;
	// cout << strcmp("Ashik", "");

	// tm * current_tm = localtime(&current_time);
	// strftime(timestamp_arr, 50, "%D", current_tm);
	// cout << current_tm->tm_year << " / " << current_tm->tm_mon << " / " << current_tm->tm_wday;
	// time_t now = time(0);   // current system date/time
	// char *dt = ctime(&now); // convert in string form
	// string timestamp = to_string(now);
	// cout << "Local date and time is:-\n\t\t" << dt << "\n";
	string my_string;
	getline(cin, my_string);
	cout << my_string;
}