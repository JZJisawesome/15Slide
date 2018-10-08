# Installing 15Slide
## Downloading a build
If you are not up to building 15Slide from scratch, [you can grab a release](https://github.com/JZJisawesome/15Slide/releases). Choose one with `linux32` for Linux, or `win32` for windows. Then [run 15Slide](https://jzjisawesome.github.io/15Slide/Running-15Slide).

## Building
Note: these steps may be changed when GTKSlide is merged (gtkmm libraries will have to be used)

### Linux
1. [Download](https://github.com/JZJisawesome/15Slide/archive/master.zip) or clone (https://github.com/JZJisawesome/15Slide.git) the 15Slide source files
2. Get the termcolor library from [http://termcolor.readthedocs.io/](http://termcolor.readthedocs.io/)
3. Go to where you downloaded the master branch, and copy the _include_ folder from the termcolor master into it
4. Open a terminal in the 15Slide master branch and run `autoreconf --install` to create the proper build enviornment
5. Run the infamous `./configure; make`
6. [Run the 15Slide executable](https://jzjisawesome.github.io/15Slide/Running-15Slide) which is now in the current directory

#### For Windows (minGW cross-platform, non GTKSlide)
1. Follow steps _one_ to _three_ in the Linux build instructions
2. Comment out `compiler=g++` in build.sh and uncomment `#compiler=i686-w64-mingw32-g++`. You may need to specify a different compiler or install one depending on your setup
3. Open a terminal in the 15Slide master branch and run `sh ./build.sh`
4. The compiled 15Slide is in the new bin folder, but you may need to add the libgcc_s_sjlj-1.dll and libstdc++-6.dll libraries or something similar to the directory

### Windows (to do)
### macOS (to do)
