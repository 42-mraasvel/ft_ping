set(NAME ft_ping)

add_executable(${NAME}
	main.c
)

target_compile_options(${NAME} PRIVATE -Wall -Wextra -Werror)
target_compile_options(${NAME} PRIVATE -Wno-unused -Wno-unused-parameter)
target_link_libraries(${NAME} PRIVATE ping_utils)
