add_library(peering NeighborTable.cpp Peering.cpp)

target_link_libraries(peering control)
