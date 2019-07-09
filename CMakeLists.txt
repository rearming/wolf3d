cmake_minimum_required(VERSION 3.14)
project(wolf3d C)

set(CMAKE_C_STANDARD 11)

set(Includes
        includes/colors.h
        includes/errors.h
        includes/fractol.h
		includes/structs.h
		includes/wolf3d.h
		includes/sdb_image.h
        )

set(libft_includes
        libft/includes)

set(ft_printf_includes
        libft/ft_printf/includes)

set(sdl_includes
		./SDL2/include)

include_directories(includes

        ${Includes}
        ${libft_includes}
        ${ft_printf_includes}
		${sdl_includes}
        )

link_directories(

        ./libft/
        ./libft/ft_printf/
		./SDL2/lib/
)

set(main
		sources/wolf3d.c
		)

set(init
		sources/init/init.c
		)

set(debug
		sources/debug/
		sources/debug/debug.c)

set(utils
		sources/utils/error.c
		)

set(SDL_utils
		sources/SDL_utils/sdl_loop.c
		sources/SDL_utils/SDL_clean.c
		)

set(render
		sources/render/render.c
		sources/render/render_utils.c
		sources/render/bresenham.c sources/render/minimap.c)
set(hooks
		sources/hooks/key_hook.c
		sources/utils/exit.c)
set(parsing
		sources/parsing/image_parser.c
		sources/parsing/map_parser.c
		sources/parsing/wolf_gnl.c sources/parsing/texture_parser.c)

add_executable(wolf3d

        ${main}
		${init}
		${utils}
		${SDL_utils}
		${render}
		${hooks}
		${parsing}
		${debug}
        )

target_link_libraries(wolf3d

		"m"
        "ftprintf"
		"ft"
        #"-framework OpenGL"
        "SDL2"
)



