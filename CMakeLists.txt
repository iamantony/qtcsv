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
    set(QT_CORE_TARGET Qt4::QtCore)
else()
    # if cmake failed to find Qt5Core configuration file, set path manually:
    #list(APPEND CMAKE_PREFIX_PATH "/path/to/Qt/lib/cmake/Qt5Core/")

    find_package(Qt5Core REQUIRED)
    set(QT_CORE_TARGET Qt5::Core)
endif(USE_QT4)

# instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# set compiler flags
if (CMAKE_COMPILER_IS_GNUCXX)
    list(APPEND CMAKE_CXX_FLAGS "-Wall -Werror -Wformat=2 -Wuninitialized \
        -Winit-self -Wmissing-include-dirs -Wswitch-enum -Wundef \
        -Wpointer-arith -Wdisabled-optimization -Wcast-align -Wcast-qual")
endif()

# set list of source files
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)

# for QtCreator: see all files in project
file(GLOB_RECURSE QTCSV_ALL_FILES "*")
add_custom_target(show_all_files_in_${PROJECT_NAME} SOURCES ${QTCSV_ALL_FILES})

if(STATIC_LIB)
    add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES})
else()
    add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES})

    set_target_properties(${LIBRARY_NAME} PROPERTIES
        VERSION ${LIB_VERSION}
        SOVERSION ${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION})
endif(STATIC_LIB)

# include root project folder as private, because the source headers are included with source/*.h
target_include_directories(${LIBRARY_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PRIVATE .)

target_link_libraries(${LIBRARY_NAME} PRIVATE ${QT_CORE_TARGET})

install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_NAME}Config
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY include DESTINATION .)

# create and install cmake package files
install(EXPORT ${LIBRARY_NAME}Config DESTINATION share/${LIBRARY_NAME}/cmake)
export(TARGETS ${LIBRARY_NAME} FILE ${LIBRARY_NAME}Config.cmake)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)
