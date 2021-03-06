# VarInt
<i>The moment you realize C++ allows you to do WAY too much.</i>

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
</br><i>Developed on a Raspberry Pi 3</i>

<h2>Computation Time</h2>
Dynamically sized memory comes at a cost. This library uses software to manage the bits as they are stored in an <b>unsigned char</b> array. The only time hardware is used is for roll-back or roll-forwarding numbers from 0x00 to 0xFF and back. To ease some of the computation time, the class keeps track of the MSB [Most Significant Bit] in order to reduce loops to constant time if the number is 0xFF or lower, 2 loops if the number is 0xFFFF or lower, etc.
<h2>Signed Int?</h2>
If you cast it to a signed type right, yes it can be a signed integer! If you cast it to an unsigned integer type, it will be unsigned. This works because of the magic of <b>Two's Complement</b>, and a little bit of help from hardware. ;)
<h2>What about floats?</h2>
Sorry, this is for integers only. If I ever learn about floating point and how it works bitwise, I may consider doing something like this for floating point. But don't get your hopes up.
