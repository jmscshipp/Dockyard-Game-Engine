# Dockyard-Game-Engine

Fully featured 3D game engine programmed in C++, built on DirextX 11 graphics API (you can poke around that code [here](https://github.com/jmscshipp/DirectX11-Graphics-API))

Notable systems
- GameObjects organized around services that GameObject-derived classes can opt into (Updatable, Drawable, Collidable, Alarmable, Inputable)
- Collisions implemented using command pattern- multiple layers for efficiency with automatically generated colliders (bounding spheres, OBB, AABB)
- Terrains generated at runtime from user-created textures
- Loading and retrieving assets (models, textures, shaders, fonts, terrains)
- Input handling with key press and release callbacks
- Displaying 2D sprites and text with fonts
- Math library with useful 3D math functions for users

In-engine debugging tools
- Collision visualizer
- On-screen text output

Screenshots of engine demo:

![Screenshot 2022-12-13 202918](https://user-images.githubusercontent.com/8291642/207490914-1fd98f8c-eee5-490a-b7da-75ae3f1da5ed.png)
![Screenshot 2022-12-13 203034](https://user-images.githubusercontent.com/8291642/207490919-2223ef8a-b725-48b0-a17a-69279405cd1a.png)

Example of multi-layer collision detection with visualizer:

![Screenshot 2022-12-13 203130](https://user-images.githubusercontent.com/8291642/207490927-c6755550-1602-44ac-b6db-90ca75b8cad6.png)
