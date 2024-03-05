cmake_minimum_required(VERSION 2.8.3) # version of cmake
project(mini_core) # name of the project

# signature_of_eigen3_matrix_library is just there as a signature to help identify directories containing Eigen3. 
# when writing a script looking for Eigen3, just look for this file. This is especially useful to help disambiguate with Eigen2...

# this is used to find a directory containing the named file and to store the result inside the variable EIGEN3_INCLUDE_DIR
# you may not need this depending on the version of eigen3.x that you have
# this is usually stored inside a file called FindEigen3.cmake, either you include this in the project folder or you insert these lines in this CMakeLists.txt 
find_path(EIGEN3_INCLUDE_DIR signature_of_eigen3_matrix_library
  /usr/include/eigen3
  /usr/local/include/eigen3
)

# check if variable is populated previously
if( NOT EIGEN3_INCLUDE_DIR )
     message( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation!")
endif()


# this invokes the routines to find a package called Eigen3
find_package(Eigen3 REQUIRED)


# specify additional locations of header files
include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/src
)

# add project source code, handle project with nested folder
add_subdirectory(src)
add_subdirectory(executables)