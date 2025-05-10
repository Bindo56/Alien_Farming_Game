Simulation Programming in C++ with SDL
 This week, I implemented an AI-based animal simulation system using C++ and SDL! 🐾
 Each animal in the game world can idle, rotate, and move dynamically based on probabilistic behavior and spatial checks. The system features:
 ✅ Idle, moving, and rotating states
 ✅ Smooth texture transitions for growing animals
 ✅ Collision avoidance with environment and other entities
 ✅ Randomized behavior logic using timers and angle calculations
 ✅ Custom rendering offsets for shadows and growth stages


🌿 Simulating Dynamic Environments with Tile-Based Logic | C++ / SDL
In this project, I created a system where ground tiles automatically update their state (wet or dry) based on nearby water tiles using a simple radius-based check. This lets the environment react dynamically to changes—or water placement—without manual updates.
Plant types respond to this system:
Some can only grow on wet dirt
Trees grow only on grass tiles

https://github.com/user-attachments/assets/de1cb642-0922-4072-a0e4-50b376dddcb7


Growth happens over time, with smooth animations and size transitions
Each plant tracks its own growth using timers, and the visuals shift from a seedling to a mature plant depending on its age. 

The core idea was to not only render a grid of tiles, but also dynamically cast shadows based on surrounding tiles — similar to how elevation or depth is handled in pixel-art games.
🧱 Key Features:
Dynamic tile-based grid rendering
Smart shadow placement using a 3x3 neighbor-check system
Corner-aware shadow logic (only draws corner shadows when appropriate)
Efficient C++ data structures for real-time rendering
💡 This helped me learn a lot about:
Texture loading and rendering with SDL2
Coordinate systems and offset mapping
Optimizing shadow logic based on tile neighbors
🎯 The end result is a clean system that automatically adapts shadows based on tile height and surroundings!
