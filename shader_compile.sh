#!/bin/bash 

mkdir -p build/shaders 

./third-party/shaderc/shaderc -f shader/v_simple.sc -o build/shaders/v_simple.bin --platform asm.js --profile 100_es --type vertex --verbose -i ./

./third-party/shaderc/shaderc -f shader/f_simple.sc -o build/shaders/f_simple.bin --platform asm.js --profile 100_es --type fragment --verbose -i ./
