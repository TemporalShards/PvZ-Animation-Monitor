cmake_minimum_required(VERSION 3.15)

project("PvZ-Animation-Monitor" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(wxWidgets_CONFIGURATION mswud)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(wxWidgets_CONFIGURATION mswu)
endif()

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

aux_source_directory(src srcs)

if(MSVC)
    add_executable(${PROJECT_NAME} ${srcs})
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/utf-8")
else()
    add_link_options(
        -Wall
        -O3
    )
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    configure_file(manifest.xml ${CMAKE_CURRENT_BINARY_DIR}/manifest.xml COPYONLY)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/app.rc "1 24 \"${CMAKE_CURRENT_BINARY_DIR}/manifest.xml\"")
    add_executable(${PROJECT_NAME} ${srcs} ${CMAKE_CURRENT_BINARY_DIR}/app.rc)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-mwindows"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/inc"
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${wxWidgets_LIBRARIES}
)

add_definitions(-DWIN32_LEAN_AND_MEAN)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin" CACHE PATH "输出目录")