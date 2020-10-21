#!/usr/local/bin/python3
import argparse
import os

from PIL import Image

if __name__ == "__main__":

  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument('--width', default=64, type=int, help='Panel width')
  argument_parser.add_argument('--height', default=32, type=int, help='Panel width')
  argument_parser.add_argument('files', metavar='FILES', nargs='*', help='Files to convert')

  args = argument_parser.parse_args()

  width = args.width
  height = args.height

  for image_file in args.files:

    image = Image.open(image_file)

    if image.size[0] != width or image.size[1] != height:
      print(f"Image {image_file} was {image.size[0]}x{image.size[1]} instead of {width}x{height} - Mode ${image.mode}")

      exit(1)

    pixels = image.load()

    with open(os.path.splitext(image_file)[0] + ".h", "w") as output_file :

      output_file.write(f"#define IMAGE_WIDTH {width}\n")
      output_file.write(f"#define IMAGE_HEIGHT {height}\n")
      output_file.write("\n")

      output_file.write("\n")

      output_file.write(f"uint8_t const IMAGE_DATA[{width}][{height}][3] = {{\n")

      for x in range(0, width):
        output_file.write(f"\t {{ ")

        for y in range(0, height):
          pixel = pixels[x, y]
          r_val = pixel[0]
          g_val = pixel[1]
          b_val = pixel[2]

#Temporarily force to a single color channel
          # if r_val >= g_val and r_val >= b_val:
          #   g_val = 0
          #   b_val = 0
          # elif g_val > r_val and g_val > b_val:
          #   r_val = 0
          #   b_val = 0
          # else:
          #   r_val = 0
          #   g_val = 0

          output_file.write(f"{{ {r_val}, {g_val}, {b_val} }}, ")


        output_file.write(f"}}, \n")

      output_file.write(f"}};\n")
