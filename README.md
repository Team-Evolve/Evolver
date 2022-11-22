# Evolver
Evolver Rendering Library

Using OpenGL 4.6 Compatibility, C++20, Visual Studio 2022

## Updates
### TODO
- [ ] Add Visual Test with compute shader
- [ ] Create Math library and test with Catch2
- [ ] Create Texture base class and TextureManager class
- [ ] Create Transform class
- [ ] Buffer class is written but has to be looked anyway.
### DONE
- [x] Create Timer class
- [x] Add time limit for every object (? Is it effect performance if no is it necessary to this)
- [x] Added Object base class and changed ShapeFactory to ObjectManager and Model inherits from Object
- [x] Added GUI class
- [x] Added include functionality for shaders
- [x] Added Model class
- [x] Added Shader Cache
- [x] Look for classes to change LOG_INFO, LOG_ERROR and use File class for file operations
- [x] Added File class
- [x] Added Mesh class
- [x] Added XMLManager class (using pugixml)
- [x] Added Path and File classes
- [x] Shader class is completed.
- [x] Texture class is completed.
- [x] Camera class is completed.
- [x] Window class is completed.
### NEED TO RESEARCH
- [ ] Model cache is too slow. => Last thought : obj is compressed file I don't need to cache other values (I think). Going to search for it anyway.