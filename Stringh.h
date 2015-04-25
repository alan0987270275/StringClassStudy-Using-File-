// Fig. 11.9: String.h
// String class definition with operator overloading.
#ifndef STRING_H
#define STRING_H
#include<fstream>
#include <iostream>
using namespace std;

class String
{
	friend ostream &operator<<(ostream &output, const String &s);
	friend istream &operator>>(istream &, String &);
public:
	String(const char * = ""); // conversion/default constructor
	String(const String &); // copy constructor
	~String(); // destructor

	void load(ifstream &inFile);//load the file.
	void write(ofstream &outFile);//write the file.

	const String &operator=(const String &); // assignment operator
	const String &operator+=(const String &); // concatenation operator

	bool operator!() const; // is String empty?
	bool operator==(const String &) const; // test s1 == s2
	bool operator<(const String &) const; // test s1 < s2
	bool operator>(const String &right) const;
	// test s1 > s2

	// test s1 != s2
	bool operator!=(const String &right) const
	{
		return !(*this == right);
	}

	// test s1 <= s2
	bool operator<=(const String &right) const
	{
		return !(*this>right);
	}

	// test s1 >= s2
	bool operator>=(const String &right) const
	{
		return !(*this < right);
	}

	char &operator[](int); // subscript operator (modifiable lvalue)
	char operator[](int) const; // subscript operator (rvalue)
	String operator()(int, int = 0) const; // return a substring
	int getLength() const; // return string length
private:
	int length; // string length (not counting null terminator)
	char *sPtr; // pointer to start of pointer-based string

	void setString(const char *); // utility function
}; // end class String

#endif