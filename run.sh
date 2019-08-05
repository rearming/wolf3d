#!/bin/zsh

PROJECT_DIR=$(pwd)

SDL_DIR="$PROJECT_DIR"/SDL2_libs

SDL2="$SDL_DIR"/SDL2

TTF_DIR="$SDL_DIR"/sdl_ttf

FREETYPE_DIR="$SDL_DIR"/freetype-2.4.9

echo "$PROJECT_DIR"
echo "$SDL_DIR"
echo "$SDL2"
echo "$TTF_DIR"
echo "$FREETYPE_DIR"

if [[ ! -d "$SDL_DIR" ]]; then
	mkdir "$SDL_DIR"
fi

#
# install SDL2 basic library
#

install_SDL2()
{
	echo "installing SDL2 core libs"
	git clone https://github.com/spurious/SDL-mirror.git "$SDL2" || return
	cd "$SDL2"
	if [[ ! -f "Makefile" ]]; then
		./configure --prefix="$SDL2"
		make && make install
	fi
	echo "PATH=\$PATH:$SDL2" >> ~/.zshrc
}

if [[ ! -d "$SDL2" ]]; then
	install_SDL2
else
	echo "SDL2 is already installed!"
fi

# install freetype2 and authomake

install_freetype()
{
	cd "$SDL_DIR"
	if [[ "$OSTYPE" == "linux-gnu" ]]; then
 		sudo apt install libfreetype6 libfreetype6-dev
 		sudo apt-get install automake
	else
		if [[ ! -d FREETYPE_DIR ]]; then
			tar -xf "$PROJECT_DIR"/freetype-2.4.9.tar.bz2 -C "$SDL_DIR"
		else
			echo "freetype is already unpacked"
			return
		fi
		echo "installing freetype"
		cd "$FREETYPE_DIR"
		sed -i -r 's:.*(#.*SUBPIXEL.*) \(.*\):\1:' \
			include/freetype/config/ftoption.h &&
		./configure --prefix="$FREETYPE_DIR"
		echo "PATH=\$PATH:$FREETYPE_DIR/builds/unix/" >> ~/.zshrc
		make && make install
		chmod 755 "$FREETYPE_DIR"/freetype-config
	fi
}

if [[ ! -d "$FREETYPE_DIR" ]]; then
	install_freetype
fi

# install SDL_ttf

install_sdl_ttf()
{
	cd "$SDL_DIR"

	git clone https://github.com/Ecognize/SDL_ttf.git

	cd "$TTF_DIR"

	# upgrade timestamps for authoconfig
	touch aclocal.m4 Makefile.am configure Makefile.in

#	export PATH=\$PATH:"$FREETYPE_DIR"/builds/unix/
	export SDL_CONFIG="$SDL2"/sdl2-config
	if [[ ! -f "Makefile" ]]; then
		./configure --prefix="$TTF_DIR" --with-freetype-prefix="$FREETYPE_DIR"
		make && make install
	fi
	echo "PATH=\$PATH:$TTF_DIR" >> ~/.zshrc
}

if [[ ! -d "$TTF_DIR" ]]; then
	install_sdl_ttf
else
	echo "SDL_ttf already installed!"
fi
