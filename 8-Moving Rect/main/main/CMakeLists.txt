# CMakeList.txt : CMake project for main, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (main "main.cpp" "main.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

set(SFML_DIR "E:/CPP_LIBS/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
target_link_libraries(main sfml-system sfml-window sfml-graphics)
# TODO: Add tests and install targets if needed.