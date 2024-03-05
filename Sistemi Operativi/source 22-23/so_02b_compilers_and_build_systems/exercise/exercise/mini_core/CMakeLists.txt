cmake_minimum_required(VERSION 2.8.3)
project(mini_core)

# signature_of_eigen3_matrix_library is just there as a signature to help identify directories containing Eigen3. 
# when writing a script looking for Eigen3, just look for this file. This is especially useful to help disambiguate with Eigen2...

# this is used to find a directory containing the named file and to store the result inside the variable EIGEN3_INCLUDE_DIR 
find_path(EIGEN3_INCLUDE_DIR signature_of_eigen3_matrix_library
  /usr/include/eigen3
  /usr/local/include/eigen3
)

# check if variable is populated previously
if( NOT EIGEN3_INCLUDE_DIR )
     message( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation!")
endif()


# TODO invokes the routines to find a package called Eigen3

# TODO specify additional locations of header files

# add project source code
add_subdirectory(src)
# TODO do the same for executables