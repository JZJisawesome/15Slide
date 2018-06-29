# 15Slide
A cross-platform(ish) slidy-tile game written with C++17!
![15Slide in the terminal](https://raw.githubusercontent.com/JZJisawesome/15Slide/master/images/15Slide_terminal.png "15Slide in the terminal")
## Building
### Linux (not done)
1. Get the termcolor library from [http://termcolor.readthedocs.io/](http://termcolor.readthedocs.io/)
2. Install the gtkmm libraries for your distrubution (see [https://developer.gnome.org/gtkmm-tutorial/](https://developer.gnome.org/gtkmm-tutorial/))
3. Checkout the 15 Slide, and put the termcolor folder in the src folder
5. Run
## Status and To Do
* Grid15 classes are done except for more optomization
* CommandUI is pretty much done, except for better parsing of invalid arguments and commands
* Making a GUI (see the GTKSlide branch) and one that works with Windows too
* Setup command line parser
* Create consistent versioning
* Setup makefiles or some other build system
* Spelling needs work, and UTF-8 support with Windows builds needs fixing
* Better/more documentation (espicially this file)
* Testing for macOS (I don't have a mac of any kind)
* Choose a licence
* Decide to ditch Windows (probably not)
## Dependencies
* termcolor ([http://termcolor.readthedocs.io/](http://termcolor.readthedocs.io/))
* gtkmm ([https://gtkmm.org/](https://gtkmm.org/))
