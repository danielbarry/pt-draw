# Algorithms

Here we describe the algorithms used and any specific changes.

## Simple Line

**TODO:** Algorithm for simple line.

## Curved Line

This library implements a
[quadratic Bézier curve](https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Quadratic_B%C3%A9zier_curves)
due to it's simplicity and small number of parameters. The curve is broken into
segments (`NUM_SEGS`) and a series of lines are drawn to produce the curve.
