# CMakeList.txt: The CMake project of BaC, where build process is defined.
cmake_minimum_required (VERSION 3.21)

# Set infomation of the project
project ("BaC" VERSION 0.4.0 LANGUAGES CXX)
set (PROJECT_BUILDER "Zou Boyu")
set (PROJECT_RELEASE_TYPE "testing")
if (NOT DEFINED PROJECT_LANGUAGE)
	set (PROJECT_LANGUAGE "zh_CN")
endif()

# Require C++ 11 standard
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure option
if (MSVC)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif ()

# Generate configuration header file based on configure.in.h
configure_file ("configure.in.h" "configure.h")

# Add source code to this project's executable
add_executable (BaC "main.cpp" "configure.in.h" "program.h" "program.cpp" 
"bac.h" "bac.cpp" "advget.h" "translate.h" "translate.cpp")

# Copy translation to the project binary directory
file (COPY_FILE "${PROJECT_SOURCE_DIR}/locale/language-${PROJECT_LANGUAGE}"
	"${PROJECT_BINARY_DIR}/language"
)

# Set include directories
target_include_directories (${PROJECT_NAME}
	PRIVATE
		"${CMAKE_CURRENT_BINARY_DIR}"
)

# Configure installation directory
install (TARGETS BaC
	RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
)
install (FILES "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/LICENSE.txt"
	DESTINATION "${CMAKE_INSTALL_PREFIX}"
)
install (FILES "${CMAKE_BINARY_DIR}/language"
	DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
)
install (DIRECTORY "${CMAKE_SOURCE_DIR}/doc"
	DESTINATION "${CMAKE_INSTALL_PREFIX}"
)
