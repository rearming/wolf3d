mkdir SDL2_libs
cd SDL2_libs
git clone https://github.com/spurious/SDL-mirror.git SDL2
cd SDL2
DIR=`pwd`
./configure --prefix=$DIR
make && make install
cd ..
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  sudo apt install libfreetype6 libfreetype6-dev
  sudo apt install libpng16-16 libpng-dev
  sudo apt-get install automake
fi
endif
git clone https://github.com/Ecognize/SDL_ttf.git
cd SDL_ttf
touch aclocal.m4 Makefile.am configure Makefile.in
export SDL_CONFIG=$DIR/sdl2-config
DIR=`pwd`
./configure --prefix=$DIR
make && make install
cd ../..