import cv2
import os
# Function to convert images to binary and resize
def convert_to_binary_and_resize(input_path, output_path):
    image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)
    
    # Convert to binary image
    _, binary_image = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)
    
    # Resize to 64x64 pixels
    resized_image = cv2.resize(binary_image, (64, 64))
    
    # Save the binary and resized image
    cv2.imwrite(output_path, resized_image)

binary_output_folder = 'BinaryImages'

if not os.path.exists(binary_output_folder):
    os.makedirs(binary_output_folder)


input_folder = 'FilteredImages'
output_folder = 'BinaryImages'

for root, dirs, files in os.walk(input_folder):
    for file in files:
        if file.lower().endswith(('.jpg', '.png', '.bmp')):
            input_path = os.path.join(root, file)
            output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder))
            convert_to_binary_and_resize(input_path, output_path)
