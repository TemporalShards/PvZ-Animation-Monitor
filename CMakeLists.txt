cmake_minimum_required(VERSION 3.0)

project("PvZ-Animation-Monitor")

set(CMAKE_CXX_STANDARD 20)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories(./inc)
aux_source_directory(./src src)
add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/utf-8")

add_definitions(-DWIN32_LEAN_AND_MEAN)