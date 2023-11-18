import os
import cv2
import numpy as np
from skimage import io
from skimage.morphology import skeletonize

# Function to perform skeletonization and resize
def skeletonize_and_resize(input_path, output_path):
    image = io.imread(input_path)

    # Check if the image is grayscale (single channel) or already binary
    if image.ndim > 2:
        image = image[:, :, 0]  # Convert to single channel if not grayscale

    # Skeletonize the image
    skeleton = skeletonize(image > 0)

    # Resize to 64x64 pixels
    resized_skeleton = cv2.resize(np.array(skeleton, dtype=np.uint8) * 255, (64, 64), interpolation=cv2.INTER_AREA)

    # Save the skeletonized and resized image
    cv2.imwrite(output_path, resized_skeleton)

input_folder = 'Images'
output_folder = 'SkeletonizedResizedImages'

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

for root, dirs, files in os.walk(input_folder):
    for file in files:
        if file.lower().endswith(('.jpg', '.png', '.bmp')):
            input_path = os.path.join(root, file)
            output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder))
            skeletonize_and_resize(input_path, output_path)
