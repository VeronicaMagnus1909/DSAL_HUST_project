#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // system   
#include <iomanip>  // setw
#include <algorithm>    // sort
#include <sstream>  
#include <fstream>

using namespace std;

class Book{
    public:
        string name;
        string author;
        string publisher;
        string date; // format: DD-MM-YYYY
        int price; //$
        string description;
        Book* next;

        Book() {
            next = NULL;
        }
};

Book* head = NULL;

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\n Press Enter to continue";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


Book* createBook(){
    Book* newBook = new Book();

    cout << "Enter book name: ";
    getline(cin >> ws, newBook->name);

    cout << "Enter author: ";
    getline(cin, newBook->author);

    cout << "Enter publisher: ";
    getline(cin, newBook->publisher);


    cout << "Enter date (DD-MM-YYYY):";
    getline(cin, newBook->date);


    cout << "Enter the price: ";
    cin >> newBook-> price;

    cout << "Enter description: ";
    getline(cin, newBook->description);

    return newBook;

}

void addBook() 
{
    Book* newBook = createBook();
    if(!newBook) return;

    if(head == NULL) {
        head = newBook;
    }
    else
    {
        Book *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    cout << "\nBook added sucessfully!\n";
    pause();
}

void addBook_auto()
{
    vector<string> names = {
    "Calculus I", "Calculus II", "Calculus III", "Linear Algebra", "Probability",
    "C/C++ Programming", "Computer Architecture", "Signal Processing", "Digital Electronics", "DSA"
};

vector<string> author = {
    "James Stewart",        // Calculus I
    "James Stewart",        // Calculus II
    "James Stewart",        // Calculus III
    "Gilbert Strang",       // Linear Algebra
    "Sheldon Ross",         // Probability
    "Bjarne Stroustrup",    // C/C++ Programming
    "David A. Patterson",   // Computer Architecture
    "Alan V. Oppenheim",    // Signal Processing
    "Thomas Floyd",         // Digital Electronics
    "Robert Lafore"         // Data Structures and Algorithms
};

vector<string> publisher = {
    "Cengage Learning",     // Calculus I
    "Cengage Learning",     // Calculus II
    "Cengage Learning",     // Calculus III
    "Wellesley-Cambridge",  // Linear Algebra
    "Academic Press",       // Probability
    "Addison-Wesley",       // C/C++ Programming
    "Morgan Kaufmann",      // Computer Architecture
    "Pearson",              // Signal Processing
    "Pearson",              // Digital Electronics
    "Sams Publishing"       // Data Structures and Algorithms
};



   vector<string> dates = {
    "01-01-2023", "01-01-2023", "01-01-2023", "20-04-2023", "30-05-2023",
    "15-06-2023", "22-07-2023", "10-08-2023", "18-09-2023", "25-10-2023"
};

vector<string> descs = {
    "Basic calculus ",               // Calculus I
    "Intermediate calculus ",     // Calculus II
    "Advanced multivariable calculus",            // Calculus III
    "Matrix operations",        // Linear Algebra
    "Fundamentals theory",         // Probability
    "Core concepts C++",                 // C/C++ Programming
    "Computer architecture",       // Computer Architecture
    "Digital signal ",      // Signal Processing
    "Basics of logic gates",         // Digital Electronics
    "Array, Linked list, graph,..."       // Data Structures and Algorithms
};
    vector<int> prices = {100, 150, 149, 200, 50, 39, 79, 89,90, 149};

    for (int i = 0; i < 10; i++)
    {
        Book* newBook = new Book();
        newBook->name = names[i];
        newBook->author = author[i];
        newBook->date = dates[i];
        newBook->publisher = publisher[i];
        newBook->description = descs[i];
        newBook->price = prices[i];
    if (!head) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newBook;
        }   

    }

    cout << "\n10 sample books added successfully!\n";

    // In tiêu đề
    cout << left
         << setw(30) << "Book name"
         << setw(30) << "Publisher"
         << setw(30) << "Author"
         << setw(20) << "Date"
         << setw(10) << "Price"
         << "    " << left << setw(40) << "Description"
         << "\n";

    // Gạch ngang phân cách
    cout << string(160, '-') << "\n";

    // In dữ liệu từng sách
    Book* temp = head;

    while (temp != NULL) {
        cout << left
             << setw(30) << temp->name
             << setw(30) << temp->publisher
             << setw(30) << temp->author
             << setw(20) << temp->date
             << setw(10) << temp->price
             << "    " << left << setw(50) << temp->description
             << "\n";

        temp = temp->next;
    }

    pause(); // Hàm tạm dừng chương trình
}

