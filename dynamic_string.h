#ifndef __DYNAMIC_STRING_H_
#define __DYNAMIC_STRING_H_

#include <cstddef> //size_t
#include <initializer_list> // initializer constructor

class DynamicString
{
public:
	DynamicString();
	DynamicString(const char* init_str_ptr);
	DynamicString(const char* init_str_ptr, size_t n);
	DynamicString(DynamicString& init_str_ptr); // Copy constructor
	DynamicString(DynamicString&& init_str_ptr); // Move constructor
	//DynamicString(initializer_list<char> il);

	~DynamicString();


	char& operator[](size_t i);
	char operator[](size_t i) const;

	DynamicString& operator=(const DynamicString& str2);
	DynamicString& operator=(const DynamicString&& str2); // Move assignment
	DynamicString& operator=(const char* str2);

	DynamicString operator+(const DynamicString& str2);
	//DynamicString operator+(const char* str1, const char* str2);

	DynamicString& operator+=(const DynamicString& str2);
	DynamicString& operator+=(const char* str2);



	


	size_t length() const;
	size_t capacity() const;
	char& at(size_t i);
	char at(size_t i) const;

	void shrink_to_fit();
	void resize_to_fit(size_t n);
	void resize(size_t new_capacity);

	size_t find(char c) const;
	DynamicString substr(size_t from, size_t n) const;
	int compare(const DynamicString& str2) const;

	const char* string() const;


private:
	size_t len;
	size_t cap;
	const size_t max_cap = 4294967291; // 2^32
	char* str_ptr;

	void copy_n(const char* str2, size_t n);
};

#endif // __DYNAMIC_STRING_H_