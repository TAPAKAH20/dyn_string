#include "dynamic_string.h"

#include <iostream>
#include <array>
#include <random>
#include <utility>
#include <algorithm>


int main(int argc, char const *argv[]){
	
	std::array<DynamicString*, 10> str_arr;


	std::random_device rdChar;  // a seed source for the random number engine
    std::mt19937 charGen(rdChar()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> charDistrib(48, 122); //random printable ascii cahracter

    std::random_device rdLen;  // a seed source for the random number engine
    std::mt19937 lenGen(rdLen()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> lenDistrib(5, 10); // random string length

    // Generate 10 random strings
    DynamicString str = DynamicString();
    for(int i=0; i<10; i++){
    	int randLength = lenDistrib(lenGen);
    	for(int j = 0; j<randLength; j++){
    		str += static_cast<char>(charDistrib(rdChar));
    	}
    	str_arr[i] = new DynamicString(std::move(str));
    }
	

    // Print generated strings in initial order
    for(int i=0; i<10; i++){
    	std::cout << *str_arr[i] << std::endl;
    }

    // sort using case insensetive compare
    std::sort(str_arr.begin(), str_arr.end(), 
    			[](DynamicString* s1, DynamicString* s2){ return (s1->compare(*s2, true)) > 0; });

    std::cout << std::endl;

    // Print generated strings in sorted order
    for(int i=0; i<10; i++){
    	std::cout << *str_arr[i] << std::endl;
    }

	return 0;
}