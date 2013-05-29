cmake_minimum_required(VERSION 2.8)
project(SimpleTest)

find_package(Qt4 4.4.3 REQUIRED QtCore QtGui QtXml)
include(${QT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(SimpleTest++)

add_subdirectory(runner)
add_subdirectory(tests)

