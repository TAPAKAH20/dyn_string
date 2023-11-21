#ifndef __DYNAMIC_STRING_H_
#define __DYNAMIC_STRING_H_

#include <cstddef>
#include <initializer_list>

class DynamicString
{
public:
	DynamicString();
	DynamicString(const char* init_str_ptr);
	DynamicString(const char* init_str_ptr, size_t n);
	DynamicString(DynamicString& init_str_ptr); // Copy constructor
	DynamicString(DynamicString&& init_str_ptr); // Move constructor
	DynamicString(initializer_list<char> il);

	~DynamicString();

	
	friend DynamicString& operator=(const DynamicString& str2);
	friend DynamicString& operator=(const DynamicString&& str2); // Move assignment
	friend DynamicString& operator=(const char* str2);
	friend DynamicString operator+(const DynamicString& str1, const DynamicString& str2);
	friend DynamicString& operator+=(const DynamicString& str2);
	friend DynamicString operator+(const char* str1, const char* str2);
	friend DynamicString& operator+=(const char* str2);
	friend char operator[](size_t i);


	size_t length();
	size_t capacity();
	char at(size_t i);

	void shrink_to_fit();
	void resize_to_fit(size_t n);
	void resize(size_t new_capacity);

	size_t find(char c);
	DynamicString substr(size_t from, size_t n);


private:
	size_t length;
	size_t capacity;
	const size_t max_capacity = 4294967291; // 2^32
	char* str_ptr;

	void copy_n(const char* str2, size_t n);
};

#endif // __DYNAMIC_STRING_H_