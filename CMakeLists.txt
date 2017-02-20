cmake_minimum_required (VERSION 3.1)

project (qtcsv)

#add additional targets enabling sanitizer on demand
option(SHARED_LIB "build as shared lib" ON) # ON is the default
option(BUILD_AND_RUN_TESTS "build and run tests" ON) # ON is the default

#find the Qt packages, delivered by conan
find_package(Qt5Core REQUIRED)

#define names
set(LIBRARY_NAME ${PROJECT_NAME})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)

if(SHARED_LIB)
	add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES})
else()
	add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
endif(SHARED_LIB)
set_target_properties(${LIBRARY_NAME} PROPERTIES VERSION 1.3.1 SOVERSION 1.3)

#include root project folder as private, because the source headers are included with source/*.h
target_include_directories(${LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE .)

TARGET_LINK_LIBRARIES(${LIBRARY_NAME} PRIVATE Qt5::Core)

install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_NAME}Config
        LIBRARY DESTINATION lib
				ARCHIVE DESTINATION lib)
install(DIRECTORY include DESTINATION .)

#create and install cmake package files
install(EXPORT ${LIBRARY_NAME}Config DESTINATION share/${LIBRARY_NAME}/cmake)
export(TARGETS ${LIBRARY_NAME} FILE ${LIBRARY_NAME}Config.cmake)

if(BUILD_AND_RUN_TESTS)
	add_subdirectory(tests)
endif(BUILD_AND_RUN_TESTS)