void displayBooks()
{
    if( head == NULL)
    {
        cout << "No Book in store";
        pause();
        return;
    }

    // In tiêu đề
    cout << left
         << setw(30) << "Book name"
         << setw(30) << "Publisher"
         << setw(30) << "Author"
         << setw(20) << "Date"
         << setw(10) << "Price"
         << "    " << left << setw(40) << "Description"
         << "\n";

    // Gạch ngang phân cách
    cout << string(160, '-') << "\n";

    // In dữ liệu từng sách
    Book* temp = head;

    while (temp != NULL) {
        cout << left
             << setw(30) << temp->name
             << setw(30) << temp->publisher
             << setw(30) << temp->author
             << setw(20) << temp->date
             << setw(10) << temp->price
             << "    " << left << setw(50) << temp->description
             << "\n";

        temp = temp->next;
    }

    pause(); // Hàm tạm dừng chương trình

}

Book* findBook(const string& name) {
    Book* temp = head;
    while (temp) {
        if (temp->name == name)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void searchBook()
{
    string name;
    cout << "What book you want to find: ";
    getline(cin>>ws, name);

    Book* book = findBook(name);
    if(book != NULL)
    {
        cout << "\nBook found:\n";
        cout << "Name: " << book->name << "\nAuthor: " << book->author << "\nPublisher: " << book ->publisher << "\nDescription: " << book-> description << "\nprice:" << book->price <<"\nDate" <<book->date;
    }
}

//////////////////////
void deleteBook() {
    string name;
    cout << "Enter Book name to delete: ";
    getline(cin >> ws, name);

    Book* temp = head;
    Book* prev = nullptr;

    while (temp && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Book not found.\n";
    } else {
        if (!prev)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Book deleted successfully.\n";
    }
    pause();
}

void editBook() {
    string name;
    cout << "Enter book name to edit: ";
    getline(cin >> ws, name);

    Book* book = findBook(name);
    if (!book) {
        cout << "book not found.\n";
        pause();
        return;
    }

    cout << "Editing Book: " << name << "\n";

    cout << "Enter new author: ";
    getline(cin, book->author);
    cout << "Enter new publisher: ";
    getline(cin, book->publisher);

    cout << "Enter new date (DD-MM-YYYY): ";
    getline(cin, book->date);

    cout << "Enter new description: ";
    getline(cin, book->description);

    cout << "book updated successfully.\n";
    pause();
}

void detectDuplicates() {
    bool found = false;
    for (Book* ptr1 = head; ptr1 != nullptr; ptr1 = ptr1->next) {
        for (Book* ptr2 = ptr1->next; ptr2 != nullptr; ptr2 = ptr2->next) {
            if (ptr1->name == ptr2->name && ptr1->date == ptr2->date) {
                cout << "Duplicate found: " << ptr1->name << " on " << ptr1->date << "\n";
                found = true;
            }
        }
    }

    if (!found)
        cout << "No duplicates found.\n";

    pause();
}

int countNodes() {
    int count = 0;
    Book* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

vector<Book*> fillArray() {
    vector<Book*> arr;
    Book* temp = head;
    while (temp) {
        arr.push_back(temp);
        temp = temp->next;
    }
    return arr;
}

bool compareByName(Book* a, Book* b) {
    return a->name < b->name;
}



bool compareByDate(Book* a, Book* b) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(a->date.c_str(), "%2d-%2d-%4d", &d1, &m1, &y1);
    sscanf(b->date.c_str(), "%2d-%2d-%4d", &d2, &m2, &y2);

    if (y1 != y2) return y1 < y2;
    if (m1 != m2) return m1 < m2;
    return d1 < d2;
}

void printSortedArray(const vector<Book*>& arr) {
    for (const auto& img : arr) {
        cout << "Name: " << img->name << ", Date: " << img->date << "\n";
    }
    pause();
}

void sortByName() {
    auto arr = fillArray();
    sort(arr.begin(), arr.end(), compareByName);
    printSortedArray(arr);
}


void sortByDate() {
    auto arr = fillArray();
    sort(arr.begin(), arr.end(), compareByDate);
    printSortedArray(arr);
}

void exportToFile() {
    ofstream fout("books.txt");
    if (!fout) {
        cout << "Cannot open file to write.\n";
        pause();
        return;
    }

    fout << left
         << setw(30) << "Book name"
         << setw(30) << "Publisher"
         << setw(30) << "Author"
         << setw(20) << "Date"
         << setw(10) << "Price"
         << "    " << left << setw(40) << "Description"
         << "\n";
    fout << string(160, '-') << "\n";

    Book* temp = head;
    while (temp != NULL) {
        fout << left
             << setw(30) << temp->name
             << setw(30) << temp->publisher
             << setw(30) << temp->author
             << setw(20) << temp->date
             << setw(10) << temp->price
             << "    " << left << setw(50) << temp->description
             << "\n";
        temp = temp->next;
    }
    fout.close();
    cout << "Exported to books.txt successfully!\n";
    pause();
}

//////
// Hàm tính trọng số giữa hai sách (ví dụ: số ký tự chung trong tên)
int calculate_weight(Book* a, Book* b) {
    int count = 0;
    for (char c1 : a->name) {
        for (char c2 : b->name) {
            if (tolower(c1) == tolower(c2) && c1 != ' ') {
                count++;
                break;
            }
        }
    }
    return count;
}

// Hàm tạo và in ma trận quan hệ giữa các sách
void create_relation_graph() {
    vector<Book*> arr = fillArray();
    int n = arr.size();
    if (n == 0) {
        cout << "No books to create relation graph.\n";
        pause();
        return;
    }

    vector<vector<int>> graph(n, vector<int>(n, 0));

    // Tính trọng số giữa các sách
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                graph[i][j] = calculate_weight(arr[i], arr[j]);
            }
        }
    }

    cout << "\nRelation graph (weight matrix) between books:\n\n";
    cout << setw(14) << "";
    for (int i = 0; i < n; i++) {
        cout << setw(14) << arr[i]->name.substr(0, 12);
    }
    cout << "\n" << setw(14) << "";
    for (int i = 0; i < n; i++) cout << string(12, '-') << " ";
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << setw(14) << arr[i]->name.substr(0, 12);
        for (int j = 0; j < n; j++) {
            cout << setw(14) << graph[i][j];
        }
        cout << "\n";
    }
    pause();
}




