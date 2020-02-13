# Compiling

The following are instructions for Debian based systems to compile and build
the code for this project.

## Requirements

    sudo apt-get install \
      cmake              \
      g++                \
      gcc                \
      git                \
      libx11-dev         \
      libglu1-mesa-dev

## Build

    make

## Clean

    make clean

## Run

For testing that the code is compiled and is working correctly:

    ./pt-draw-test
