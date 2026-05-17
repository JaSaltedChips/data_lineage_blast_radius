add_executable(blast_radius main.cpp)
target_link_libraries(blast_radius PRIVATE lineage_core)
set_target_properties(blast_radius PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/src")
