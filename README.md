<div align=center>
<pre>
    __________  ___   _______________    __    _________   __________ 
   / ____/ __ \/   | / ____/_  __/   |  / /   /  _/__  /  / ____/ __ \
  / /_  / /_/ / /| |/ /     / / / /| | / /    / /   / /  / __/ / /_/ /
 / __/ / _, _/ ___ / /___  / / / ___ |/ /____/ /   / /__/ /___/ _, _/ 
/_/   /_/ |_/_/  |_\____/ /_/ /_/  |_/_____/___/  /____/_____/_/ |_|  
--------------------------------------------------------------------------
Coming Soon...
</pre>

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
</div>

## Overview ##
A WIP Ray Marcher to create cool and interesting fractals! Created utilizing C++, CUDA, and the GLM Library. You can view my work on the basic version of this tool, which relies purely on the CPU, in the `main` branch. Meanwhile, you can view the GPU-accelerated version in the `cuda` branch.

## Setup ##
Clone this repository utilizing `git clone`. Then, in `main.cpp`, add objects here:
```cpp
std::vector<std::shared_ptr<Hittable>> scene = {
    // std::make_shared<ObjType>()
    // Objects go here. Refer to hittable.h for object names and constructors. 
};
```
Then, create an instance of the `Camera` object, passing its position, focal length, and if you want to use anti-aliasing. For example, this defines a `Camera` located at (0,0,0), with a focal length of 2.0, and anti-aliasing turned ON when rendering the scene.
```cpp
Camera cam(vec3(0,0,0), 2.0, true);
```
Finally, write the following to render the scene:
```cpp
cam.renderImage(scene);
cam.outputImage();
```

To execute, run the following in your terminal (at the root directory of the cloned repository on your machine):
```
mkdir build
cd build 
cmake make ..
cmake --build .
./Fractalizer > output.ppm
```
