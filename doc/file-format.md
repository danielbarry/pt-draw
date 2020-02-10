# File Format

**Filename:** It is recommended that the filename has the extension `pt4`, i.e.
`cool-image.pt4`. (The "4" suggests the points are encoded in four bits). This
should reduce confusion with future versions.

**Encoding:** Everything is encoded as 4 bit nibbles and the presentation of
values are also unsigned integers of 4 bits. The largest represented value is
15 and the smallest is 0.

**Draw area:** The draw width and height is 16 (a square), where the highest
precision is one unit. This means that graphics are ultimately represented in a
grid-like format.

**Reccomendation:** For images that are intended to be drawn small, it is
recommended that they are designed with this in mind. For example, if your icon
is to be displayed in a 4x4 window, design the icon in this resolution and
upscale it to fill the draw window.

## Shape Selector Byte

The shape selector byte tells the reader which type of shape is being drawn.

|Bit|Description                                                |
|---|-----------------------------------------------------------|
|7  |0: Simple line sequence                                    |
|   |1: Curved line sequence                                    |
|6  |0: No fill                                                 |
|   |1: Fill (assumes connected sequence)                       |
|5-4|Reserved                                                   |
|0-3|Number of lines in the sequence, 16 maximum (starts from 1)|

## Simple Line Sequence

A simple line sequence consists of (2 + NUM_LINES) bytes, the following example
is for NUM_LINES = 2, no fill:

|Offset|Description                     |
|------|--------------------------------|
|0     |Shape selector, bits: [10000001]|
|1     |(x1,y1)                         |
|2     |(x2,y2)                         |
|3     |(x3,y3)                         |

## Curve Line Sequence

A curved line sequence consists of (2 + (2 x NUM_LINES)) bytes, the following
example is for NUM_LINES = 3, with fill:

|Offset|Description                     |
|------|--------------------------------|
|0     |Shape selector, bits: [11000010]|
|1     |(x1,y1)                         |
|2     |(cx1,cy1) Centre of 1st curve   |
|3     |(x2,y2)                         |
|4     |(cx2,cy2) Centre of 2nd curve   |
|5     |(x3,y3)                         |
