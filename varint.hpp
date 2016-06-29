/*
 * VarInt Library
 * 
 * Version 0.0.1 (Last Updated 2016-06-27)
 * 
 * Description:
 *     Implements an integer data type that can be of any number of bits.
 *     The integer disguises itself as a fully functional "integer" via
 *     operator overloading and casting abilities. The size of the bits
 *     is determined with a template parameter (e.g. varint<32> declares
 *     a 32-bit integer).
 *
 *     Changelog of library is located at the bottom of this file.
 *
 * Author:
 *     Clara Van Nguyen
 *
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/varint/index.html
 */

#ifndef __VARINT_HPP__
#define __VARINT_HPP__

#include <cstdio>
#include <cstdlib>

using namespace std;

typedef unsigned long long int cn_u64;
typedef unsigned long long int cn_ull;

#define size_u64 sizeof(cn_u64)
#define size_ull sizeof(cn_ull)

template <unsigned int N>
class varint {
	public:
		varint();
		template<typename T> varint(const T&);
		~varint();

		//Ad-Hoc Polymorphism
		template <typename T> varint& operator= (const T&);
		template <typename T>         operator T() const;
		varint& operator++(int);
		varint& operator++();
		varint& operator--(int);
		varint& operator--();

	private:
		bool           _negative;
		unsigned int   _num_bit,
		               _num_byte;
		int            _MSB;
		unsigned char* _byte;
		
		//Private Functions
		void init();
		void bit_copy(long long int, unsigned int);
		void print_bits();
		void increment();
		void decrement();
};

//To get the compiler to shut up
#include "varint.tpp"

#endif

/***************************************\
    * ** ***    CHANGELOG    *** ** *
\***************************************/

/*
    2016-06-27 (0.0.1)
      - Started writing VarInt.
*/
