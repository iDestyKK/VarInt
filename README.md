#VarInt
The moment you realize C++ allows you to do WAY too much.

C++ is a very powerful language. It allows you to utilize polymorphism in classes and structures to allow them to work with any datatype. We use ints, doubles, floats, chars, etc to store data. However, these are of a fixed size. Often in compuationally heavy programs, you will use an int and find out that you will run out of bits (As it is 32-bit) if the number goes too high. When numbers go too high, they "roll back" to 0 (if unsigned).

VarInt is a class that I wrote to implement an "pseudo" integer-like class where "you" define the amount of bits it can allocate. It takes the bit amount as a template parameter.

Here is an example of how to declare a 64-bit VarInt and increment it by 1:
```c++
int main() {
	varint<64> stuff = 24;
	stuff++;
	cout << (int)stuff << end; //Prints out "25"
}
```
Don't get too excited though yet, it is still a work in progress and a side project. As of now, you can only increment and decrement with "++" and "--" operators respectively. Also you can set the value with the "=" operator. No addition, subtraction, multiplication, division, or modulation is supported yet.
<i>Developed on a Raspberry Pi 3</i>
