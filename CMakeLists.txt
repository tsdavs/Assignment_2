# CMakeLists.txt from SILENT HILL 3 Redux by Palm Studios
# Copyright 2016-2018 Alexander Hirsch And Jesse Buhagiar
# Used with Permission

cmake_minimum_required(VERSION 3.1)

project(assignment_2 C)

if(WIN32)
    enable_language(RC)
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
	set(BINARY_RESOURCE_FILE "resource64.rc")
	add_definitions(-DARCH_64)
elseif("${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
	set(BINARY_RESOURCE_FILE "resource32.rc")
else()
	message(SEND_ERROR "Could not detect system bitness.")
endif()

include(CheckCCompilerFlag)

set(ASSERTION_BEHAVIOR_DEFAULT "Log and ask")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR "${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
	set(ASSERTION_BEHAVIOR_DEFAULT "Disable")
endif()
set(ASSERTION_BEHAVIOR "${ASSERTION_BEHAVIOR_DEFAULT}" CACHE STRING "What to do when an assertion fails.")
set_property(CACHE ASSERTION_BEHAVIOR PROPERTY STRINGS "Disable" "Log and abort" "Log and continue" "Log and ask")

if("${ASSERTION_BEHAVIOR}" STREQUAL "Disable")
	add_definitions("-DASSERT_OFF")
elseif("${ASSERTION_BEHAVIOR}" STREQUAL "Log and abort")
	#default, no special defines required
elseif("${ASSERTION_BEHAVIOR}" STREQUAL "Log and continue")
	add_definitions("-DASSERT_CONTINUE")
elseif("${ASSERTION_BEHAVIOR}" STREQUAL "Log and ask")
	add_definitions("-DASSERT_ASK_MSGBOX" "-DASSERT_ASK_STDERR")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if("${CMAKE_C_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
	list(APPEND C_FLAGS
		"-pedantic"
		"-Wall"
		"-Wextra"
		"-Wsign-compare"
		"-Wold-style-cast"
		"-Wdeprecated"
		"-Wsign-conversion"
		"-Wconversion"
		"-Wnon-virtual-dtor"
		"-Wundef"
		"-Wfloat-equal"
		"-Wunreachable-code"
		"-Wswitch-enum"
	)
	string(REPLACE ";" " " C_FLAGS "${C_FLAGS}")
	set(C_FLAGS "${C_FLAGS}" CACHE INTERNAL "Additional compiler flags to use.")
	
	option(C_FORCE_COLOR "Force compiler to use colored output (if available)." ON)
	if(C_FORCE_COLOR)
		set(COLOR_DIAG_FLAGS "fcolor-diagnostics" "fdiagnostics-color=always")
		foreach(COLOR_DIAG_FLAG ${COLOR_DIAG_FLAGS})
			set(TEST_NAME "HAVE_${COLOR_DIAG_FLAG}_FLAG")
			check_c_compiler_flag("-${COLOR_DIAG_FLAG}" ${TEST_NAME})
			if(${TEST_NAME})
				message(STATUS "Forcing colored compiler output")
				set(C_FLAGS "${C_FLAGS} -${COLOR_DIAG_FLAG}")
			endif()
		endforeach()
	endif()
	
	set(BUILD_EXTRA_WARNINGS "Some" CACHE STRING "How many extra warnings to enable.")
	set_property(CACHE BUILD_EXTRA_WARNINGS PROPERTY STRINGS "None" "Some" "Many")
	
	# Some warnings that are of absolutely no interest
	if(NOT ${BUILD_EXTRA_WARNINGS} STREQUAL "Many")
		# These warnings often produce much uninteresting output
		list(APPEND WARN_NOT_FLAGS "padded")
	endif()
	
	if(NOT ${BUILD_EXTRA_WARNINGS} STREQUAL "None")
		set(WARN_EVERYTHING_FLAG "Weverything" CACHE STRING "The flag that enables all warnings.")
		check_C_compiler_flag("-${WARN_EVERYTHING_FLAG}" HAVE_${WARN_EVERYTHING_FLAG}_FLAG)
		if(HAVE_${WARN_EVERYTHING_FLAG}_FLAG)
			set(C_FLAGS "${C_FLAGS} -${WARN_EVERYTHING_FLAG}")
		endif()
	endif()
	
	foreach(WARN_FLAG ${WARN_NOT_FLAGS})
		string(REPLACE "+" "x" TEST_NAME "HAVE_W${WARN_FLAG}_FLAG")
		check_C_compiler_flag("-W${WARN_FLAG}" ${TEST_NAME})
		if(${TEST_NAME})
			message(STATUS "Disabling -W${WARN_FLAG}")
			set(C_FLAGS "${C_FLAGS} -Wno-${WARN_FLAG}")
		endif()
	endforeach()
elseif(MSVC)
	set(C_FLAGS "/W4")
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")
add_subdirectory(source)

if(DOXYGEN_FOUND)
	add_custom_target(doc
		"${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating documentation..."
		VERBATIM
	)
else()
	message(WARNING "Doxygen not found. Target 'doc' not available.")
endif()

