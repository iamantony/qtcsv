cmake_minimum_required(VERSION 3.1)

project (qtcsv_tests)

if(USE_QT4)
	find_package(Qt4 REQUIRED)
	set(QT_TEST_TARGET Qt4::QtTest)
else()
	find_package(Qt5Test REQUIRED)
	set(QT_TEST_TARGET Qt5::Test)
endif(USE_QT4)


#define names
set(BINARY_NAME ${PROJECT_NAME})

#Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#add also the header part to source files. this is necessary for correct automoc
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${BINARY_NAME} ${SOURCE_FILES} )

if(SHARED_LIB)
  TARGET_LINK_LIBRARIES(${BINARY_NAME} PRIVATE ${QT_TEST_TARGET} qtcsv)
else()
  TARGET_LINK_LIBRARIES(${BINARY_NAME} PRIVATE ${QT_TEST_TARGET} qtcsv_static)
endif(SHARED_LIB)

#provide current project dir for projects header search path
target_include_directories(${BINARY_NAME} PRIVATE .)

#copy test files after build
add_custom_command(TARGET ${BINARY_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

#run tests after build; they assume to be runned from top level bin-dir
# add_custom_command(TARGET ${BINARY_NAME} POST_BUILD WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND ./tests/${BINARY_NAME})

#install the test environment
install(TARGETS ${BINARY_NAME}
        RUNTIME DESTINATION bin/tests)
install(DIRECTORY data DESTINATION bin/tests/)
