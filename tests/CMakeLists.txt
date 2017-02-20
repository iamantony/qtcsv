cmake_minimum_required(VERSION 3.1)

project (qtcsv_tests)

find_package(Qt5Test REQUIRED)

#define names
set(BINARY_NAME ${PROJECT_NAME})

#Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#add also the header part to source files. this is necessary for correct automoc
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${BINARY_NAME} ${SOURCE_FILES} )

TARGET_LINK_LIBRARIES(${BINARY_NAME} PRIVATE Qt5::Test qtcsv)

#provide current project dir for projects header search path
target_include_directories(${BINARY_NAME} PRIVATE .)

#copy test files after build
add_custom_command(TARGET ${BINARY_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

#run tests after build; they assume to be runned from top level bin-dir
add_custom_command(TARGET ${BINARY_NAME} POST_BUILD WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND ./tests/${BINARY_NAME})
