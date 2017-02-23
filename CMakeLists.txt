cmake_minimum_required (VERSION 2.8)

project (qtcsv)

# define names
set(LIB_MAJOR_VERSION 1)
set(LIB_MINOR_VERSION 3)
set(LIB_REVISION_VERSION 1)
set(LIB_VERSION ${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_REVISION_VERSION})
set(LIBRARY_NAME ${PROJECT_NAME})

# set options
option(STATIC_LIB "build as static lib if ON, otherwise build shared lib" OFF)
option(USE_QT4 "builds against Qt4 if ON, otherwise builds against Qt5" OFF)
option(BUILD_TESTS "build tests" ON)

# find qt package
if(USE_QT4)
    find_package(Qt4 REQUIRED)
    set(QT_CORE_TARGET Qt4::QtGui)
else()
    # if cmake failed to find Qt5Core configuration file, set path manually:
    set(Qt5Core_DIR "/opt/Qt/5.5/gcc_64/lib/cmake/Qt5Core/")

    find_package(Qt5Core REQUIRED)
    set(QT_CORE_TARGET Qt5::Core)
endif(USE_QT4)

# instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# set compiler flags and build type
if (WIN32)
    set(CMAKE_CXX_FLAGS "")
else()
    set(CMAKE_CXX_FLAGS "-fPIC -Wall -Werror -Wformat=2 -Wuninitialized \
        -Winit-self -Wmissing-include-dirs -Wswitch-enum -Wundef \
        -Wpointer-arith -Wdisabled-optimization -Wcast-align -Wcast-qual")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" QTCSV_BUILD_TYPE)
if(QTCSV_BUILD_TYPE MATCHES release OR QTCSV_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS}")
elseif(QTCSV_BUILD_TYPE MATCHES debug)
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS "-g ${CMAKE_CXX_FLAGS}")
else()
  message(FATAL_ERROR "Build " ${CMAKE_BUILD_TYPE} " is not supported!")
endif()

# set list of source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)

if(STATIC_LIB)
    set(LIBRARY_NAME_STATIC ${LIBRARY_NAME}_static)
    add_library(${LIBRARY_NAME_STATIC} STATIC ${SOURCE_FILES})
    # include root project folder as private, because the source headers are included with source/*.h
    target_include_directories(${LIBRARY_NAME_STATIC}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE .)

    # set static lib name to the same of shared lib
    set_target_properties(${LIBRARY_NAME_STATIC}
        PROPERTIES OUTPUT_NAME ${LIBRARY_NAME})

    TARGET_LINK_LIBRARIES(${LIBRARY_NAME_STATIC} PRIVATE ${QT_CORE_TARGET})
else()
    set(LIBRARY_NAME_SHARED ${LIBRARY_NAME})
    add_library(${LIBRARY_NAME_SHARED} SHARED ${SOURCE_FILES})
    # include root project folder as private, because the source headers are included with source/*.h
    target_include_directories(${LIBRARY_NAME_SHARED}
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE .)

    set_target_properties(${LIBRARY_NAME_SHARED} PROPERTIES
        VERSION ${LIB_VERSION}
        SOVERSION ${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION})

    TARGET_LINK_LIBRARIES(${LIBRARY_NAME_SHARED} PRIVATE ${QT_CORE_TARGET})
endif(STATIC_LIB)

install(TARGETS ${LIBRARY_NAME_SHARED} ${LIBRARY_NAME_STATIC} EXPORT ${LIBRARY_NAME}Config
        LIBRARY DESTINATION lib
                ARCHIVE DESTINATION lib)

install(DIRECTORY include DESTINATION .)

# create and install cmake package files
install(EXPORT ${LIBRARY_NAME}Config DESTINATION share/${LIBRARY_NAME}/cmake)
export(TARGETS ${LIBRARY_NAME_SHARED} ${LIBRARY_NAME_STATIC} FILE ${LIBRARY_NAME}Config.cmake)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)
