#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define endl "\n"

class Book {                                                                 //Book class
    public:
        Book* next;
        Book(string title, string author, int year, double price);          //Constructor
        void printBookDetails();                                            //Printing Book Details
        string getTitle(){ return title;}                                   //getting title
        string getAuthor(){ return author;}                                 //getting author
        int getYear(){ return year;}                                        //getting year
        double getPrice(){ return price;}                                   //getting price
    private:
        string title;
        string author;
        int year;
        double price;
};

Book::Book(string title, string author, int year, double price){
    this->title = title;
    this->author = author;
    this->year = year;
    this->price = price;
    this->next = NULL;
}

void Book::printBookDetails(){
    cout<<this->title<<',';
    cout<<this->author<<',';
    cout<<this->year<<',';
    cout<<this->price<<endl;
}

//Duplicate Books checking function

bool isDuplicate(Book* b1, Book* b2){                                   
    int flag=0;
    if(b1->getTitle() != b2->getTitle()) flag = 1;
    if(b1->getAuthor() != b2->getAuthor()) flag = 1;
    if(b1->getYear() != b2->getYear()) flag = 1;
    if(b1->getPrice() != b2->getPrice()) flag = 1;

    if(flag == 0) return true;   //Duplicate
    else return false;           //Not a Duplicate
}

class Bookshelf {                                                                       //Bookshelf - base class
    public:
        virtual void addBook(string title, string author, int year, double price)=0;    //Adding book
        virtual void removeBook()=0;                                                    //Removing book
        bool checkEmpty();                                                              //Checking if shelf is empty
        virtual void list()=0;                                                          //Listing the books
        virtual void findCheap()=0;                                                     //Finding the cheap one step by step
        virtual void reverseUnique()=0;                                                 //Reversing only the unique elements
        Book* getHead(){ return head;}
    protected: 
        Book* head = NULL;
        Book* tail = NULL;
};

bool Bookshelf::checkEmpty(){
    
    if(head == NULL) return true;
    else return false;

}

class VerticalBookshelf : public Bookshelf {                                            //Vertical Bookshelf - derived class
    public:
        virtual void addBook(string title, string author, int year, double price);
        virtual void removeBook();
        virtual void list();
        virtual void findCheap();
        virtual void reverseUnique();
};

void VerticalBookshelf::addBook(string title, string author, int year, double price){

    Book* newptr = new Book(title, author, year, price);

    if(checkEmpty()){
        head = newptr;
    }else{
        newptr->next = head;
        head = newptr;
    }
    
    return;
}

void VerticalBookshelf::removeBook(){

    if(checkEmpty()){
        cout<<'e'<<endl;
    }else{
        Book* removed = head;
        head = head->next;
        free(removed);
    }

    return;
}

void VerticalBookshelf::list(){

    if(checkEmpty()){
        cout<<'e'<<endl;
        return;
    }

    Book* iterator = head;

    while(iterator != NULL){
        iterator->printBookDetails();
        iterator = iterator->next;
    }

    return;
}

void VerticalBookshelf::findCheap(){

    if(checkEmpty()){
        cout<<'e'<<endl;
        return;
    }

    Book* iterator = head;
    double min = iterator->getPrice();

    while(1){
        if(iterator->getPrice() <= min){
            cout<<-1;
            min = iterator->getPrice();
        }else{
            cout<<min;
        }
        iterator = iterator->next;
        if(iterator != NULL) cout<<',';
        else{
            cout<<endl;
            break;
        }
    }

    return;
}

class HorizontalBookshelf : public Bookshelf {                                              //Horizontal Bookshelf - derived class
    public:
        virtual void addBook(string title, string author, int year, double price);
        virtual void removeBook();
        virtual void list();
        virtual void findCheap();
        virtual void reverseUnique();
};

void HorizontalBookshelf::addBook(string title, string author, int year, double price){

    Book* newptr = new Book(title, author, year, price);

    if(checkEmpty()){
        head = newptr;
        tail = newptr;
    }else{
        tail->next = newptr;
        tail = newptr;
    }
    
    return;
}

