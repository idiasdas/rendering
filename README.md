# rendering

In this repository, I practice the basics of rendering, with a focus on OpenGL.

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
$ git clone https://github.com/idiasdas/rendering
```

Initialize its submodules:

```bash
$ git submodule update --init
```

Configure CMake:

```bash
$ cmake -B build -DCMAKE_BUILD_TYPE=Debug
```
Build the project:

```bash
$ cd build
$ make
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

>[!NOTE]
>I have changed the LoadShaders() function so it only needs the shaders relative path to the executable's source.
>Therefore, you can now use whichever build directory you want, as long as you run the executables from this directory.
