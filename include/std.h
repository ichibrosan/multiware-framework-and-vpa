////////////////////////////////////////////////////////////////////
// ~/public_html/fw/std.h 2025-07-16 08:08 dwg -                  //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// The purpose of this file is to emulate the functionality if the   //
// "import std;" line which is not yet supported in our devo tools.  //
///////////////////////////////////////////////////////////////////////

// 2024/12/29 05:00 dwg - updated modern includes from C++17 SLQR
// 2024/12/22 07:00 dwg - added stdlib.h for system()

#pragma once

// OLD STYLE SYSTEM INCLUDES (Ad Hoc List)
#include <arpa/inet.h>
//#include <errno.h>        // deprecated by <cerrno>
#include <fcntl.h>
#include <memory.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <pwd.h>
//#include <stdio.h>        // deprecated by <cstdio>
//#include <stdlib.h>       // deprecated by <cstdlib>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
//#include <string.h>         // deprecated by <cstring>
#include <strings.h>
#include <syslog.h>
#include <termio.h>             // added 2025-07-13 for vpalogin
#include <time.h>
#include <unistd.h>
#include <uuid/uuid.h>


/*
 * MODERN STYLE SYSTEM INCLUDES
 * See C++17 Standard Library Quick Reference (2e)
 * Appendix: Standard Library Headers Pages 271-277
 */
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <ccomplex>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <chrono>
#include <cinttypes>
#include <climits>      // added 2025-01-16 10:25 dwg -
#include <clocale>
#include <cmath>
#include <codecvt>
#include <complex>
#include <condition_variable>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cuchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <shared_mutex>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <stack>
#include <system_error>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <stdexcept>
#include <string>
#include <string_view>
//#include <strstream>
#include <thread>
#include <ctime>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>

#define RETURN_SUCCESS EXIT_SUCCESS
#define RETURN_FAILURE EXIT_FAILURE
#define RETURN_SUCCESS_SORT_OF EXIT_SUCCESS
#define RETURN_FAILURE_SORT_OF EXIT_FAILURE

/////////////////
// eof - std.h //
/////////////////
