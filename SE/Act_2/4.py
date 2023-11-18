import os
import cv2
import numpy as np
from skimage import io
from skimage.morphology import skeletonize
import pandas as pd

# Function to perform skeletonization and resize
def skeletonize_and_resize(input_path, output_path, output_intensity_path):
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

    # Extract pixel intensity values
    intensity_values = resized_skeleton.flatten()

    # Save the intensity values to an Excel file
    intensity_df = pd.DataFrame({'Intensity': intensity_values})
    intensity_df.to_excel(output_intensity_path, index=False)

input_folder = 'FilteredImages'
output_folder = 'SkeletonizedResizedImages'
output_intensity_folder = 'IntensityFiles'

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

if not os.path.exists(output_intensity_folder):
    os.makedirs(output_intensity_folder)

for root, dirs, files in os.walk(input_folder):
    for file in files:
        if file.lower().endswith(('.jpg', '.png', '.bmp')):
            input_path = os.path.join(root, file)
            output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder))
            output_intensity_path = os.path.join(output_intensity_folder, os.path.splitext(file)[0] + '.xlsx')
            skeletonize_and_resize(input_path, output_path, output_intensity_path)
