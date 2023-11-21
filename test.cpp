#include "dynamic_string.h"

#include <iostream>

int main(int argc, char const *argv[]){
	

	DynamicString str = DynamicString("0");

	std::cout << str << std::endl;
	std::cout << (str.find('r') == -1) << std::endl;
	std::cout << str.length() << std::endl;
	std::cout << str.capacity() << std::endl;

	str += "123";
	std::cout << str << std::endl;
	std::cout << str.length() << std::endl;
	std::cout << str.capacity() << std::endl;
	std::cout << str[0] << std::endl;

	str = "123456789";
	std::cout << str << std::endl;
	std::cout << str.length() << std::endl;
	std::cout << str.capacity() << std::endl;

	str += str;
	std::cout << str << std::endl;
	std::cout << str+str << std::endl;
	std::cout << str.length() << std::endl;
	std::cout << str.capacity() << std::endl;
	return 0;
}