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
 *     Changelog of library is located at the bottom of "varint.hpp".
 *
 * Author:
 *     Clara Van Nguyen
 *
 * For documentation and details on every function in this library, visit the following URL:
 * http://web.eecs.utk.edu/~ssmit285/lib/varint/index.html
 */

#ifndef __VARINT_TPP__
#define __VARINT_TPP__

//#include "varint.hpp"

#define __UIN__ \
	template <unsigned int N>
#define __UIN_T__ \
	template <unsigned int N> \
	template <typename T>

//Constructor
__UIN__ varint<N>::varint() {
	init();
}

__UIN_T__ varint<N>::varint(const T& i) {
	init();
	operator=(i);
}

//Destructor
__UIN__ varint<N>::~varint() {
	//Free dynamically allocated memory
	delete[] _byte;
}

//Ad-Hoc Polymorphism
__UIN_T__ varint<N>& varint<N>::operator=(const T& i) {
	//memset((char*)_byte, 0, (size_t)_num_byte);
	fill(_byte, _byte + _num_byte, 0);
	bit_copy((long long int) i, sizeof(T));
	return *this;
}

__UIN_T__ varint<N>::operator T() const {
	return *(T*)_byte; //Using some C magic to cast to any integer type easily by returning the bytes.
}

__UIN__ varint<N>& varint<N>::operator++(int i) {
	return operator++(); //Cheat like a champion
}

__UIN__ varint<N>& varint<N>::operator++() {
	/*if (_negative)
		decrement();
	else*/
		increment();
	return *this;
}

__UIN__ varint<N>& varint<N>::operator--(int i) {
	return operator--(); //Still cheating over here.
}

__UIN__ varint<N>& varint<N>::operator--() {
	/*if (_negative)
		increment();
	else*/
		decrement();
	return *this;
}

__UIN__ void varint<N>::init() {
	_num_bit  = N;
	_num_byte = (N / 8) + (N % 8 != 0);
	_negative = false;
	_MSB = -1;
	_byte = new unsigned char[_num_byte];
}

__UIN__ void varint<N>::bit_copy(long long int value, unsigned int byte_count) {
	cn_u64 nv  = (cn_u64) ((value < 0) ? -1 * value : value),
	       def = 0;
	
	bool _val;
	for (unsigned int i = 0; i < byte_count * 8 && i < _num_bit; i++) {
		//I like writing nasty things
		_val = (nv & ((cn_u64)0x1 << (((size_u64 * 8) - 1) - (((size_u64 * 8) - 1) - i)))) ? 1 : 0;
		_byte[i / 8] |= _val << (i % 8);
	}

	//Find MSB
	for (_MSB = _num_byte - 1; _MSB >= 0; _MSB--) {
		if (_byte[_MSB] != 0)
			break;
	}

	print_bits();
}

__UIN__ void varint<N>::print_bits() {
	//DEBUG FUNCTION
	bool _val;
	for (unsigned int i = 0; i < _num_bit; i++) {
		_val = _byte[i / 8] & ((0x1 << (7 - (7 - i % 8)))) ? 1 : 0;
		cout << _val;
	}
	cout << endl;
}

__UIN__ void varint<N>::increment() {
	if (_byte[0] == 0 && _MSB == -1)
		_MSB = 0;
	_byte[0]++;
	unsigned int pos = 0;
	while (_byte[pos] == 0 && pos < _num_byte)
		_MSB++,
		_byte[++pos]++;
}

__UIN__ void varint<N>::decrement() {
	if (_MSB == -1) {
		fill(_byte, _byte + _num_byte, 0xFF);
		_MSB = _num_byte - 1;
	} else {
		unsigned int pos = 0;
		while (pos <= _MSB) {
			if (_byte[pos] > 0) {
				_byte[pos]--;
				if (_byte[pos] == 0)
					_MSB--;
				break;
			} else {
				_byte[pos] = 0xFF;
				pos++;
			}
		}
	}
}

#endif
