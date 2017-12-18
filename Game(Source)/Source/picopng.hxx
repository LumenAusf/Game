#pragma once

#include <vector>

/*
decodePNG: The picoPNG function, decodes a PNG file buffer in memory, into a raw
pixel buffer.
out_image: output parameter, this will contain the raw pixels after decoding.
  By default the output is 32-bit RGBA color.
  The std::vector is automatically resized to the correct size.
image_width: output_parameter, this will contain the width of the image in
pixels.
image_height: output_parameter, this will contain the height of the image in
pixels.
in_png: pointer to the buffer of the PNG file in memory. To get it from a file
on
  disk, load it and store it in a memory buffer yourself first.
in_size: size of the input PNG file in bytes.
convert_to_rgba32: optional parameter, true by default.
  Set to true to get the output in RGBA 32-bit (8 bit per channel) color format
  no matter what color type the original PNG image had. This gives predictable,
  useable data from any random input PNG.
  Set to false to do no color conversion at all. The result then has the same
data
  type as the PNG image, which can range from 1 bit to 64 bits per pixel.
  Information about the color type or palette colors are not provided. You need
  to know this information yourself to be able to use the data so this only
  works for trusted PNG files. Use LodePNG instead of picoPNG if you need this
information.
return: 0 if success, not 0 if some error occured.
*/
int decodePNG (std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png,
               size_t in_size, bool convert_to_rgba32 = true);

// an example using the PNG loading function:

#include <fstream>
#include <iostream>

void loadFile (std::vector<unsigned char>& buffer, const std::string& filename)    // designed for loading files from
                                                                                   // hard disk in an std::vector
    ;

/*
int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "test.png";

  //load and decode
  std::vector<unsigned char> buffer, image;
  loadFile(buffer, filename);
  unsigned long w, h;
  int error = decodePNG(image, w, h, buffer.empty() ? 0 : &buffer[0], (unsigned
long)buffer.size());

  //if there's an error, display it
  if(error != 0) std::cout << "error: " << error << std::endl;

  //the pixels are now in the vector "image", use it as texture, draw it, ...

  if(image.size() > 4) std::cout << "width: " << w << " height: " << h << "
first pixel: " << std::hex << int(image[0]) << int(image[1]) << int(image[2]) <<
int(image[3]) << std::endl;
}
*/

/*
  //this is test code, it displays the pixels of a 1 bit PNG. To use it, set the
  flag convert_to_rgba32 to false and load a 1-bit PNG image with a small size
  (so that its ASCII representation can fit in a console window)
  for(int y = 0; y < h; y++)
  {
    for(int x = 0; x < w; x++)
    {
      int i = y * h + x;
      std::cout << (((image[i/8] >> (7-i%8)) & 1) ? '.' : '#');
    }
    std::cout << std::endl;
  }
*/
