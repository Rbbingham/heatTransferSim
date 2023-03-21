include(CTest)

# create executable target
add_executable(Test basic_tests.cpp)

# include headers and source
target_include_directories(Test PUBLIC ../include)
target_link_libraries(Test gtest_main utils)

# add tests
add_test(NAME Test
         COMMAND $<TARGET_FILE:Test>
)