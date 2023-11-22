#include "dynamic_string.h"

#include <cstddef>			// size_t
#include <cctype>			// tolower
#include <stdexcept>		//range and len errors

// Constructors
// basic init
DynamicString::DynamicString(){
	len = 0;
	cap= 0;
	str_ptr = nullptr;
}


// Copy first N
DynamicString::DynamicString(const char* init_str, size_t n){
	str_ptr = new char[n];
	copy_n(init_str, n);
	len = n;
	cap= n;
}

//Find null character and copy chars
DynamicString::DynamicString(const char* init_str){
	size_t n = 0;
	while(init_str[n] != '\x00') n++;
	str_ptr = new char[n];
	copy_n(init_str, n);
	len = n;
	cap= n;
}

// Copy constructor
DynamicString::DynamicString(DynamicString& init_str){
	len = init_str.length();
	cap = init_str.capacity();
	str_ptr = new char[cap];
	copy_n(init_str.string(), len);
}

// Move constructor
DynamicString::DynamicString(DynamicString&& init_str){
	delete str_ptr;
	// Move data
	str_ptr = init_str.str_ptr;
	len = init_str.len;
	cap = init_str.cap;

	// Clean up the initializer
	init_str.len = 0;
	init_str.cap = 0;
	init_str.str_ptr = nullptr;
}



// Destructor
DynamicString::~DynamicString(){
	delete str_ptr;
}

//Utility functions
void DynamicString::copy_n(const char* str2, size_t n){
	for(size_t i = 0; i<n; i++)
		str_ptr[i] = str2[i];
}

size_t DynamicString::find(char c) const{
	for(size_t i=0; i<len; i++)
		if (str_ptr[i] == c) return i;
	return -1;
}

bool DynamicString::empty() const{		return len==0;}
size_t DynamicString::length() const{ 	return len; }
size_t DynamicString::capacity() const{	return cap; }
const char* DynamicString::string() const{return str_ptr; }

char& DynamicString::at(size_t i){
	if(i < len){
		return str_ptr[i];
	}else
		throw std::out_of_range("Out of bounds accsses");
}
char DynamicString::at(size_t i) const{
	if(i < len){
		return str_ptr[i];
	}else
		throw std::out_of_range("Out of bounds accsses");
}

void DynamicString::resize(size_t new_capacity){
	if(new_capacity > max_cap) throw std::length_error("Maximum capacity exceeded.");
	char* new_str_ptr = new char[new_capacity];
	for(size_t i = 0; i<len && i<new_capacity; i++){
		new_str_ptr[i] = str_ptr[i];
	}
	delete str_ptr;
	str_ptr = new_str_ptr;
	cap= new_capacity;
	len = (len < new_capacity) ? len : new_capacity;
}

void DynamicString::shrink_to_fit(){ resize(len);}
// Double the capuntil enough to fit n
void DynamicString::resize_to_fit(size_t n){
	if(n > max_cap) throw std::length_error("Maximum capacity exceeded.");
	size_t new_cap = (cap == 0) ? 1 : cap;
	while(new_cap < n) new_cap*= 2;
	if(new_cap > max_cap) new_cap = max_cap;
 	resize(new_cap);
}

void DynamicString::clear(){
	delete str_ptr;
	len = 0;
	cap = 0;
}

// Return is negative if this string is earlier in the lexicographical order
// and 0 if both are equal
int DynamicString::compare(const DynamicString& str2, bool ignore_case /*=false*/) const{
	if(!ignore_case){
		for(size_t i = 0; i < len && i < str2.length(); i++)
			if(str_ptr[i] - str2[i] != 0)
				return str_ptr[i] - str2[i];
		return len - str2.length();
	}else{
		for(size_t i = 0; i < len && i < str2.length(); i++)
			if(std::tolower(str_ptr[i]) - std::tolower(str2[i]) != 0){
				return std::tolower(str_ptr[i]) - std::tolower(str2[i]);
			}
		return len - str2.length();
	}
}



// Operator overloads

// Character access
char DynamicString::operator[](size_t i) const{	return at(i); }
char& DynamicString::operator[](size_t i){		return at(i); }

// Assignment operators
DynamicString& DynamicString::operator=(const DynamicString& str2){
	size_t length2 = str2.length();
	resize_to_fit(length2);
	copy_n(str2.string(), length2);
	len = length2;
	return *this;
}

DynamicString& DynamicString::operator=(DynamicString&& str2){
	delete str_ptr;
	// Move data
	str_ptr = str2.str_ptr;
	len = str2.len;
	cap = str2.cap;

	// Clean up the initializer
	str2.str_ptr = nullptr;
	str2.clear();
	return *this;
}

// C-style strings
DynamicString& DynamicString::operator=(const char* str2){
	size_t length2 = 0;
	while(str2[length2] != '\x00') length2++;
	
	resize_to_fit(length2+1);
	copy_n(str2, length2+1);
	len = length2;
	return *this;
}

// Concatination operators
DynamicString DynamicString::operator+(const DynamicString& str2){
	size_t length2 = str2.length();

	DynamicString res(*this);
	res.resize_to_fit(len + length2);
	res.len = len + length2;

	for (size_t i = 0; i < length2; i++){
		res[len+i] = str2[i];
	}


	return res;
}

// C strings concatination
DynamicString DynamicString::operator+(const char* str2){
	size_t length2 = 0;

	while(str2[length2] != '\x00') length2++;

	DynamicString res = DynamicString(*this);
	res.resize_to_fit(len +length2);
	res.len = len + length2;

	for (size_t i = 0; i < length2; i++){
		res[len+i] = str2[i];
	}
	return res;
}

DynamicString& DynamicString::operator+=(const DynamicString& str2){
	resize_to_fit(len + str2.length());
	for(size_t i = 0; i<str2.length(); i++){
		str_ptr[len + i] = str2[i];
	}
	len += str2.length();
	return *this;
}

DynamicString& DynamicString::operator+=(const char* str2){
	size_t length2 = 0;

	while(str2[length2] != '\x00') length2++;
	

	resize_to_fit(len + length2);
	for(size_t i = 0; i<length2; i++){
		str_ptr[len + i] = str2[i];
	}
	len += length2;
	return *this;
}
DynamicString& DynamicString::operator+=(const char c){
	resize_to_fit(len + 1);
	str_ptr[len] = c;
	len ++;
	return *this;
}


// Stream operators
std::ostream& operator<< (std::ostream& os, const DynamicString& str){
	os << str.str_ptr;
	return os;
}