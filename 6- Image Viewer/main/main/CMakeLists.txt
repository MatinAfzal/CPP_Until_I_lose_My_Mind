# CMakeList.txt : CMake project for main, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (main "main.cpp" "main.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(main ${OpenCV_LIBS} )

# TODO: Add tests and install targets if needed.
