# law-firm-record-management-system ⚖️
This is a repository which contains my File Structures Mini Project for the File Structures Laboratory With Mini Project in C++.

It has minimal features and implements the following simple methods: 

* ```read_data()``` - reads the lawyer's data to be stored from the user.
* ```pack()``` - packs the lawyer's data into a string to be stored in the text file.
* ```write_to_file()``` - writes the packed data into a text file.
* ```create_index()``` - opens a text file which may contain previously entered lawyer details. Creates an index to access them in memory. If the file doesn't contain any lines, it is closed.
* ```remove()``` - removes the record from the index and subsequently the file.
* ```search()``` - searches the index for the record and retrieves it using the index.
* ```search_index()``` - basic implementation of binary search.
* ```extract_lawyer()``` - extracts the lawyer name from the packed record 
* ```sort_index()``` - sorts the index based on the lawyer name.
* ```disp()``` - a small method to display all the lawyers and the addresses in the record. Not to be implemented in an professional version of app.
* ```unpack()``` - method to extract all the fields from a record separated using a delimiter.
* ```modify()``` - method to change a particular field in a record entry.
## Requirements
To add a little bit of flair to it, I made use of ```figlet``` to have a CLI banner. 😀 <br>
Install it using 
    ```$ sudo apt install figlet``` 
