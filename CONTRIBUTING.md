# Contributing to 15Slide
Thanks for taking time to contribute to 15Slide. Here are a few thing you can help with
## Coding
### Code Formating Guidelines
#### Licencing
In the first lines of all 15Slide source and header files, put a comment:
`   

    This file is part of 15Slide.

    15Slide is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    15Slide is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with 15Slide.  If not, see <https://www.gnu.org/licenses/>.`


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
