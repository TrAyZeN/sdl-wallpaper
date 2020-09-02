<h1 align="center">
    sdl-wallpaper
</h1>

> Example code to put an SDL window as the wallpaper on Windows

This code shows how to create an SDL window and put it as wallpaper.
It has been done with an SDL window to easily draw inside it as an example,
but the same code can be used with just any window when you have its handle.

## Requirements
- [CMake](https://cmake.org/download/)
- [SDL2](https://www.libsdl.org/download-2.0.php)

## Build
*Below **path/to/SDL2/include** corresponds to the directory containing the
**SDL2/** folder containing all the headers and **path/to/SDL2/libs**
corresponds to the directory containing **SDL2.lib**.*
```
git clone https://github.com/TrAyZeN/sdl-wallpaper.git
cd sdl-wallpaper
cmake . -DSDL2_INCLUDE_DIR:FILEPATH=path/to/SDL2/include -DSDL2_LIBRARY:FILEPATH=path/to/SDL2/libs
```
This should generate solution file, just open it with Visual Studio and build sdl-wallpaper.

## Contributing
Contribution are welcomed

## License
MIT TrAyZeN
