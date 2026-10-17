# OpenGL Multi-Scene 3D Experience

A small explorable 3D world written in C++ and modern OpenGL. You start inside a **bedroom** that contains a **portal**: walk up to it, press `SPACE`, and you are transported to **outer space**, where the planets of the solar system rotate around you. Press `SPACE` again to go back to the room.

Every scene (camera, materials, shaders, textures, 3D models, transforms and portal triggers) is described in an **XML configuration file**, so new scenes can be added without touching the C++ code.

Project by **Chiara Frascaria**, **Arianna Martinelli** and **Letizia Penne'** (Tor Vergata University of Rome), 2022.

the .obj files aren't present inthe repository at the moment, but the XML file can be configured with any new scene.

equirements: **Windows**, **Visual Studio 2019 or later** (C++ desktop workload), a GPU with OpenGL 3.3+.

External libraries (install them and add their include/lib folders to the project properties):

- GLFW — window and input
- glad — OpenGL loader
- Assimp — model loading (`assimp-vc142-mtd.lib`, `zlibstaticd.lib`)
- rapidxml  — XML parsing
- stb_image — image loading

## Features

- Scene loading from `config.xml` (window, background, scenes, cameras, materials, objects, transforms, triggers)
- Scene switching through **trigger objects** (the portal) and a target `nextScene`
- 3D model loading (`.obj`) with **Assimp**
- Texture loading with **stb_image**, including cube maps for the skybox
- Many GLSL shaders: Lambert lighting, normal mapping, textured materials, planets, moon, the animated portal sprite, light sources and the cube map
- Free-moving camera with rotation around the scene center
- Hand-written linear algebra library (`Vec2f`, `Vec3f`, `Vec4f`, `Mat3f`, `Mat4f`, `Quat`)
