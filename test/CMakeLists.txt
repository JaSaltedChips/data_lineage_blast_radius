add_executable(test test_lineage.cpp)
target_link_libraries(test PRIVATE lineage_core)
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test")