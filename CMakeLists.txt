cmake_minimum_required(VERSION 3.14)
project(wolf3d C)

set(CMAKE_C_STANDARD 11)

set(libft_includes
        libft/includes)

set(ft_printf_includes
        libft/ft_printf/includes)

set(sdl_includes
		SDL2_libs/SDL2/include/
		SDL2_libs/SDL_ttf/include/)

if(!OSX)
	set(freetype_includes
			/usr/include/freetype2
			/usr/include/libpng16
	)
	set(freetype_lib
			freetype)
endif()

include_directories(includes
		${sdl_includes}
        ${Includes}
        ${libft_includes}
        ${ft_printf_includes}
		${freetype_includes}
        )

link_directories(
        libft/
        libft/ft_printf/
		SDL2_libs/SDL2/lib/
		SDL2_libs/SDL_ttf/lib/
)

set(main
		sources/wolf3d.c
		)

set(init
		sources/init/init.c
		sources/init/parse_params.c)

set(utils
		sources/utils/error.c
		sources/utils/exit.c
		)

set(SDL_utils
		sources/SDL_utils/sdl_loop.c
		sources/SDL_utils/sdl_clean.c
		)

set(render
		sources/render/render.c
		sources/render/render_utils.c
		sources/render/bresenham.c
		sources/render/minimap.c
		sources/render/texture_render_utils.c
		sources/game_logic/game_logic_utils.c
        sources/render/items.c)
set(game_logic
		sources/game_logic/parse_items.c)
set(hooks
		sources/hooks/key_hook.c
		sources/hooks/mouse_hook.c
		sources/hooks/player_moves.c
		sources/game_logic/player_actions.c)
set(parsing
		sources/parsing/image_parser.c
		sources/parsing/map_parser.c
		sources/parsing/fast_gnl.c
		sources/parsing/texture_parser.c
		sources/parsing/parsing_utils.c)
set(terminal
		sources/terminal/init_terminal.c
		sources/terminal/terminal_render.c
		sources/terminal/term_command_parser.c
		sources/terminal/term_processing.c)

add_executable(wolf3d

        ${main}
		${init}
		${utils}
		${SDL_utils}
		${render}
		${hooks}
		${parsing}
		${debug}
		${game_logic}
		${terminal}
        )


target_link_libraries(wolf3d

		"SDL2"
		"m"
        "ftprintf"
		"ft"
		"SDL2_ttf"
		${freetype_lib}

)



