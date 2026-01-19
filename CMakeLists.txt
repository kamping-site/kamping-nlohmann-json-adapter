cmake_minimum_required(VERSION 3.23)
project(
  kamping-spdlog-adapter
  DESCRIPTION "Adapter for briding KaMPIng's timers with nlohmann_json"
  LANGUAGES CXX
  VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
  kamping
  GIT_REPOSITORY https://github.com/kamping-site/kamping
  GIT_TAG v0.2.1
  GIT_SHALLOW ON
  SYSTEM)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json
  GIT_TAG v3.12.0
  GIT_SHALLOW ON
  SYSTEM)

add_library(kamping-nlohmann-json-adapter INTERFACE)

target_sources(
  kamping-nlohmann-json-adapter
  INTERFACE FILE_SET HEADERS BASE_DIRS src FILES
            src/kamping/nlohmann_json_adapter/printer.hpp)

target_link_libraries(kamping-nlohmann-json-adapter
                      INTERFACE kamping::kamping nlohmann_json::nlohmann_json)
add_library(kamping::nlohmann-json-adapter ALIAS kamping-nlohmann-json-adapter)
