include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
include_directories(${CMAKE_SOURCE_DIR}/inc)
add_definitions(--std=c++11)
test_module (simple col)
test_module (simple mat)
test_module (simple row)
test_module (simple quat)

add_custom_target(simple-test-all
    DEPENDS
        test_col
        test_mat
        test_row
	test_quat
    )
