cmake_minimum_required(VERSION 3.14)
project(FT_PING LANGUAGES C)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_compile_options(-fsanitize=address -g)
add_link_options(-fsanitize=address -g)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(libft)
