cmake_minimum_required(VERSION 3.5)

project(L_Script_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

FILE(GLOB_RECURSE LibFiles "include/*.h")
add_custom_target(_L_Script_Test_include SOURCES ${LibFiles})
FILE(GLOB_RECURSE Models "Resources/*")
add_custom_target(L_Script_Test_models SOURCES ${Models})

file(GLOB_RECURSE Sources "source/*.cpp")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DL_DEBUG")
# set(CMAKE_CXX_FLAGS "-DL_DEBUG")

if(MSVC)
    add_compile_options(/bigobj)
endif(MSVC)

add_executable(L_Script_Test ${Sources} Main.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/L_Utility"
                 "${PROJECT_BINARY_DIR}/L_Utility"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/L_Variable"
                 "${PROJECT_BINARY_DIR}/L_Variable"
)
add_subdirectory("${PROJECT_SOURCE_DIR}/L_Script"
                 "${PROJECT_BINARY_DIR}/L_Script"
)

target_include_directories(L_Script_Test PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/L_Utility/include"
                            "${PROJECT_SOURCE_DIR}/L_Variable/include"
                            "${PROJECT_SOURCE_DIR}/L_Script/include"
)


target_link_libraries(L_Script_Test PUBLIC
    L_Variable
    L_Utility
    L_Script
)

# if (WIN32)
#     target_link_libraries(L_Script_Test PUBLIC
#         user32
#         gdi32
#         shell32
#     )
# endif (WIN32)

# if (UNIX)
#     target_link_libraries(L_Script_Test PUBLIC
#         pthread
#         X11
#         dl
#     )
# endif (UNIX)
