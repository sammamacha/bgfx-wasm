Toy example of using bgfx with wasm and passing data into the wasm module via. javascript for personal use. 

Compile with emscripten in PATH:
```
mkdir build && cd build
emcmake cmake ..
cmake --build . 
```
I have not added shaders for multiple platforms, you can place them in `3rdparty` and then run `shader_compile.sh`

TODO: 
- Fix CMakeLists.txt 
- Document compiling steps for future reference
- Fix main having no consistent style and comment 
