// <!-- HEADERS --!>
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;

// <!-- FUNCTION DECLARATIONS --!>
string dateTime(void);
void insertRecord(const string);
void showRecords(void);
void inputLoop(bool&, string&, const string);
void displayChoices(void);
void exitProgram(void);
int stringToInt(const string);

// <!-- BOOK CLASS --!>
class book {
	private:
		string datetimeAdded;
	public:
		string title;
		string author;
		string datePublished;
		string address;
		book (void) {}
		book (const string t, const string a, const string d, const string ad)
		: title(t), author(a), datePublished(d), address(ad), datetimeAdded(dateTime()) {
		}
		void displayTitle(void) {
			cout << title << endl;
			return;
		}
		void displayAuthor(void) {
			cout << author << endl;
			return;
		}
		void displayDatePublished(void) {
			cout << datePublished << endl;
			return;
		}
		void displayProperties(void) {
			cout << "\t\t\t     Added Datetime: " + datetimeAdded << endl;
			cout << "\t\t\t     Title: " << title << endl;
			cout << "\t\t\t     Author: " << author << endl;
			cout << "\t\t\t     Date Published: " << datePublished << endl;
			cout << "\t\t\t     Address: " << address << endl;
			return;
		}
};

// <!-- FUNCTION DECLARATIONS --!>
void arrangeAlpha(stack<book>& Books);
void bubbleSort(vector<book>& Books);
void pushBook(stack<book>&, book);
void addBook(stack<book>&);
void showBooks(stack<book>&);
void updateBook(stack<book>&);
void selectUpdate(stack<book>&);
void deleteBook(stack<book>&);
void selectDelete(stack<book>&);
int mainMenu(stack<book>&);

// <!-- MAIN FUNCTION --!>
int main (void) {
	// Initial objects for testing purposes (You can add more)
	stack<book> Books;
	mainMenu(Books);
	return 0;
}

void bubbleSort(vector<book>& Books) {
	bool swapped = true;
	int j = 0;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < Books.size() - j; i++) {
			if (Books[i].title > Books[i + 1].title) {
				book Book = Books[i];
				Books[i] = Books[i + 1];
				Books[i + 1] = Book;
				swapped = true;
			}
		}
	}
   return;
}

void arrangeAlpha(stack<book>& Books) {
	vector<book> BooksTempConVec;
	if (Books.empty()) {
		cout << endl << "\t\t\Empty!" << endl;
        return;
	}
	while (!Books.empty()) {
		BooksTempConVec.push_back(Books.top());
		Books.pop();
	}
	bubbleSort(BooksTempConVec);
	for (int i = 0; i < BooksTempConVec.size(); i++) {
		Books.push(BooksTempConVec[i]);
	}
 	return;
}

// <!-- GETS THE CURRENT DATE & TIME --!>
string dateTime(void) {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%m-%d-%y %H:%M:%S", timeinfo);
	string str(buffer);
	return str;
}

// <!-- RECORDS EVENT IN TEXT FILE (IT ACTS AS A DATABASE) --!>
void insertRecord(const string Str) {
    ofstream file ("history.txt", ios_base::app | ios_base::out);
    file << Str << "\n";
    return;
}

// <!-- DISPLAY RECORDS FROM THE TEXT FILE --!>
void showRecords (void) {
    system("cls");
    int index = 0;
    fstream file ("history.txt");
    string Str;
    cout << endl << "\tRecords" << endl;
    while (getline(file, Str)) {
        index++;
        cout << endl << "\t" << index << ".) " << Str << endl;
    }
    return;
}

// <!-- INPUT VALUE IN A LOOP --!>
void inputLoop(bool& isRunning, string& var, const string idName) {
	while (isRunning) {
		system("color a");
        cout << endl << "\t\t\tInput " + idName + ": ";
        getline(cin, var);
        if (var.size() == 0) {
            cout << endl << "\t\t\tInsert " + idName + "!"
                 << endl << endl << "\t\t\t";
            system("color 47");
            system("PAUSE");
            system("CLS");
            displayChoices();
            continue;
        } else if (!(var.compare("0"))) {
            cout << endl << "\t\t\tCanceled!" << endl;
            isRunning = false;
            return;
        } else {
        	break;
		}
	}
	return;
}

