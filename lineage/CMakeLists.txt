add_library(lineage_core
 lineage.cpp
 utility.cpp)

target_include_directories(lineage_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})