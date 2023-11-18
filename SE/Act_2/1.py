import cv2
import os

# Function to apply filtering techniques
def apply_filter(input_path, output_path):
    image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)
    
    # Apply a smoothing filter (e.g., Gaussian filter) to make the image smoother
    smoothed_image = cv2.GaussianBlur(image, (5, 5), 0)
    
    # Save the smoothed image
    cv2.imwrite(output_path, smoothed_image)

output_folder = 'FilteredImages'

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

languages = ['Bangla', 'English', 'Hindi', 'Odia']

for lang in languages:
    input_folder = 'Images\\' + lang

    for root, dirs, files in os.walk(input_folder):
        for file in files:
            if file.lower().endswith(('.jpg', '.png', '.bmp')):
                input_path = os.path.join(root, file)
                output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder))
                apply_filter(input_path, output_path)
