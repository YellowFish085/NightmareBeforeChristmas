set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

## Compilation de gtest
find_package(Threads REQUIRED)
set(GTEST_DIR gtest)
include_directories(SYSTEM ${GTEST_DIR}/include)
include_directories(${GTEST_DIR})
add_library(gtest ${GTEST_DIR}/src/gtest-all.cc) # gtest - librairie
add_library(gtest_main ${GTEST_DIR}/src/gtest_main.cc) # gtest - 'main'

file(GLOB HEADER_FILES *.hpp)
file(GLOB SRC_FILES *.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(FILE ${SRC_FILE} NAME_WE)
    get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(OUTPUT ${DIR}_${FILE})
    add_executable(${OUTPUT} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES})
    target_link_libraries(${OUTPUT} ${ALL_LIBRARIES} gtest gtest_main)
endforeach()

## Compilation des tests
# executable pour lancer les tests
#file(GLOB_RECURSE ALL_TEST_FILES tests/*Test.cpp)
#add_executable(runAllTests ${ALL_TEST_FILES})
#target_link_libraries(runAllTests gtest gtest_main projet)
## Lancement automatique des tests après compilation
#add_custom_command(TARGET runAllTests POST_BUILD COMMAND runAllTests)
