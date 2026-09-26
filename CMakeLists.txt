cmake_minimum_required(Version 3.28)
project(SFML_setup LANGUAGE CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY){
    ${CMAKE_BINARY_DIR}/bin
}

include(FetchContent)

fetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

fetchContent_MakeAvailable(SFML)

add_executable(sfml_setup 
    main.cpp
)
target_compile_features(sfml_setup PRIVATE cxx_std_20)

target_link_libraries(sfml_setup PRIVATE SFML::Graphics SFML::Audio SFML::NETWORK )
