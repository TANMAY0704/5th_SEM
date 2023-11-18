import cv2
import os
from skimage.morphology import skeletonize
from skimage import img_as_ubyte

def thin_and_resize(input_path, output_path):
    image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)
    
    # Perform thinning or skeletonizing using skimage
    _, thinned_image = cv2.threshold(image, 128, 255, cv2.THRESH_BINARY)
    thinned_image = skeletonize(thinned_image)
    
    # Convert to 8-bit image (if needed, as skeletonize may return a boolean image)
    thinned_image = img_as_ubyte(thinned_image)
    
    # Resize to 64x64 pixels
    resized_image = cv2.resize(thinned_image, (64, 64))
    
    # Save the thinned and resized image
    cv2.imwrite(output_path, resized_image)

thinned_output_folder = 'ThinnedImages'

if not os.path.exists(thinned_output_folder):
    os.makedirs(thinned_output_folder)
    
input_folder = 'BinaryImages'
output_folder = 'ThinnedImages'

for root, dirs, files in os.walk(input_folder):
    for file in files:
        if file.lower().endswith(('.jpg', '.png', '.bmp')):
            input_path = os.path.join(root, file)
            output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder))
            thin_and_resize(input_path, output_path)
