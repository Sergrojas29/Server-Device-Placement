cmake_minimum_required(VERSION 3.15)
project(CrowProject)

# [FIX 1] Downgrade to C++20 for compatibility with VS 2019 on laptop
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- 1. Fetch Asio ---
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG        asio-1-30-2
)
FetchContent_MakeAvailable(asio)

# Update Path: The git repo has an extra 'asio' folder
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

# --- 2. Fetch Crow ---
FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(Crow)

# --- 3. Add Your Library ---
add_subdirectory(libs/kdtree)

# --- 4. Compile Server ---
add_executable(server src/main.cpp)

# [FIX 3] Force the Include Directory
# Crow sometimes struggles to find Asio if it's not system-installed.
# We manually tell the server where to look.
target_include_directories(server PRIVATE ${ASIO_INCLUDE_DIR})

# --- 5. Link ---
# Make sure "kdtree_lib" matches the name inside libs/kdtree/CMakeLists.txt
target_link_libraries(server PRIVATE Crow::Crow KDTreeLib)