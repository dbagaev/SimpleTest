file(GLOB  ALL_SOURCE *.cpp *.h)

if(MSVC)
  file(GLOB  WIN_SOURCE Win32/*.cpp Win32/*.h)
else()
  file(GLOB POSIX_SOURCE Posix/*.cpp Posix/*.h)
endif(MSVC)

source_group(ui FILES ${QT_UI_FILES})

add_library(SimpleTest++ ${ALL_SOURCE} ${POSIX_SOURCE} ${WIN_SOURCE})
