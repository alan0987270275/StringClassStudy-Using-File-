// Fig. 11.10: String.cpp
// String class member-function and friend-function definitions.
#include <iostream>
#include <iomanip>
#include <cstring> // strcpy and strcat prototypes
#include <cstdlib> // exit prototype
#include "Stringh.h" // String class definition
using namespace std;

// conversion (and default) constructor converts char * to String
String::String(const char *s)
:length((s != 0) ? strlen(s) : 0)
{
	setString(s);
}

// copy constructor
String::String(const String &copy)
:length(copy.length)
{
	setString(copy.sPtr);
}

// Destructor
String::~String()
{
	delete[]sPtr;
}


void  String::load(ifstream &inFile)//load the file.
{
	char *read = new char[100];

	inFile.getline(read, '\n');
	int count = strlen(read);
	length = count;
	setString(read);
}

void String::write(ofstream &outFile)//write the file.
{
	char *newword = new char[length+1];
	newword = sPtr;
	outFile << newword << endl;
}


// utility function called by constructors and operator=
void String::setString(const char *string2)
{
	sPtr = new char[length + 1];
	if (string2 != 0)
		strcpy(sPtr, string2);
	else
		sPtr[0] = '\0';
}

// overloaded = operator; avoids self assignment
const String &String::operator=(const String &right)
{
	if (&right != this)
	{
		delete[]sPtr;
		length = right.length;
		setString(right.sPtr);
	}
	else
		cout << "Error!" << endl;
	return *this;
}

// concatenate right operand to this object and store in this object
const String &String::operator+=(const String &right)
{
	int newlength = length + right.length;
	char *tempString = new char[newlength + 1];
	strcpy(tempString, sPtr);
	strcpy(tempString + length, right.sPtr);
	delete[]sPtr;
	sPtr = tempString;
	length = newlength;
	return *this;
}

// is this String empty?
bool String::operator!() const
{
	return length == 0;
}

// Is this String equal to right String?
bool String::operator==(const String &right) const
{
	return strcmp(sPtr, right.sPtr) == 0;
}

// Is this String less than right String?
bool String::operator<(const String &right) const
{
	return strcmp(sPtr, right.sPtr) < 0;
}


bool String::operator>(const String &right) const
{
	return strcmp(sPtr, right.sPtr) > 0;
}

// return reference to character in String as a modifiable lvalue
char &String::operator[](int subscript)
{
	if (subscript < 0 || subscript >= length)
		cout << "Error" << endl;
	return sPtr[subscript];
}

// return reference to character in String as rvalue
char String::operator[](int subscript) const
{
	if (subscript < 0 || subscript >= length)
		cout << "Error" << endl;
	return sPtr[subscript];
}

// return a substring beginning at index and of length subLength
String String::operator()(int index, int subLength) const
{

	if (subLength < 0 || index >= length || index < 0)
		return "";

	int newlength = 0;

	if ((subLength == 0) || (index + subLength>length))
		newlength = length - index;
	else
		newlength = subLength;

	char *tempString = new char[newlength + 1];
	strncpy(tempString, &sPtr[index], newlength);
	tempString[newlength] = '\0';
	String temp(tempString);
	delete[]tempString;
	return temp;
}

// return string length
int String::getLength() const
{
	return length;
}

// overloaded output operator
ostream &operator<<(ostream &output, const String &s)
{
	output << s.sPtr;
	return output;
}

// overloaded input operator
istream &operator>>(istream &input, String &s)
{
	char temp[100];
	input >> setw(100) >> temp;
	s = temp;
	return input;
}