## Space Game NX
This is a port of [Space Game](https://github.com/vgmoose/space) to the Nintendo Switch.

The game is currently fully playable, but there's no music, enemy count is limited to compared to the Wii U version, and some Switch-specific features are planned.

For a more simple SDL2 switch example, you can see [sdl-hello-world](https://github.com/vgmoose/sdl-hello-world).

### Compiling
#### For Switch
A `spacenx.nro` file will be produced, which can be used on the switch through hbmenu. It can be compiled using libtransistor or libnx.

#### Using libtransistor
Clone and setup libtransistor, for more detail [see this post](https://reswitchedweekly.github.io/Development-Setup/). Then run the following command:

```
make -f Makefile.switch
```

Notice: currently libtransistor builds are crashing on 5.x. The latest release uses libnx for now.

#### Using libnx
Setup libnx and devkitarm64 [using the installer](http://switchbrew.org/index.php?title=Setting_up_Development_Environment). At the time of writing, this code uses devkitA64 r10-2. Then run the following command:

```
make -f Makefile.libnx
```

#### For PC
This version of Space Game is ported to sdl2, so the same code can be compiled on the computer as well. Running `make -f Makefile.pc` creates a binary file that can be executed on the computer using the sdl2 library is required to compile it. It also plays using gamepad controls, so the keyboard won't work to control it.

`make -f Makefile.pc` creates a binary file using the sdl1 library instead.

### License
This program is licensed under [the MIT license](https://opensource.org/licenses/MIT), see the original repo for more information.
