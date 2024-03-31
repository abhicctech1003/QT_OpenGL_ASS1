# Project: QT_OpenGL_Window

## Overview

This project opearates using triangulation of data from STL files and render the object in 3D spacw using OpenGL window. The key components of the project are as follows:

- **Source Files**: 
  - `point3D.cpp`
  - `triangle.cpp`
  - `triangulation.cpp`
  - `reader.cpp`

- **Header Files**: 
  - Located in the `headers` folder, containing declarations for all respective source files.

- **Functionality**:
  - `Reader.cpp` reads data from STL files, extracting coordinates and storing them as vectors using triangulation .
  - Triangulation algorithms are implemented in `Triangulation.cpp`.
  - `main.cpp` utilizes the triangulated data, creating vertices arrays for rendering 3D object using OpenGL.
  
-  **Input**:
   - When prompted, provide the path to the input STL file.

-  **Visualization**:
   - The program will visualize the triangulated coordinates using OpenGL rendering.

   


