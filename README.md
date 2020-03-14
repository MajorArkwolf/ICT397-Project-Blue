# ICT397-Project-Blue
<p align=center>
  <b> ICT397 Project Blue </b>
</p>
<p align="center">
  <a href="#building">Building</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>


## Building
### Tools
* macOS: [brew][brew-dl]
* Windows: [vcpkg][vcpkg-dl], [Visual Studio 2019][VS2019-dl]

### Dependencies
* NOTE: `Linux and Mac dependences out of date`
* Linux: `sudo apt-get install cmake libsdl2-dev libsdl2-image-dev
    libsdl2-ttf-dev libsdl2-mixer-dev libglm-dev assimp-utils`
* Windows: `.\vcpkg.exe install --triplet x64-windows sdl2 sdl2-image sdl2-ttf
    sdl2-mixer glm assimp glad`

### GIT LFS
Ensure you have GIT LFS installed.
```
git lfs install
```

### Cloning
```
git clone --recurse-submodules https://github.com/MajorArkwolf/ICT397-Project-Blue.git
git checkout develop && git submodule update --init --recursive --depth 1
```

### Building
* Unix:
    ```
    cmake -S . -B build && cmake --build build && ./build/project-blue
    ```
* Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * In Visual Studio, select Open → CMake, select `CMakeLists.txt`
    * From the "Select Startup Item" menu, select `shays-world.exe`

## Contributing
* Ensure your editor uses Unix line endings
    * Use the [Line Endings Unifier][leu-dl]
      plugin for Visual Studio
    * Here's the [suggested configuration][leu-config]
* Use **clang-format** to format your source code to the project standard
    * Install a clang-format extension to your text editor:
        * [vim][clang-format-vim]
        * [Atom][clang-format-atom]
        * [Visual Studio][clang-format-vs]
        * [Visual Studio Code][clang-format-vsc]

## License
This project is licensed under the MIT license. Please see the [`LICENSE](LICENSE) file
for details.
