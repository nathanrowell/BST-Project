//#include "BST.hpp"
//#include "Book.hpp"
// Nathan Rowell CISC220013
#include "Library.hpp"
#include <iostream>
using namespace std;

int main() {
	// Testing book comparisons
	//Book b1("Acorns","Shmoe, Joe",1992, "Science Books",12345,3.5);
	//Book b2("Birch Trees","Shmoe, Joe",1994, "Science Books",34567,4.0);
	//Book b3("Dogs Are My Best Friend","David, Alex",1955, "Books for Children",22222,4.0);
	//cout << (b1 < b1);
	//cout << (b1 < b2);
	//cout << (b1 < b3);
	//cout << (b1 == b1);
	//cout << (b1 == b2);
	//cout << (b1 != b3);
	//cout << (b1 > b1);
	//cout << (b1 > b2);
	//cout << (b1 > b3);
	//cout << (b1 <= b1);
	//cout << (b1 <= b2);
	//cout << (b1 <= b3);
	//cout << (b1 >= b1);
	//cout << (b1 >= b2);
	//cout << (b1 >= b3);

	Library library( "C:\\Users\\natha\\Downloads\\BSTLibrary\\halloween.txt");

	library.menu();


	return 0;
}
