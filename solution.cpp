#include <bits/stdc++.h>
using namespace std;

struct book{
    int id;
    string title;
    string author;
    string edition;
    string publisher;
    string category;
    int copies_available;
    int lended;
};

struct borrower{
    string id;
    int borrowed_book_id;
    time_t issue_date;
    time_t return_date;
};

void save(vector<struct book> &books, string what){
    if(what == "book"){
        ofstream file("book_database.data");
        for(auto x : books){
            file << x.id << "\n";
            file << x.title << "\n";
            file << x.author << "\n";
            file << x.edition << "\n";
            file << x.publisher << "\n";
            file << x.category << "\n";
            file << x.copies_available << "\n";
            file << x.lended << "\n";
        }
        file.close();
    }
    if(what == "borrower"){
        ofstream file("borrower_database.data");
        /*for(){

        }*/
    }
}

void read(vector<struct book> &old_books, string what){
    if(what == "book"){
        ifstream file("book_database.data");
        vector<struct book> books;
        if(file){
            while(!file.eof()){
                struct book tmp;
                file >> tmp.id;
                if(file.eof()) break;
                file.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(file, tmp.title);
                getline(file, tmp.author);
                getline(file, tmp.edition);
                getline(file, tmp.publisher);
                getline(file, tmp.category);
                file >> tmp.copies_available;
                file.ignore(numeric_limits<streamsize>::max(), '\n');
                file >> tmp.lended;
                books.push_back(tmp);
            }
        }
        file.close();
        old_books = books;
    }
    if(what == "borrower"){
        
    }
}

string to_lowercase(string s){
    string s2;
    for(char c : s){
        char c2 = tolower(c);
        s2.push_back(c2);
    }
    return s2;
}

bool check(string s1, string s2){
    for(int i = 0; i < s2.length(); i++){
        if(s1.length() < i) return false;
        if(s1[i] != s2[i]) return false;
    }
    return true;
}

vector<struct book> search_name(vector<struct book> books, string name){
    vector<struct book> result;
    for(auto b : books){
        string test = to_lowercase(b.title);
        if(check(test, name)) result.push_back(b);
    }
    return result;
}

void print_line(){
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void display(vector<struct book> &books){
    print_line();
    cout << setw(5) << "ID" << setw(50) << "Title" << setw(35) << "Author" << setw(20) << "Edition" << setw(35) << "Publisher" << setw(35) << "Category" << endl;
    print_line();
    for(auto tmp : books){
        cout << setw(5) << tmp.id << setw(50) << tmp.title << setw(35) << tmp.author << setw(20) << tmp.edition << setw(35) << tmp.publisher << setw(35) << tmp.category << endl;
    }
    print_line();
}

int main(){
    vector<struct book> books;
    vector<struct borrower> borrowers;
    while(true){
        read(books, "book");
        cout << "\n--------------------Computerized Seminar Room Book Management System--------------------\n\n";
        cout << "1) Add a book\n";
        cout << "2) Display all books\n";
        cout << "3) Search for a book\n";
        cout << "4) Update a book's information\n";
        cout << "5) Issue a book\n";
        cout << "6) Return a book\n";
        cout << "7) Show report\n";
        cout << "9) Exit\n";
        int input;
        cout << "Enter a value: ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(input == 9) break;
        if(input == 1){
            struct book tmp;
            cout << "Enter book title: ";
            getline(cin, tmp.title);
            cout << "Enter author's name: ";
            getline(cin, tmp.author);
            cout << "Enter edition no.: ";
            getline(cin , tmp.edition);
            cout << "Enter publisher's name: ";
            getline(cin, tmp.publisher);
            cout << "Enter category: ";
            getline(cin, tmp.category);
            cout << "Enter number of copies available: ";
            cin >> tmp.copies_available;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter number of copies lended: ";
            cin >> tmp.lended;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            tmp.id = books.size()+1;
            books.push_back(tmp);
            save(books, "book");
        }
        if(input == 2){
            display(books);
        }
        if(input == 3){
            cout << "Enter the name of the book you want to search.\n";
            string name;
            getline(cin, name);
            vector<struct book> found = search_name(books, name);
            cout << "\nThese are the books that match your query,\n";
            display(found);
        }
        if(input == 4){
            ask_id:
                cout << "Enter the ID of the book you want to update: ";
                int tmp_id;
                cin >> tmp_id;
                if(tmp_id > books.size()){
                    cout << "Invalid ID!\n";
                    goto ask_id;
                }
            bool keep_running = true;
            while(keep_running){
                auto *tmp = &books[tmp_id-1];
                cout << "1) Title: " << tmp->title << endl;
                cout << "2) Author: " << tmp->author << endl;
                cout << "3) Edition: " << tmp->edition << endl;
                cout << "4) Publisher: " << tmp->publisher << endl;
                cout << "5) Category: " << tmp->category << endl;
                cout << "6) Available copies: " << tmp->copies_available << endl;
                cout << "Which data would you like to update? (Enter 0 to quit) ";
                char option;
                cin >> option;
                option -= '0';
                switch(option){
                    case 0:
                        keep_running = false;
                        break;
                    case 1:
                        cout << "Title: ";
                        cin >> tmp->title;
                        break;
                    case 2:
                        cout << "Author: ";
                        cin >> tmp->author;
                        break;
                    case 3:
                        cout << "Edition: ";
                        cin >> tmp->edition;
                        break;
                    case 4:
                        cout << "Publisher: ";
                        cin >> tmp->publisher;
                        break;
                    case 5:
                        cout << "Category: ";
                        cin >> tmp->category;
                        break;
                    case 6:
                        cout << "Available copies: ";
                        cin >> tmp->copies_available;
                        break;
                    default:
                        print_line();
                        cout << "Please enter a value between 0 and 6!\n";
                }
                save(books, "book");
            }
            
        }
    }
}
