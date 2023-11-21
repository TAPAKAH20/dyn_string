#include "dynamic_string.h"

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

// Constructors
// basic init
DynamicString::DynamicString(){
	length = 0;
	capacity = 0;
	str_ptr = nullptr;
}


// Copy first N
DynamicString::DynamicString(const char* init_str_ptr, size_t n){
	str_ptr = new char[n];
	copy_n(init_str_ptr, n);
	length = n;
	capacity = n;
}

//Find null character and copy chars
DynamicString::DynamicString(const char* init_str_ptr){
	size_t n = 0;
	while(str2[n] != '\x00') n++;
	str_ptr = new char[n];
	copy_n(init_str_ptr, n);
	length = n;
	capacity = n;
}

// Copy constructor
DynamicString::DynamicString(DynamicString& init_str_ptr){
	length = init_str_ptr.length();
	capacity = init_str_ptr.capacity();
	str_ptr = new char[capacity];
	copy_n(init_str_ptr, length);
}

// Move constructor
DynamicString::DynamicString(DynamicString&& init_str_ptr){

}

// Initialiazer list constructor
DynamicString::DynamicString(initializer_list<char> il){

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
size_t DynamicString::find(char c){
	for(size_t i=0; i<=length; i++)
		if (str_ptr[i] == c) return i;
	return -1;
}
size_t DynamicString::length(){ 	return length; }
size_t DynamicString::capacity(){	return capacity; }
char DynamicString::at(size_t i){
	if(i < length)
		return str_ptr[i];
	else if(i == length)
		return 0x00;				// C-style string ending
	else
		throw std::out_of_range;
}

void DynamicString::resize(size_t new_capacity){
	if(new_capacity > max_capacity) throw std::length_error;
	char* new_str_ptr = new char[new_capacity];
	for(size_t i = 0; i<length && i<new_capacity; i++){
		new_str_ptr[i] = str_ptr[i];
	}
	delete str_ptr;
	str_ptr = new_str_ptr;
	capacity = new_capacity;
	length = (length < new_capacity) ? length : new_capacity;
}

void DynamicString::shrink_to_fit(){ resize(length);}
// Double the capacity until enough to fit n
void DynamicString::resize_to_fit(size_t n){
	size_t new_capacity = (capacity == 0) ? 1 : capacity;
	while(new_capacity < n) new_capacity *= 2;
 	resize(new_capacity);
}


// Character access
char DynamicString::operator[](size_t i){	return at(i); }


// Assignment operators
DynamicString& DynamicString::operator=(const DynamicString& str2){
	size_t length2 = str2.length();
	resize_to_fit(length2);
	copy_n(str2, length2);
}

DynamicString& DynamicString::operator=(const char* str2){
	size_t length2 = 0;
	while(str2[length2] != '\x00') length2++;
	resize_to_fit(length2);
	copy_n(str2, length2);
}
//TODO move assignment

// Concatination operators
DynamicString DynamicString::operator+(const DynamicString& str1, const DynamicString& str2){
	DynamicString res = new DynamicString();
	res.resize_to_fit(str1.length + str2.length);
	for(size_t i = 0; i<str1.length; i++){
		res[i] = str1[i];
	}
	for (size_t i = 0; i < str2.length; i++){
		res[str1.length+i+1] = str2[i];
	}

	return res;
}

DynamicString& DynamicString::operator+=(const DynamicString& str2){
	resize_to_fit(length + str2.length);
	for(size_t i = 0; i<str2.length; i++){
		str_ptr[length + 1 + i] = str2[i];
	}
	return *this;
}

//C strings
DynamicString DynamicString::operator+(const char* str1, const char* str2){
	size_t length1 = 0;
	size_t length2 = 0;

	while(str1[length1] != '\x00') length1++;
	while(str2[length2] != '\x00') length2++;

	DynamicString res = new DynamicString();

	res.resize_to_fit(length1 + length2);

	for(size_t i = 0; i<length1; i++){
		res[i] = str1[i];
	}
	for (size_t i = 0; i < length2; i++){
		res[length1+i+1] = str2[i];
	}

	return res;
}

DynamicString& DynamicString::operator+=(const char* str2){
	size_t length2 = 0;

	while(str2[length2] != '\x00') length2++;

	resize_to_fit(length + length2);
	for(size_t i = 0; i<length2; i++){
		str_ptr[length + 1 + i] = str2[i];
	}
	return *this;
}