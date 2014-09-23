include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../inc)
include_directories(${CMAKE_SOURCE_DIR}/inc)
add_definitions(--std=c++11)
test_module (matrix matrix)
test_module (matrix matrix_threevec)
test_module (matrix matrix_colvec)
test_module (matrix matrix_matrix)

add_custom_target(matrix-test-all
    DEPENDS
        test_matrix
        test_matrix_threevec
        test_matrix_colvec
        test_matrix_matrix
    )
