#noisy

`noisy` is a highly-configurable, command-line 2D noise generator, with a 
focus on providing efficient noise generation, many transform options, and 
flexible output formats.

##To-do

* Add proper GNU getopt support
  * `w`, `--width`: get width for output
  * `-h`, `--height`: get height for output
  * `-wh`, `--widthxheight`: get width and height together for output
  * `-o`, `--output`: output name
  * `-f`, `--format`: format for output (should defautl to png)
  * `-i`, `--implementaion`: implementation used for noise generation
* Clean up ugly dsa code

##Compiling

A pre-compiled Windows binary is provided in the 'bin' folder, and a makefile 
is provided as a convenience for compiling on different platforms:

* `make noisy` or simply `make` for Linux-based systems (this is the default)
* `make noisy-mingw` for Windows-based MinGW platforms (Note: On Widnows, [MinGW](https://www.mingw.org) must be installed and the system path must point to your 'MinGW\bin' folder

##License

This program is licensed under the GPLv2. A full copy of this license can be 
found in [license.txt](https://github.com/Torkue/noisy/blob/master/license.txt)

