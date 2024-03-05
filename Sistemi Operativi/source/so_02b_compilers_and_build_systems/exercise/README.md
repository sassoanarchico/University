# Exercise Prerequisites
### rp_01_compilers_and_build_systems

## Installing GCC on Ubuntu (Compiler)

The default Ubuntu repositories contain a meta-package named  `build-essential`  that contains the GCC compiler and a lot of libraries and other utilities required for compiling software.

Perform the steps below to install the GCC Compiler Ubuntu 18.04/20.04:

1.  Start by updating the packages list:
    
    ```
    sudo apt update
    ```
    
2.  Install the  `build-essential`  package by typing:
    
    ```
    sudo apt install build-essential
    ```
    
    The command installs a bunch of new packages including  `gcc`,  `g++`  and  `make`.
    
    You may also want to install the manual pages about using GNU/Linux for development:
    
    ```
    sudo apt-get install manpages-dev
    ```
    
3.  To validate that the GCC compiler is successfully installed, use the  `gcc --version`  command which prints the GCC version:
    
    ```
    gcc --version
    ```
    
    The default version of GCC available in the Ubuntu 18.04 repositories is  `7.4.0`:
    
    ```output
    gcc (Ubuntu 7.4.0-1ubuntu1~18.04) 7.4.0
    Copyright (C) 2017 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    ```
	  The default version of GCC available in the Ubuntu 20.04 repositories is  `9.3.0`:
	```output 
	gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
	Copyright (C) 2019 Free Software Foundation, Inc.
	This is free software; see the source for copying conditions.  There is NO
	warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	```

## Installing Eigen

Eigen is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms. We will explain better this when we will use the library. At the moment is enough to install it. On Ubuntu 18.04/20.04 execute the following command on the terminal:
```
sudo apt install libeigen3-dev
```
Check that package has been installed correctly using `pkg-config`:
```
pkg-config --list-all | grep eigen
```

## Hint - Debugging with CMakeLists
Often, especially for very large projects and builds you have errors :)  hence it is very helpful having a way of debugging. With CMakeLists you can print a message by typing (in the `CMakeLists.txt`):  
```
message("my variable value:"  ${SOME_VARS})
```
or you can actually write if-statement to redirect the user to human readable errors
```
if(NOT SOME_VARS)
message(FATAL_ERROR "This variable is not set!")
endif()
```

Here the FLAG `FATAL_ERROR` will exit the compilation! Please refer to the [docs](https://cmake.org/cmake/help/latest/command/message.html) for more info and flags! 

### Now you are ready to write your (first maybe) nested CMakeLists :)

## Exercise - building and running

Once you have completed the exercise, open a terminal and in the root folder of your project `<YOUR_PATH>/mini_core/`, where you have the following file and folders:
```
executables
src
CMakeLists.txt
```
create a folder called `build` and go into it, so type in the terminal:
```
mkdir build && cd build
```
after you can configure your project and create your `Makefile` necessary to build your package. This is done using `cmake`. The `cmake` executable is the CMake command-line interface. It may be used to configure projects in scripts. Project configuration settings may be specified on the command line with the -D option (for more info check [this out](https://cmake.org/cmake/help/v3.2/manual/cmake.1.html)).

CMake is a cross-platform build system generator. Projects specify their build process with platform-independent CMake listfiles included in each directory of a source tree with the name CMakeLists.txt. Users build a project by using CMake to generate a build system for a native tool on their platform.

Now that you know a little of `cmake` you are ready to build your package, always in the same terminal (make sure you are inside the `build` folder) type:
```
make
```
by default this will build with just a single core. Since your machine usually has more, you can speed up the compilation by typing the number of core you want to use for compilation (check this out by typing in a terminal `nproc`), for instance:
```
make -j4
```
Once you build and no error message are popped out you can finally run your executable. This will be placed inside `<YOUR_PATH>/mini_core/build/executables/`. Therefore go inside the following folder by typing:
```
cd <YOUR_PATH>/mini_core/build/executables/
```
And run the only executable that you have in the folder (check the name out using the `ls` command, the executable will be highlighted in green for you :))

In my case the name is `many_object_in_stack_example`, therefore you can run this by typing:
```
./many_object_in_stack_example
```
You should see a stupid ASCII-Art and not error or `Segmentation Fault` appearing in the terminal. If this is the case, you have completed the homework successfully and you know now how to build a C++ package.

 
