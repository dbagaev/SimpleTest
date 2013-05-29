file(GLOB  ALL_SOURCE *.cpp *.h)

file(GLOB QT_UI_FILES *.ui)
file(GLOB QT_CPP_SOURCE MainWindow.h)

qt4_wrap_cpp(QT_MOC_SOURCES ${QT_CPP_SOURCE})
qt4_wrap_ui(QT_MOC_UI ${QT_UI_FILES})

source_group([qt_moc] FILES ${QT_MOC_SOURCES} ${QT_MOC_UI})
source_group(ui FILES ${QT_UI_FILES})

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_BINARY_DIR}/runner)

add_executable(TestUI ${ALL_SOURCE} ${QT_MOC_UI} ${QT_MOC_SOURCES} ${QT_UI_FILES})
target_link_libraries(TestUI ${QT_LIBRARIES})
target_link_libraries(TestUI SimpleTest++)