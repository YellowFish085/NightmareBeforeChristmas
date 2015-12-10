include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_library(projet ${SRC_FILES})
