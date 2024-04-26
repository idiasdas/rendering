# rendering

In this repository, I practice the basics of rendering with a focus on OpenGL.

I'm following the [OpenGL tutorial](http://www.opengl-tutorial.org/), however, I am managing dependencies and project compilation myself.

# Dependencies

For Linux, install the following:

```bash
$ sudo apt install cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev
```

The rest of the dependencies are managed automatically with CMake.

# Quick Start

Clone this repository:

```bash
git clone https://github.com/idiasdas/rendering
```

Initialize its submodules:

```bash
git submodule update --init
```

Configure CMake:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

Build the project:

```bash
cd build
make
```
Finally, you can run the executable `rendering` which should show:

```bash
rendering/build$ ./rendering
GLFW initialized
GLEW version: 2.2.0
GLM working
```

# External Software

Currently using:

- [glfw](https://github.com/glfw/glfw)
- [glew](https://github.com/nigels-com/glew)
- [glm](https://github.com/g-truc/glm)

All external software can be found in `rendering/ext/`.

# Progress

- [x] Tutorial 01
- [x] Tutorial 02
- [x] Tutorial 03
- [x] Tutorial 04

>[!NOTE]
>I have modified LoadShaders to handle relative paths between the source file and the shaders' files.
>Therefore, you are now free to choose whichever build directory you would like.
