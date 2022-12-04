set(NAME ping_utils)
add_library(${NAME} STATIC
	parse_args.c
	result.c
	util.c
)

target_compile_options(${NAME} PRIVATE -Wall -Wextra -Werror)
target_compile_options(${NAME} PRIVATE -Wno-unused -Wno-unused-parameter)
target_include_directories(${NAME} PUBLIC ../include)
target_link_libraries(${NAME} PUBLIC ft)