// <!-- PUSH BOOK OBJECT IN THE STACK --!>
void pushBook(stack<book>& Books, book Book) {
	Books.push(Book);
	return;
}

// <!-- MAIN FUNCTION --!>
void addBook(stack<book>& Books) {
	string title;
	string author;
	string datePublished;
	string address;
	bool isRunning = true;
	cout << endl << "\t\t\tInput [0] to Cancel" << endl;
	inputLoop(isRunning, title, "title");
	inputLoop(isRunning, author, "author");
	inputLoop(isRunning, datePublished, "date published");
	inputLoop(isRunning, address, "address");
	if (isRunning) {
		book Book(title, author, datePublished, address);
		pushBook(Books, Book);
		insertRecord(title + " was added at " + dateTime());
	}
	return;
}

// <!-- DISPLAY BOOKS --!>
void showBooks(stack<book>& Books) {
	arrangeAlpha(Books);
	stack<book> BooksTempCon;
	int index = 1;
	if (Books.empty()) {
		cout << endl << "\t\t\tEmpty!" << endl;
        return;
	}
	while (!Books.empty()) {
		BooksTempCon.push(Books.top());
		Books.pop();
	}
	cout << endl;
	while (!BooksTempCon.empty()) {
		cout << "\t\t\t" << index << ".)" << endl;
		Books.push(BooksTempCon.top());
		BooksTempCon.top().displayProperties();
		BooksTempCon.pop();
		index++;
	}
	return;
}

// <!-- UPDATE BOOK ADDRESS/LOCATION, SINCE YOU CANNOT UPDATE ITS CONTENT --!>
void updateBook(string number, stack<book>& Books) {
	string newStr;
	int index = 1;
	vector<book> BooksTempConVector;
	stack<book> BooksTempConStack;
	while (!Books.empty()) {
		BooksTempConStack.push(Books.top());
		Books.pop();
	}
	while (!BooksTempConStack.empty()) {
		if (stringToInt(number) == index) {
			cout << endl << "\t\t\tCurrent address: " << BooksTempConStack.top().address << endl;
			cout << "\t\t\tSet new address: ";
			getline(cin, newStr);
			insertRecord(BooksTempConStack.top().title + "'s address was changed from " + BooksTempConStack.top().address + " to " + newStr + " at " + dateTime());
			BooksTempConStack.top().address = newStr;
		}
		BooksTempConVector.push_back(BooksTempConStack.top());
		BooksTempConStack.pop();
		index++;
	}
	for (int j = 0; j < BooksTempConVector.size(); j++) {
		Books.push(BooksTempConVector[j]);
	}
	return;
}

// <!-- SELECT BOOK NUMBER IN UPDATE BOOK FUNCTION --!>
void selectUpdate(stack<book>& Books) {
	string select, number;
	bool isRunning = true;
	while (isRunning) {
		system("color a");
        system("CLS");
        cout << endl << "\t\t\t------- UPDATE BOOK -------" << endl;
        showBooks(Books);
        cout << endl << "\t\t\t[1] UPDATE" <<
        endl << "\t\t\t[2] CANCEL" << endl <<
        endl << "\t\t\tSELECT [1-2]: ";
        getline(cin, select);
        if (select == "1") {
        	if (!Books.empty()) {
        		cout << endl << "\t\t\tSelect book number: ";
			} else {
				cout << endl << "\t\t\tStack is empty!" << endl
                     << endl << "\t\t\t";
                system("PAUSE");
                continue;
			}
			getline(cin, number);
			updateBook(number, Books);
			cout << endl << "\t\t\t";
            system("PAUSE");
		} else if (select == "2") {
			return;
		} else {
			system("color 47");
            cout << endl << "\t\t\tError!" << endl
                 << endl << "\t\t\t";
            system("PAUSE");
		}
	}
	return;
}

