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
A WIP tool to create cool and interesting fractals! Created utilizing C++, the GLM Library, and CUDA.

## Roadblocks & Roadmap ##
- Rendering Scenes: I was able to successfully render a single object by launching a CUDA Kernel where each pixel is processed by a thread. However, when it comes to rendering a scene of objects, I cannot create a vector of `Hittable` shared pointers like the `main` branch of this project (CPU-Based), since CUDA does not support polymorphism, nor features of the standard library such as vectors or smart pointers. Thus, I am looking for a workaround to this issue.
- Anti-Aliasing: Anti-aliasing can pretty easily be implemented by having each thread run through a for loop to perform the random sampling process. However, another idea I had was to utilize "Dynamic Parallelism" to have each thread launch another kernel, with just 1 block of 10 threads. This new kernel can then compute the average of the random sampling process, letting the average be shared memory across the block that each thread can contribute to, being mindful of race conditions. However, implementing this method of anti-aliasing is subject to hardware limitations; the sheer number of kernels being launched and threads would result in the queuing of resources, likely slowing down our program greatly.
- I would like to implement popular optimization techniques, such as Bounding Volume Hierarchies (BVH), Spatial Partioning, and Denoisers.
