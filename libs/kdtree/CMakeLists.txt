add_library(KDTreeLib STATIC 
    src/sorted_kdtree.cpp
)

# Define where the header files are
target_include_directories(KDTreeLib PUBLIC include)


