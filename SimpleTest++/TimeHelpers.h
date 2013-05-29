#include "Config.h"

#if defined SIMPLETEST_POSIX
    #include "Posix/TimeHelpers.h"
#else
    #include "Win32/TimeHelpers.h"
#endif