void HorizontalBookshelf::removeBook(){

    if(checkEmpty()){
        cout<<'e'<<endl;
    }else{
        Book* removed = head;
        head = head->next;
        if(head == NULL) tail = NULL;
        free(removed);
    }

    return;
}

void HorizontalBookshelf::list(){

    if(checkEmpty()){
        cout<<'e'<<endl;
        return;
    }

    Book* iterator = head;

    while(iterator != NULL){
        iterator->printBookDetails();
        iterator = iterator->next;
    }

    return;
}

void HorizontalBookshelf::findCheap(){

    if(checkEmpty()){
        cout<<'e'<<endl;
        return;
    }

    Book* iterator = head;
    double min = iterator->getPrice();

    while(1){
        if(iterator->getPrice() <= min){
            cout<<-1;
            min = iterator->getPrice();
        }else{
            cout<<min;
        }
        iterator = iterator->next;
        if(iterator != NULL) cout<<',';
        else{
            cout<<endl;
            break;
        }
    }

    return;
}

void VerticalBookshelf::reverseUnique(){

    HorizontalBookshelf temp = HorizontalBookshelf();

    while(!checkEmpty()){
        Book* shift = head;
        temp.addBook(shift->getTitle(), shift->getAuthor(), shift->getYear(), shift->getPrice());
        this->removeBook();
    }

    while(!temp.checkEmpty()){
        Book* shift = temp.getHead();
        Book* check = head;
        int flag = 0;
        while(check != NULL){
            if(isDuplicate(shift, check)){
                flag = 1;
                break;
            }
            check = check->next;
        }
        if(flag == 0){
            this->addBook(shift->getTitle(), shift->getAuthor(), shift->getYear(), shift->getPrice());
        }

        temp.removeBook();
    }

    return;
}

void HorizontalBookshelf::reverseUnique(){

    VerticalBookshelf temp = VerticalBookshelf();

    while(!checkEmpty()){
        Book* shift = head;
        temp.addBook(shift->getTitle(), shift->getAuthor(), shift->getYear(), shift->getPrice());
        this->removeBook();
    }

    while(!temp.checkEmpty()){
        Book* shift = temp.getHead();
        Book* check = head;
        int flag = 0;
        while(check != NULL){
            if(isDuplicate(shift, check)){
                flag = 1;
                break;
            }
            check = check->next;
        }
        if(flag == 0){
            this->addBook(shift->getTitle(), shift->getAuthor(), shift->getYear(), shift->getPrice());
        }

        temp.removeBook();
    }

    return;
}

int main() {
    int Q;
    cin>>Q;

    VerticalBookshelf v = VerticalBookshelf();
    HorizontalBookshelf h = HorizontalBookshelf();

    while(Q--){
        string opcode;
        cin>>opcode;

        if(opcode == "ADD"){
            char x;
            cin>>x;
            string title, author;
            int year;
            double price;
            cin>>title>>author>>year>>price;

            if(x == 'v'){
                v.addBook(title, author, year, price);
            }else if(x == 'h'){
                h.addBook(title, author, year, price);
            }
        }else if(opcode == "REMOVE"){
            int n;
            char x;
            cin>>n>>x;

            if(x == 'v'){
                while(n--){
                    v.removeBook();
                }
            }else if(x == 'h'){
                while(n--){
                    h.removeBook();
                }
            }
        }else if(opcode == "LIST"){
            char x;
            cin>>x;

            if(x == 'v') v.list();
            else if(x == 'h') h.list();

        }else if(opcode == "FINDC"){
            char x;
            cin>>x;

            if(x == 'v') v.findCheap();
            else if(x == 'h') h.findCheap();
        }else if(opcode == "REVUNI"){
            char x;
            cin>>x;

            if(x == 'v') v.reverseUnique();
            else if(x == 'h') h.reverseUnique();
        }
    } 
    return 0;
}
