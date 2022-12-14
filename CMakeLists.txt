# CMakeList.txt: The CMake project of BaC, where build process is defined.
cmake_minimum_required (VERSION 3.8)

# Set infomation of the project
project ("BaC" VERSION 0.3.0 LANGUAGES CXX)
set (PROJECT_BUILDER "Zou Boyu")
set (PROJECT_RELEASE_TYPE "preview")

# Require C++ 11 standard
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate configuration header file based on configure.in.h
configure_file ("configure.in.h" "configure.h")

# Add source code to this project's executable
add_executable (BaC "main.cpp" "configure.in.h" "bac.h" "bac.cpp" "advget.h" 
"program.h" "program.cpp")

# Set include directories
target_include_directories (${PROJECT_NAME}
	PRIVATE
		"${CMAKE_CURRENT_BINARY_DIR}"
)

# Configure installation directory
install(TARGETS BaC
	RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/LICENSE.txt" 
	DESTINATION "${CMAKE_INSTALL_PREFIX}"
)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/doc"
	DESTINATION "${CMAKE_INSTALL_PREFIX}/doc"
)
