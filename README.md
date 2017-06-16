# Containers Ostream
## Synopsis
This header provides some templates to print **STL containers**, **C-style array**
and **array pointer (such as double*)** into *std::ostream*.<br />
The "graphic" (if you can call that graphic) format is quite simple :
  1. Display objects which implements the [Iterator pair idiom](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Iterator_Pair) with this format:
     ```[ elt1 elt2 elt3 ... eltn ]```
  2. Display objects which matches the tuple interface like this :
     ```( elt1 elt2 elt3 ... eltn )```

As you can see, there is no separator, but feel free to edit this file if you want to add
any.
To do so, one can find the official [repository](https://github.com/Lbardoux/container_utilities.git).

---

## Compilation
This is a _.hpp_ so you'll need a C++ compiler (cpt.obvious forever) and provide
at least **-std=c++11** option.<br />
Well done, you're able to use this header within your code !

---

## Tests
If you're a developer, and you want to enhance this code, you could run tests to ensure than you don't break anything.<br />
To do so, one may follow these instructions using **cmake**:
```
# cd test.cpp_directory
mkdir build
cd build
cmake ..
make
ctest
```

If nothing prompt, well done, tests are successfull.

---

## Supported Containers
Every STL containers are supported.

In addition, except char[] and unsigned char[] (because it conflicts with current STL implementation), every possible
**C-style arrays** are supported (as long as the type of your array implements the operator<<(std::ostream&)).<br />
Keep in mind than this file won't help you for pointers, this in particular won't work at all :
```
int* array = new int[6];
// fill it.
std::cout << array << std::endl;
// display a random memory address.
```
You're maybe thinking : "Oh why ?". This is because I'm using template inference on C-style array to deduce their length.
It is typically impossible with such pointers. Even worse, it could collide with another intention of your, showing
the address of this pointer for instance.
For these cases, it is less user friendly, because you'll have to specify by yourself :
  - The array length.
  - Your intention of displaying the content and not the address of the first element.

```
double* arr = new double[5];
// Fill it with whatever you want
std::cout << array_cast<double>(arr, 5) << std::endl;
// Here is the content of your array.
```

---

## Copyright
Copyright 2017 MTLCRBN<br />
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright notice, this list of
     conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright notice, this list
     of conditions and the following disclaimer in the documentation and/or other materials
     provided with the distribution.
  3. Neither the name of the copyright holder nor the names of its contributors may be
     used to endorse or promote products derived from this software without specific prior
     written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
