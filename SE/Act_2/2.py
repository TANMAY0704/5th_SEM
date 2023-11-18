import cv2
import os
# Function to convert to binary and resize
def binarize_and_resize(input_path, output_path):
    image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)
    
    # Apply a binary threshold
    _, binary_image = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)
    
    # Resize to 64x64 pixels
    resized_image = cv2.resize(binary_image, (64, 64), interpolation=cv2.INTER_AREA)
    
    # Save the binary and resized image
    cv2.imwrite(output_path, resized_image)

input_folder = 'FilteredImages'
output_folder = 'BinaryResizedImages'

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

for root, dirs, files in os.walk(input_folder):
    for file in files:
        if file.lower().endswith(('.jpg', '.png', '.bmp')):
            input_path = os.path.join(root, file)
            output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder))
            binarize_and_resize(input_path, output_path)
