file(GLOB  ALL_SOURCE *.cpp *.h)

add_library(Tests SHARED ${ALL_SOURCE})

target_link_libraries(Tests SimpleTest++)

