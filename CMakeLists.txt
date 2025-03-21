cmake_minimum_required(VERSION 3.10)
project(UbuntuImageFetcher)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(UbuntuFetcher main.cpp UbuntuImageFetcher.cpp)
target_link_libraries(UbuntuFetcher CURL::libcurl nlohmann_json::nlohmann_json)