void deleteBook(string number, stack<book>& Books) {
	vector<book> BooksTempConVector;
	stack<book> BooksTempConStack;
	int index = 1;
	while(!Books.empty()) {
		BooksTempConStack.push(Books.top());
		Books.pop();
	}
	while(!BooksTempConStack.empty()) {
		BooksTempConVector.push_back(BooksTempConStack.top());
		BooksTempConStack.pop();
	}
	for (vector<book>::iterator i = BooksTempConVector.begin(); i < BooksTempConVector.end(); i++) {
		if (stringToInt(number) == index) {
			cout << endl << "\t\t\t" << (*i).title << " has been deleted." << endl;
            insertRecord((*i).title + " has been deleted.");
            BooksTempConVector.erase(i);
		}
		index++;
	}
	for (int j = 0; j < BooksTempConVector.size(); j++) {
		Books.push(BooksTempConVector[j]);
	}
	return;
}

void selectDelete(stack<book>& Books) {
	string select, number;
	bool isRunning = true;
	while (isRunning) {
		system("color a");
        system("CLS");
        cout << endl << "\t\t\t------- DELETE BOOK -------" << endl;
        showBooks(Books);
        cout << endl << "\t\t\t[1] DELETE" <<
        endl << "\t\t\t[2] CANCEL" << endl <<
        endl << "\t\t\tSELECT [1-2]: ";
        getline(cin, select);
        if (select == "1"){
            if (!Books.empty()){
                cout << endl << "\t\t\tSelect book number: ";
            } else {
                cout << endl << "\t\t\tStack is empty!" << endl
                     << endl << "\t\t\t";
                system("PAUSE");
                continue;
            }
            getline(cin, number);
            deleteBook(number, Books);
            cout << endl << "\t\t\t";
            system("PAUSE");
        } else if (select == "2") {
            return;
        } else {
            system("color 47");
            cout << endl << "\t\t\tError!" << endl
                 << endl << "\t\t\t";
            system("PAUSE");
        }
	}
	return;
}

// <!-- DISPLAY THE PROVIDED OPTIONS --!>
void displayChoices (void){
    cout << endl
         << "\t\t\t LIBRARY MANAGEMENT SYSTEM" << endl << endl
         << "\t\t\t=======| OPTIONS |=========" << endl << endl
         << "\t\t\t[1] ADD BOOK" << endl
         << "\t\t\t[2] SHOW BOOKS" << endl
         << "\t\t\t[3] UPDATE BOOK" << endl
         << "\t\t\t[4] DELETE BOOK" << endl
         << "\t\t\t[5] SHOW RECORDS" << endl
         << "\t\t\t[6] EXIT" << endl;
    return;
}

// <!-- CLOSE THE ENTIRE PROGRAM --!>
void exitProgram(bool& isRunning) {
	isRunning = false;
	return;
}

// <!-- CONVERT STRING TO INTEGER NUMBER --!>
int stringToInt(string number) {
	int num = atoi(number.c_str());
	return num;
}

// <!-- THE MAIN MENU OF THE PROGRAM --!>
int mainMenu (stack<book>& Books) {
	string user_option;
	bool isRunning = true;
	do{
        system("color a");
        displayChoices();
        cout << endl << "\t\t\tSELECT [1-6]: ";
        getline(cin, user_option);
		if(user_option == "1") {
		    addBook(Books);
		    cout << endl << "\t\t\t";
		} else if(user_option == "2") {
            showBooks(Books);
            cout << endl << "\t\t\t";
		} else if(user_option == "3") {
            selectUpdate(Books);
		    cout << endl << "\t\t\t";
		} else if(user_option == "4") {
			selectDelete(Books);
            cout << endl << "\t\t\t";
		} else if (user_option == "5") {
            showRecords();
            cout << endl << "\t\t\t";
        } else if (user_option == "6") {
            exitProgram(isRunning);
            cout << endl << "\t\t\t";
            break;
        } else {
		    system("color 47");
		    cout << endl << "\t\t\tERROR!" << endl
                 << endl << "\t\t\t";
		}
		system("PAUSE");
		system("CLS");
	}
	while (isRunning);
	return EXIT_SUCCESS;
}
