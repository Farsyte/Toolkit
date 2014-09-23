include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
include_directories(${CMAKE_SOURCE_DIR}/inc)
add_definitions(--std=c++11)
test_module (testing testing)
test_module (testing testing_log)
test_module (testing testing_suite)
test_module (testing testing_test)

add_custom_target(testing-test-all
    DEPENDS
        test_testing
        test_testing_log
        test_testing_suite
        test_testing_test
    )
