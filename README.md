<a name="readme-top"></a>


![Contributors][contributors-shield]
![stage][stage-shield]
![Stargazers][stars-shield]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a>
    <img src="https://raw.githubusercontent.com/SixLeopard/README-Templates/main/RayTracer/raytracingtitle.png" alt="Logo" width="312" height="211">
  </a>

<h3 align="center">Ray Tracer</h3>

  <p align="center">
    Simple 3D CPU ray tracer
    <br />
    <a href="https://github.com/SixLeopard/AQileo/wiki"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/SixLeopard/AQileo/releases">View Releases</a>
    ·
    <a href="https://github.com/SixLeopard/AQileo/issues">Report Bug</a>
    ·
    <a href="https://github.com/SixLeopard/AQileo/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#Build">Build</a></li>
      </ul>
    </li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

My implementation of <a href="https://raytracing.github.io/books/RayTracingInOneWeekend.html">Ray Tracing in One Weekend</a> built using C++ and RayLIb.
Very barebones but was only created to learn about how ray tracing works <br><br>

<h4>Background</h4>
<p>Since the beginning of computer graphics there has been a constant push to create more and
more realistic graphics however the magnum opus of computer graphics Ray Tracing hasn't
been a viable option for general consumers until recent years due to how computationally
demanding it is. With a large amount of today's focus being squarely on real time ray tracing
which can allow for games, scientific visualizations, architectural mockups and mechanical
simulations to look more realistic while still being able to be interacted with in real time without
having to use traditional rasterization with copious post processing effects to create a realistic
image</p>

<h4>Aim</h4>
The aim was to create a ray tracer that can achieve realistic lighting on a simple scene

<h5>Features required that i would consider to be minimum for realistic lighting</h5>
  * Soft shadows<br>
  * Directional lights (the sun)<br>
  * Indirect lighting (multiple ray bounces)<br>
  * Indirect shadows (multiple ray bounces)<br>
  * Diffuse reflections<br>
  * Ambient occlusion (should just come as a result of indirect shadows)<br>
  * Sky box reflections<br>
  * Ambient light<br>
  * Depth of Field<br>

<h4>Current Features:</h4>
- Soft shadows <br>
- Directional lights (the sun)<br>
- Indirect lighting (multiple ray bounces)<br>
- Indirect shadows (multiple ray bounces)<br>
- Diffuse reflections<br>
- Ambient occlusion (should just come as a result of indirect shadows)<br>
- Sky box reflections<br>
- Ambient light<br>
- Depth of Field<br>

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![NET-badge][NET-badge]][NET]
* [![Monogame-badge][Monogame-badge]][Monogame]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Getting setup to work on AQileo

### Prerequisites

Required to build project
* CMake
  https://cmake.org/
* C/C++ compiler

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/SixLeopard/AQileo.git
   ```

### Build

1. Generate Build files
   ```sh
   cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -Bbuild
   ```
2. Build Ray Tracer
    ```sh
   cmake --build build 
   ```
3. Run
    ```sh
   linux/Macos:
     ./bin/RayTracer
    Windows:
      start /bin/RayTracer.exe
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

See the [open issues](https://github.com/SixLeopard/AQileo/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [https://raytracing.github.io/books/RayTracingInOneWeekend.html]()
* [https://github.com/othneildrew/Best-README-Template]()


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/badge/Constributors-1%20-blue?style=for-the-badge
[stage-shield]: https://img.shields.io/badge/Developement%20Stage-Complete%20-red?style=for-the-badge
[stars-shield]: https://img.shields.io/badge/C%2B%2B-CMake-green?style=for-the-badge
[NET]: https://cmake.org/
[Monogame]: https://www.raylib.com/
[NET-badge]: https://img.shields.io/badge/C%2B%2B-CMake-blue?style=for-the-badge
[Monogame-badge]: https://img.shields.io/badge/C%2B%2B-RayLib%20-red?style=for-the-badge
