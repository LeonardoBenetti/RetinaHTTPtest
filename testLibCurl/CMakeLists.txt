cmake_minimum_required (VERSION 2.8)
project (TestLibCurl)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable (tstlibcurl ${SOURCES})

find_package (CURL REQUIRED)


target_link_libraries(tstlibcurl ${CURL_LIBRARIES})