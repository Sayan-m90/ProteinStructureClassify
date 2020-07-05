#!/bin/sh

LIBS="-I/usr/local/include -I/usr/local/include/eigen3 -Igmpq -lCGAL -Igmp -lgmp -lann -lboost_system -lboost_filesystem -lboost_program_options"

g++  -o sibaco-dec --std=c++11  -I./ *.cpp Wrappers/*.cpp SimPers/*.cpp Graphs/*.cpp GIComplex/*.cpp  $LIBS
# 

# g++  -O3 -o sibaco-dec3 --std=c++11  *.cpp Wrappers/*.cpp SimPers/*.cpp Graphs/*.cpp GIComplex/*.cpp  $LIBS