// You can then create a menu to test all functions here if you want.
int main() {
    int choice;
    do {
        clearScreen();
        cout << "===========Book Manager Project =====\n";
        cout << "==============Le Van Minh ===========\n";
        cout << "================20214001 ============\n";
        cout << "===========C/C++ programming=========\n";
        cout << "\n============Base Features===========\n";
        cout << "1. Add Book\n";
        cout << "2. Add Sample Book\n";
        cout << "3. Display Books\n";
        cout << "4. Search Book\n";
        cout << "=============Advanced Features========\n";
        cout << "5. Delete Book\n";
        cout << "6. Edit Book\n";
        cout << "7. Detect Duplicates\n";
        cout << "8. Sort by Name\n";
        cout << "9. Sort by Date\n";
        cout << "10. Relation Graph\n";
        cout << "11. Export to file txt\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addBook(); break;
            case 2: addBook_auto(); break;
            case 3: displayBooks(); break;
            case 4: searchBook(); break;
            case 5: deleteBook(); break;
            case 6: editBook(); break;
            case 7: detectDuplicates(); break;
            case 8: sortByName(); break;
            case 9: sortByDate(); break;
            case 10: create_relation_graph();break;
            case 11: exportToFile();break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n"; pause(); break;
        }

    } while (choice != 0);

    return 0;
}


