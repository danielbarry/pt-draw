#!/bin/bash

# Build test program
make clean
make

# Run test program
./pt-draw-test

# Convert the letter files from PPM to PNG
for f in font-*.ppm; do
  file="${f%.*}"
  convert "$f" "doc/$file.png"
done

# Convert the icons files from PPM to PNG
for f in icon-*.ppm; do
  file="${f%.*}"
  convert "$f" "doc/$file.png"
done
