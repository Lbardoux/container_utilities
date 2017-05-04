# operator<< for STL containers
---

## Compilation prerequisite
You just need to provide a C++ version at least C++11 when you compile :
> -std=c++11

---
---

## Usage
### std::coutable
You just have to call the operator<< as usual :
```
std::cout << myvector << std::endl;
std::cout << mytuple  << std::end;
std::cout << myStack  << std::endl;
```
But be aware, there is no flush or newline characte with my operators.

---

### Iterate through std::stack or/and std::queue
You could also iterate through these containers without any useless copy or loss.
To do so, you could now use the begin() and end() functions (non member) as c++ standard
functions.
```
#include <algorithm>
#include <functional>
#include <iostream>

#include "stl_streaming.hpp"

int main()
{
	std::stack<int> stack;
	for(int i=0;i<15;++i)
		stack.push(i);
	
	std::cout << "before : " << stack << std::endl;
	std::for_each(begin(stack), end(stack), [](int& i){i += 2;});
	std::cout << "after  : " << stack << std::endl;

	return 0;
}
```
In addition, you could write template code using begin() and end() because they work with other
standard containers such as std::list, std::vector, etc.

#### Warning !
But don't bother try to use them for erase, remove, or moving element because it will break your program (you're aware).
Use them to iterate in read, or to modify all values instead.
In a nutshell :
  - std::cout = fine
  - apply_to_each = fine
  - erase = Segfault

---

### Less useful, check if a type is tuplable.
It's just a trait to ensure a type **T** doew match for the tuple interface.
Meaning there exist implementation for :
 1. std::tuple_size
 2. std::get<0> at least

---
---
## Copyright
Copyright 2017 MTLCRBN
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
