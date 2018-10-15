# Installing 15Slide
## Downloading a build
There may be compiled binaries avaliable in a 15Slide [release](https://github.com/JZJisawesome/15Slide/releases).

## Building
It is suggested that you grab a [stable release](https://github.com/JZJisawesome/15Slide/releases) instead of building from the latest master branch.
### Linux
#### GUI
1. Download or clone the 15Slide source files
2. Get the termcolor library from [http://termcolor.readthedocs.io/](http://termcolor.readthedocs.io/)
3. Go to where you downloaded the master branch, and copy the _include_ folder from the termcolor master into it
4. Open a terminal in the 15Slide master branch and run `autoreconf --install` to create the proper build enviornment
5. Run the infamous `./configure; make` to build the 15Slide binary
6. [Run the 15Slide executable](https://jzjisawesome.github.io/15Slide/Running-15Slide) which is now in the current directory

Make sure the data folder is in the same directory 15Slide is being run from, or the GUI (GTKSlide) may not work.

#### Terminal
1. Download or clone the 15Slide source files
2. Get the termcolor library from [http://termcolor.readthedocs.io/](http://termcolor.readthedocs.io/)
3. Go to where you downloaded the master branch, and copy the _include_ folder from the termcolor master into it
4. Comment out lines in configure.ac, Makefile.am, and the ENABLE_GUI line in src/ProgramStuff
5. Open a terminal in the 15Slide master branch and run `autoreconf --install` to create the proper build enviornment
6. Run the infamous `./configure; make` to build the 15Slide binary
7. [Run the 15Slide executable](https://jzjisawesome.github.io/15Slide/Running-15Slide) which is now in the current directory

#### For Windows (minGW cross-platform, non GTKSlide)
This is broken. Feel free to help out and find a way to build.

1. Follow steps _one_ to _three_ in the Linux build instructions
2. Comment out `compiler=g++` in build.sh and uncomment `#compiler=i686-w64-mingw32-g++`. You may need to specify a different compiler or install one depending on your setup
3. Open a terminal in the 15Slide master branch and run `sh ./build.sh`
4. The compiled 15Slide is in the new bin folder, but you may need to add the libgcc_s_sjlj-1.dll and libstdc++-6.dll libraries or something similar to the directory

### Windows (to do)
### macOS (to do)
