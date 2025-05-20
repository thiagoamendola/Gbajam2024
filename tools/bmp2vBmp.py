from PIL import Image
import sys

def convert_bmp_to_8_indexed(input_path, output_path, show_palette=False):
    # Load image
    img = Image.open(input_path)

    # Convert to 8-color palette image using an adaptive palette
    img_quantized = img.convert('P', palette=Image.ADAPTIVE, colors=8)

    # Save the new 8-color indexed image
    img_quantized.save(output_path, format='BMP')

    print(f"Saved 8-color indexed BMP to: {output_path}")

    if show_palette:
        # Get the actual palette (returns up to 768 values, 256 * RGB)
        palette = img_quantized.getpalette()[:24]  # Only first 8*3 values (8 colors)
        print("Palette (RGB):")
        for i in range(8):
            r, g, b = palette[i*3:i*3+3]
            print(f"Index {i}: ({r}, {g}, {b})")

        # Show indexed values for each pixel (as a 2D list)
        pixels = list(img_quantized.getdata())
        width, height = img_quantized.size
        pixel_2d = [pixels[i * width:(i + 1) * width] for i in range(height)]

        print("\nIndexed pixel data:")
        for row in pixel_2d:
            print(row)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python bmp_to_8indexed.py <input.bmp> <output.bmp> [--show]")
    else:
        show = "--show" in sys.argv
        convert_bmp_to_8_indexed(sys.argv[1], sys.argv[2], show_palette=show)
