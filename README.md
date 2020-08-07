## Space Game NX [![Build status](https://api.travis-ci.org/vgmoose/space-nx.svg?branch=master)](https://travis-ci.org/vgmoose/space-nx)
This is a port of [Space Game](https://github.com/vgmoose/space) to the Nintendo Switch.

The game is currently fully playable, but there's no music, enemy count is limited to compared to the Wii U version, and some Switch-specific features are planned.

### Compiling
#### For Switch
A `spacenx.nro` file will be produced, which can be used on the switch through hbmenu. It can be compiled using libnx.

Setup libnx and devkitA64 [using the installer](http://switchbrew.org/index.php?title=Setting_up_Development_Environment). Then run the following command:

```
make -f Makefile.switch
```

#### For PC
This version of Space Game is ported to sdl2, so the same code can be compiled on the computer as well. Running `make -f Makefile.pc` creates a binary file that can be executed on the computer using the sdl2 library is required to compile it. It also plays using gamepad controls, so the keyboard won't work to control it.

### License
This program is licensed under [the MIT license](https://opensource.org/licenses/MIT), see the original repo for more information.
