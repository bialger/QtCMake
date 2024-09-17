# QtCMake
A C++ project template with Qt6 and CMake that downloads and compiles Qt.
The resulting app is an executable that can be run on a system without Qt.

The main Qt6 configuration is found in the [correspondent](lib/qt/CMakeLists.txt) CMakeLists.txt file.

> Note that statically compiled Qt6 weights more than 5 GB.
> The good thing is that user does not need whole compiled Qt6 with this configuration.

## Prerequisites

* CMake
* Ninja
* Git

On Linux: `libgl1-mesa-dev libglu1-mesa-dev` and all dependencies are required.
> Note that most of the libraries that match `*xcb*` and `*xkb*` may be required on Linux.

## How to build and run

Run the following commands from the project directory.

1. Create CMake cache

This step may take a lot of time because it downloads and compiles Qt.

```shell
cmake -S . -B cmake-build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
```

2. Build executable target

```shell
cmake --build cmake-build --target QtCMake
```

3. Run executable target

* On Windows:

```shell
.\cmake-build\bin\QtCMake.exe
```

* On *nix:

```shell
./cmake-build/bin/QtCMake
```
