#cmake_minimum_required(VERSION 3.5)

#find_package(GTest REQUIRED)

#if(${GTest_FOUND})
#    message("gtest found successfully")
#endif()

#add_executable(SolutionFuctionality SolutionFuctionality.cpp)

#target_include_directories(SolutionFuctionality PRIVATE
#                ${GTEST_INCLUDE_DIRS})
#target_include_directories(SolutionFuctionality PRIVATE
#    ${SOLUTION_LIBRARY_INCLUDE_DIRECTORY})
#target_link_libraries(SolutionFuctionality solution)
#target_link_libraries(SolutionFuctionality GTest::gtest GTest::gtest_main)

#add_test(NAME solution COMMAND $<TARGET_FILE:SolutionFuctionality>)



