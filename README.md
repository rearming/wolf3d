# wolf3d
Recoding simple version of Wolfenstein 3D (42 project wolf3d)

### Build - run make and wait a few minutes while external libraries compiling:
```
make
```
### Run:
```
./wolf3d wolf_config.wolf
```
### or
```
./wolf wolf_config.wolf maps/map*
```

### Usage:
![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/controls.png)

One of the features of this wolf3d is self-written terminal, through which you can control the game and do some crazy things:
### 360 degrees fov...
![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/fov360.png)
### Change color channels order from default RGB...
![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/changed_channels.png)
### Even change textures from Wolfenstein originals to Minecraft (command: "render all minecraft")!
![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/minecraft.png)
**You can also place and break blocks with pickaxe =)**
### Change all blocks: (set all [number of block]: "set all 50" -> all diamonds!)
![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/diamonds.png)
### There is dynamic minimap with cool animated Wolf3d guy on it!
![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/wolf3d_1.png)
### Terminal commands:

**render all [minecraft/wolf]** - change textures type

**render all [compass/index]** - render textures by index or by compass side

**set all [number of block/]** - change all blocks

**set all default** - set default block textures

**set block [number of block/default]** - change block in front of player

**change channels [order]** - "change channels gbr" - change order of color channels

**player fov [degrees]** - change player's field of view

**player look (un)freeze** - freeze/unfreeze up and down mouse look

![Image alt](https://github.com/rearming/wolf3d/raw/master/screenshots/wolf3d_2.png)

### Hope you enjoy! :)
