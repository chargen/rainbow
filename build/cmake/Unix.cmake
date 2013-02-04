if(UNIX)
	set(RAINBOW_COMMON_CFLAGS "-fno-rtti -fno-exceptions")
	if(MINGW)
		set(RAINBOW_CSTD   "-std=gnu99")
		set(RAINBOW_CXXSTD "-std=gnu++11")
	else()
		set(RAINBOW_CSTD   "-std=c99")
		set(RAINBOW_CXXSTD "-std=c++11")
		if(NOT APPLE)
			# Common C-/C++ compiler flags
			set(RAINBOW_COMMON_CFLAGS "${RAINBOW_COMMON_CFLAGS} -fstack-protector -fpie -march=native")
		endif()

		# Compiler warning flags
		set(RAINBOW_CXX_WARNINGS "-Werror -pedantic -Wall -Wextra -Wno-invalid-offsetof -Wold-style-cast -Woverloaded-virtual -Wsign-promo")
	endif()

	# Set CFLAGS and CXXFLAGS
	set(CMAKE_C_FLAGS   "-pipe ${RAINBOW_CSTD} -w ${RAINBOW_COMMON_CFLAGS}")
	set(CMAKE_CXX_FLAGS "-pipe ${RAINBOW_CXXSTD} ${RAINBOW_CXX_WARNINGS} ${RAINBOW_COMMON_CFLAGS}")

	if(NOT APPLE)
		if(CMAKE_CXX_COMPILER MATCHES "clang")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
		endif()

		# Set LDFLAGS
		if(NOT MINGW)
			set(CMAKE_EXE_LINKER_FLAGS "-pie -Wl,-z,now -Wl,-z,relro")
			if(CMAKE_CXX_COMPILER MATCHES "clang")
				set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthreads")
			endif()
		endif()

		# Debug- and release-specific flags
		set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0 -ftrapv")
		set(CMAKE_CXX_FLAGS_RELEASE "-O2 -D_FORTIFY_SOURCE=2 -finline-functions")

		if(NOT MINGW)
			set(PLATFORM_LIBRARIES m rt stdc++)
		endif()
	endif()
endif()
