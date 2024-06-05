#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

 class Book
{

private:
std::string title;
  
std::string author;
  
std::string isbn;
  
bool isAvailable;

 
public:
	
Book (std::string t, std::string a, std::string i) 
:
  title (t), author (a), isbn (i),
  isAvailable (true)
  {
  } 
 
	
	std::string getTitle ()const
  {
	return title;
  }
   
std::string getAuthor () const
  {
	return author;
  }
   
std::string getISBN () const
  {
	return isbn;
  }
   
bool getAvailability () const
  {
	return isAvailable;
  }
   

	
  void setAvailability (bool avail)
  {
	isAvailable = avail;
  } 
 
	
  void displayBookInfo () const
  {
	
std::
	  cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " <<
	  isbn << "\nAvailability: " << (isAvailable ? "Available" :
									 "Not Available") << std::endl;

} 
};

 
class User
{

private:
std::string name;
  
std::string userId;
  
std::vector < Book * >borrowedBooks;

 
public:
	
User (std::string n, std::string id):name (n), userId (id)
  {
  } 
 
	
	std::string getName ()const
  {
	return name;
  }
   
std::string getUserId () const
  {
	return userId;
  }
   

	
  void borrowBook (Book & book)
  {
	
if (book.getAvailability ())
	  {
		
borrowedBooks.push_back (&book);
		
book.setAvailability (false);
	  
}
	else
	  {
		
std::cout << "Book is not available for borrowing." << std::endl;
	  
}
  
}
  
 
	
  void returnBook (Book & book)
  {
	
auto it =
	  std::find (borrowedBooks.begin (), borrowedBooks.end (), &book);
	
if (it != borrowedBooks.end ())
	  {
		
borrowedBooks.erase (it);
		
book.setAvailability (true);
	  
}
	else
	  {
		
std::cout << "Book was not borrowed by this user." << std::endl;
	  
}
  
}
  
 
	
  void displayUserInfo () const
  {
	
std::
	  cout << "Name: " << name << "\nUser ID: " << userId <<
	  "\nBorrowed Books: ";
	
for (const auto & book:borrowedBooks)
	  { 
std::cout << book->getTitle () << ", ";
	  
} 
std::cout << std::endl;

} 
};


 
class Library
{

private:
std::vector < Book > books;
  
std::vector < User > users;

 
public:
	
  void addBook (const Book & book)
  {
	
books.push_back (book);
  
} 
 
	
  void removeBook (const std::string & isbn)
  {
	
books.erase (std::remove_if (books.begin (), books.end (), 
								  [&isbn] (const Book & book)
								  { return book.getISBN () == isbn;
								  }
				  ), books.end ());
  
}
  
 
	
  void searchBookByTitle (const std::string & title) const
  {
	
bool found = false;
	 
for (const auto & book:books)
		{ 
if (book.getTitle () == title)
		  {
book.displayBookInfo ();
		   
found = true;
		   
}
		   
}
		   
if (!found)
		   {
		   
std::cout << "Book not found." << std::endl; 
}
		   
}
		   
 
		   
		   void searchBookByAuthor (const std::string & author) const
		   {
  
bool found = false; 
for (const auto & book:books)
		   { 
if (book.getAuthor () == author)
		   {
book.displayBookInfo (); 
found = true; 
}
			
}
			
if (!found)
			{
			
std::cout << "Book not found." << std::endl; 
}
			
}
			
 
			
			void searchBookByISBN (const std::string & isbn) const
			{
  
bool found = false; 
for (const auto & book:books)
			{ 
if (book.getISBN () == isbn)
			{
book.displayBookInfo (); 
found = true; 
}
			 
}
			 
if (!found)
			 {
			 
std::cout << "Book not found." << std::endl; 
}
			 
}
			 
 
			 
			 void listAllBooks ()const
			 {
			 
if (books.empty ())
			 {
			 
std::cout << "No books available in the library." << std::endl; 
}
			 else
			 {
	
for (const auto & book:books)
			 { 
book.displayBookInfo (); 
} 
} 
} 
 
			 
			 void addUser (const User & user)
			 {
			 
users.push_back (user); 
} 
 
			 
			 User * findUserById (const std::string & userId)
			 {
  
for (auto & user:users)
			 {
			 
if (user.getUserId () == userId)
			 {
			 
return &user; 
}
			 
}
			 
return nullptr; 
}
			 
 
			 
			 void listAllUsers ()const
			 {
			 
if (users.empty ())
			 {
			 
std::cout << "No users registered in the library." << std::endl; 
}
			 else
			 {
	
for (const auto & user:users)
			 { 
user.displayUserInfo (); 
} 
} 
} 
}; 
 

int main() {
    Library library;

    
    Book book1("The Great Gatsby", "F. Scott Fitzgerald", "1234567890");
    Book book2("1984", "George Orwell", "0987654321");
    Book book3("To Kill a Mockingbird", "Harper Lee", "1122334455");

    
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    
    std::cout << "Listing all books in the library:" << std::endl;
    library.listAllBooks();
    std::cout << std::endl;

    
    User user1("John Doe", "U001");

    
    library.addUser(user1);

    
    std::cout << "Listing all users in the library:" << std::endl;
    library.listAllUsers();
    std::cout << std::endl;

    
    User* userPtr = library.findUserById("U001");
    if (userPtr) {
        std::cout << "User borrowing 'The Great Gatsby':" << std::endl;
        userPtr->borrowBook(book1);
    }

    
    std::cout << "Displaying user info after borrowing a book:" << std::endl;
    userPtr->displayUserInfo();
    std::cout << std::endl;

    
    std::cout << "Searching for book by title '1984':" << std::endl;
    library.searchBookByTitle("1984");
    std::cout << std::endl;

    std::cout << "Searching for book by author 'Harper Lee':" << std::endl;
    library.searchBookByAuthor("Harper Lee");
    std::cout << std::endl;

    std::cout << "Searching for book by ISBN '1234567890':" << std::endl;
    library.searchBookByISBN("1234567890");
    std::cout << std::endl;

    
    if (userPtr) {
        std::cout << "User returning 'The Great Gatsby':" << std::endl;
        userPtr->returnBook(book1);
    }

    
    std::cout << "Displaying user info after returning a book:" << std::endl;
    userPtr->displayUserInfo();

    return 0;
}
