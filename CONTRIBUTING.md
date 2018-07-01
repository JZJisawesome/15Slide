# Contributing to 15Slide

## Licencing
In the first and second line of all 15Slide source and header files, put:

`//Copyright 2018 John Jekel`

`//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms`

## Documentation
15Slide uses Doxygen comments to document the code. Please be sure to document all functions in source files, classes in their header files, and varibles in the header files. LEAVE NOTHING UNDOCUMENTED, and be sure to use plenty of comments _inside_ functions.

## Including
Including files (`#include`) should be done in this order, with spaces in between each section. Omit a step if no header of that type is used.
1. The source file's header
2. 15Slide headers starting with ProgramStuff.h
3. External library headers
4. STL and C headers (use angle brackets and "c" headers (eg. `<cstdint>` instead of `<stdint.h>`))
5. Headers that may be enabled or disabled by _preprocessing_.

Also put two blank lines before and after the includes.

## Everything Combined
### Class Header (.h)
1. Licence comments
2. Header guard
3. 2 spaces
4. Includes
5. 2 spaces
6. Class documentation
7. Class definition
8. Member variable documentation/definition and function definition (any order)
9. Header guard end
### Source File (.cpp)
1. Licence comments
2. Header guard
3. 2 spaces
4. Includes
5. 2 spaces
6. Function documentation
7. Function implementation
8. (repeat 6 and 7 for each function)
