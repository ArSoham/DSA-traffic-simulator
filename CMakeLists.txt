find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(my_project ${SDL2_LIBRARIES})
