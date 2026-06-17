cmake_minimum_required(VERSION 3.15.7)

project(lovc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif() # CMAKE_BUILD_TYPE

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} 
	${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/perf_kw_hash.c)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	target_compile_options(${PROJECT_NAME} PRIVATE
		-fmacro-prefix-map=${CMAKE_CURRENT_SOURCE_DIR}=)
endif()
