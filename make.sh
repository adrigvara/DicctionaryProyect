#!/bin/bash
g++ proyect.cpp -lGL -lGLU -lglut -lm -o dictionary
./dictionary
if [ls | grep .gch | wc -l > 0]; then
  ls | grep .gch | xargs trash 
fi
