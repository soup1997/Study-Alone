cmake_minimum_required(VERSION 3.0.0)

# create project
project(pcl_tutorial VERSION 0.1.0)
add_executable(pcl_tutorial main.cpp)

# find packages
find_package(PCL 1.10 REQUIRED)


if(PCL_FOUND)
  # [C/C++]>[General]>[Additional Include Directories]
  include_directories( ${PCL_INCLUDE_DIRS} )

  # [C/C++]>[Preprocessor]>[Preprocessor Definitions]
  add_definitions( ${PCL_DEFINITIONS} )

  # For Use Not PreCompiled Features 
  #add_definitions( -DPCL_NO_PRECOMPILE )

  # [Linker]>[General]>[Additional Library Directories]
  link_directories( ${PCL_LIBRARY_DIRS} )

  # [Linker]>[Input]>[Additional Dependencies]
  target_link_libraries( pcl_tutorial ${PCL_LIBRARIES} )
endif()
