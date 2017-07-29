#
# Lua bindings for libllvm
#
cmake_minimum_required(VERSION 2.8)

project(lua-llvm C)

set(BUILD_SHARED_LIBS TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(INSTALL_CMOD share/lua/cmod CACHE PATH "Directory to install Lua binary modules (configure lua via LUA_CPATH)")

set(COMMON_CFLAGS "${CFLAGS}")
set(COMMON_LDFLAGS)
set(COMMON_LIBS)

message(STATUS "System Name: ${CMAKE_SYSTEM_NAME}")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	list(APPEND CMAKE_PREFIX_PATH /usr/local)
endif()

if(NOT ${LUA_INCLUDE_DIR})
	## Find Lua 5
	include(FindLua)
	if(NOT ${LUA_FOUND})
		message(FATAL_ERROR "The FindLua module could not find lua :-(")
	endif()
	set(COMMON_LIBS "${COMMON_LIBS};${LUA_LIBRARIES}")
endif()

## LibLlvm
include(FindPkgConfig)
find_package(LLVM 4.0 REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(LLVM_LIBRARIES support core irreader bitwriter nativecodegen)
message(STATUS "LLVM_LIBRARIES: ${LLVM_LIBRARIES}")
# We probably shouldn't staticly link llvm
set(COMMON_LIBS "${COMMON_LIBS};${LLVM_LIBRARIES}")

## LuaNativeObjects
include(LuaNativeObjects)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${LUA_INCLUDE_DIR})

## LuaLlvm
set(LUA_LLVM_SRC
	llvm.nobj.lua
)

if(${USE_PRE_GENERATED_BINDINGS})
	set(LUA_LLVM_SRC src/pre_generated-llvm.nobj.c)
else()
	# Generate Lua bindings.
	GenLuaNativeObjects(LUA_LLVM_SRC)
endif()

add_library(lua-llvm MODULE ${LUA_LLVM_SRC})
target_link_libraries(lua-llvm ${COMMON_LIBS})
set_target_properties(lua-llvm PROPERTIES PREFIX "")
set_target_properties(lua-llvm PROPERTIES COMPILE_FLAGS "${COMMON_CFLAGS}")
set_target_properties(lua-llvm PROPERTIES OUTPUT_NAME llvm)
# Not sure this is correct
target_link_libraries(lua-llvm gcc stdc++)

install(TARGETS lua-llvm
        DESTINATION "${INSTALL_CMOD}")

