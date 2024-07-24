cmake_minimum_required(VERSION 3.8)

project(test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(bgfx REQUIRED)

if (DEFINED EMSCRIPTEN)
  file(GLOB src "*.h" "*.cpp")
	add_executable(main ${src})
	
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set_property(TARGET main PROPERTY CXX_STANDARD 17)
	set_target_properties(main PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1")
  set_target_properties(main PROPERTIES LINK_FLAGS    "-Os -s ASSERTIONS -s WASM=1 -s USE_WEBGL2 --shell-file ${CMAKE_SOURCE_DIR}/webpage/shell.html -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH --embed-file ./shaders/v_simple.bin --embed-file ./shaders/f_simple.bin -s IMPORTED_MEMORY -s INITIAL_MEMORY=32mb -s SAFE_HEAP=1 -lembind -sNO_DISABLE_EXCEPTION_CATCHING" )
  target_include_directories(main PRIVATE bgfx)
	target_include_directories(main PRIVATE glm)
  target_include_directories(main PRIVATE json/include)
  target_link_libraries(main bgfx::bx bgfx::bgfx)
else()
	add_library(main SHARED main.cpp)
endif()
