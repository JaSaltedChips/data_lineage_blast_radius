add_executable(main main.cpp)
target_link_libraries(main PRIVATE lineage_core)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/src")
