# Contributing to 15Slide
Thanks for taking time to contribute to 15Slide. Here are a few thing you can help with
## Coding
### Code Formating Guidelines
#### Licencing
In the first and second line of all 15Slide source and header files, put:

`//Copyright 2018 John Jekel`

`//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms`

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
* With the [wiki](https://github.com/JZJisawesome/15Slide/wiki)
* With the [website](https://github.com/JZJisawesome/15Slide/tree/master/docs)
* With documentation in code
