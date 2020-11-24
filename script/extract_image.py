#!/usr/local/bin/python3
import argparse
import os

from PIL import Image, ImageSequence

if __name__ == "__main__":

  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument('--width', default=64, type=int, help='Image width')
  argument_parser.add_argument('--height', default=32, type=int, help='Image height')
  argument_parser.add_argument('--handle_frames', default=False, help='Process multiple frames')
  argument_parser.add_argument('files', metavar='FILES', nargs='*', help='Files to convert')

  args = argument_parser.parse_args()

  width = args.width
  height = args.height

  for image_file in args.files:

    image = Image.open(image_file)

    if image.size[0] != width or image.size[1] != height:
      print(f"Image {image_file} was {image.size[0]}x{image.size[1]} instead of {width}x{height} - Mode ${image.mode}")

      exit(1)

    with open(os.path.splitext(image_file)[0] + ".h", "w") as output_file :

      output_file.write(f"#define IMAGE_WIDTH {width}\n")
      output_file.write(f"#define IMAGE_HEIGHT {height}\n")
      output_file.write("\n")

      output_file.write("\n") 

      frames = 0

      output_buffer = ""

      while True:
        try:
          image.seek(frames)
        except EOFError: 
          print("Seek past end")
          break

        frames = frames + 1

        print(f"Processing frame {frames}")

        pixels = image.load()

        output_buffer += f"\t{{ "


        for x in range(0, width):
          output_buffer += f"\t\t{{ "

          for y in range(0, height):
            pixel = pixels[x, y]

            if image.mode == "P":
              palette_color = pixel   

              color = image.getpalette()[palette_color * 3:(palette_color + 1) * 3]

              r_val = color[0]
              g_val = color[1]
              b_val = color[2]
            else:

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

            output_buffer += f"{{ {r_val}, {g_val}, {b_val} }}, "


          output_buffer += f"}}, \n"
        output_buffer += f"}}, \n"

      print(f"{frames} frames found.")

      output_file.write(f"#define IMAGE_FRAMES {frames}\n")

      output_file.write(f"uint8_t const IMAGE_DATA[{frames}][IMAGE_WIDTH][IMAGE_HEIGHT][3] = {{\n")

      output_file.write(output_buffer)

      output_file.write(f"}};\n")
