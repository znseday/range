cmake_minimum_required(VERSION 3.12)

if(WIN32 OR WIN64)
	message(STATUS "My Windows detected")
	project(range VERSION 0.0.1000)
	set(BOOST_ROOT "C:/Boost")
else()
	project(range VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
endif()

# There is something wrong here
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(range main.cpp)

add_executable(my_tests my_test.cpp)

if(WIN32 OR WIN64)
	add_library(my_aux my_aux.cpp my_aux.h)
else()
	add_library(my_aux my_aux.cpp)
endif()

if(WIN32 OR WIN64)
	set_target_properties(range my_aux my_tests PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		# COMPILE_OPTIONS doesn't work that way. VS will say that they are ignored !!! 
		COMPILE_OPTIONS "/std:c++17 /permissive- /experimental:preprocessor")
else()
	set_target_properties(range my_aux my_tests PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
endif()

# Added this cos "set_target_properties" doesn't work with two INCLUDE_DIRECTORIES (((
target_include_directories(my_tests
   PUBLIC "${Boost_INCLUDE_DIR}"
   PRIVATE "${CMAKE_MODULE_PATH}/include"
)

set_target_properties(my_tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
   # INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(range
	my_aux
	${CONAN_LIBS}
#    Threads::Threads
)

target_link_libraries(my_tests
    ${Boost_LIBRARIES}
    my_aux
#   ${CONAN_LIBS}
)

install(TARGETS range RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT znseday@yandex.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()


if(WIN32 OR WIN64)
	add_test(my_tests_ my_tests)
else()
	add_test(my_tests_ bin/my_tests)
endif()
