cmake_minimum_required(VERSION 3.15)
project(CrowProject)

# 1. Force C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# 2. Dependencies (Asio & Crow)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG        asio-1-30-2
)
FetchContent_MakeAvailable(asio)
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/include)

FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(Crow)


#add library
add_subdirectory(libs/kdtree)


# --- COMPILE THE SERVER ---
add_executable(server 
    src/main.cpp
    # Note: Header files in src/routes don't strictly need to be listed 
    # if they are included in main.cpp, but it's good practice.
)



# --- LINK EVERYTHING TOGETHER ---
# Link Crow AND your personal MyLib to the server
target_link_libraries(server PRIVATE Crow::Crow KDTreeLib)