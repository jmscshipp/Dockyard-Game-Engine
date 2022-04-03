# Dockyard-Game-Engine

Fully featured 3D game engine programmed in C++, built on AZUL framework. Currently in development

Notable systems
- Loading and retrieving assets (models, textures, shaders, fonts, etc)
- GameObjects organized around services from multiple base classes that new GameObject-derived classes can opt into
- Collisions implemented using command pattern (bounding spheres, OBB, AABB)
- Input handling with key press and release callbacks
- Displaying 2D sprites and text with fonts
- Math library with useful functions for users

In-engine debugging tools
- Collision visualizer
- On-screen text output

Screenshots of engine demo:

![Screenshot 2022-04-03 175559](https://user-images.githubusercontent.com/8291642/161453555-d73939f5-39ac-457c-97fc-f377191c25fe.png)
![Screenshot 2022-04-03 175850](https://user-images.githubusercontent.com/8291642/161453556-0bbc9784-653c-4d79-a3c0-cb80cda28eaa.png)

Collision visualization and debug text output example:

![Screenshot 2022-04-03 182433](https://user-images.githubusercontent.com/8291642/161453560-c691e8ef-2fe9-4c98-8a21-123d57d21f7e.png)
