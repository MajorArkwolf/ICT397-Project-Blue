# Project-Blue-Engine
<p align=center>
  <b> Project Blue </b>
</p>
<p align="center">
  <a href="#building">Building</a> •
  <a href="#contributing">Contributing</a> •
  <a href="#license">License</a>
</p>

## Basic Info
This is a new iteration of Project Red Engine and is a proof of concept. Design decisions were made knowing full well that we only had 4 months to develop it. Certain best practices were ignored in some situations due to deadlines and we were aware of this short comings. 

## Building
### Tools
* macOS: [xcode][xcode command line tool][brew][brew-dl]
* Windows: [vcpkg][vcpkg-dl], [Visual Studio 2019][VS2019-dl]

### Dependencies
* Linux: `sudo apt-get install cmake libsdl2-dev libsdl2-image-dev
    libsdl2-ttf-dev libsdl2-mixer-dev libglm-dev assimp-utils`
* macOS: `brew install cmake ninja llvm --with-toolchain`
* Windows: `None` 

### GIT LFS
Ensure you have GIT LFS installed.
```
git lfs install
```

### Cloning
```
git clone https://github.com/MajorArkwolf/ICT397-Project-Blue.git
cd ICT397-Project-Blue
git checkout develop 
git submodule update --init --recursive --depth 1
```

### Building
#### Linux:
```
cmake -S . -B build && cmake --build build && ./build/project-blue
```

#### macOS:
Replace X with compiler built types for example 'debug', 'release' or 'RelWithDebInfo'
```
CXX=/usr/local/opt/llvm/bin/clang++ cmake -S . -B build/X -G Ninja -D CMAKE_BUILD_TYPE=X
```
Change directory to whatever you specified X as.
```
ninja && ./Project-Blue
```

#### Windows:
    * Open Visual Studio as Administrator (required to make symbolic links)
    * In Visual Studio, select Open → CMake, select `CMakeLists.txt`
    * From the "Select Startup Item" menu, select `Project-Blue.exe`

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
This project is licensed under the MIT license. Please see the [LICENSE](LICENSE) file
for details.
