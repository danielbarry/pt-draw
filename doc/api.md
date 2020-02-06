# API

Here we define the available API functions.

## `void create_bitmap(char* desc, unsigned int len, char* buff, unsigned int size)`

**Description:** This method is used for creating a binary bitmap from the
scalable vector image description.

* @param **desc** - A pointer to the description array of the object to be
created as a sequence of bytes (see [file format](file-format.md)).
* @param **len** - The length of the description sequence.
* @param **buff** - A pointer to the binary buffer to be set. The buffer must
have adequate space for storing the resulting data.
* @param **size** - The size of the width and height (`size = width = height`).
The number of pixels in total is `size x size`, total number of bytes is
`(size x size) / 8` rounded up to the nearest byte.
