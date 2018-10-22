# Contributing to 15Slide
Thanks for taking time to contribute to 15Slide. Here are a few thing you can help with
## Coding
### Code Formating Guidelines
#### Licencing
In the first lines of all new 15Slide source and header files, put a comment:`   

    MIT License

	Copyright (c) DATE AUTHOR

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.`
    
#### Source Documentation
15Slide uses Doxygen comments to document the code. Please try to document all functions in source files, classes in their header files, and varibles in the header files. Be sure to use plenty of comments _inside_ functions as well.

#### Including
Including files (`#include`) should be done in this order, with spaces in between each section. Omit a step if no header of that type is used.
1. The source file's header
2. 15Slide headers starting with ProgramStuff.h
3. External library headers
4. STL and C headers (use angle brackets and "c" headers (eg. `<cstdint>` instead of `<stdint.h>`))
5. Headers that may be enabled or disabled by _preprocessing_.

Also put two blank lines before and after the includes.

#### Everything Combined
Try to make source and header files similar to this.
##### Class Header (.h)
1. Licence comments
2. Header guard
3. 2 spaces
4. Includes
5. 2 spaces
6. Class documentation
7. Class definition
8. Member variable documentation/definition and function definition (any order)
9. Header guard end
##### Source File (.cpp)
1. Licence comments
2. Header guard
3. 2 spaces
4. Includes
5. 2 spaces
6. Function documentation
7. Function implementation
8. (repeat 6 and 7 for each function)
### Bug Squashing (to do)
### Profiling (to do)
## Documentation
As you can probably see, my spelling is not so good (I'm 14!!!). You can help...
- With the [wiki](https://github.com/JZJisawesome/15Slide/wiki)
- With the [website](https://github.com/JZJisawesome/15Slide/tree/master/docs)
- With documentation in code
