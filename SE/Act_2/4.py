# ... (previous code)
import cv2
import os
import pandas as pd

# Function to copy pixel intensity values to an Excel file
def copy_to_excel(input_path, excel_path):
    image = cv2.imread(input_path, cv2.IMREAD_GRAYSCALE)
    
    # Resize to 64x64 pixels
    resized_image = cv2.resize(image, (64, 64))
    
    # Flatten the 2D array to 1D
    pixel_values = resized_image.flatten()
    
    # Create a DataFrame and save to Excel
    df = pd.DataFrame({'Pixel Intensity': pixel_values})
    df.to_excel(excel_path, index=False)

excel_output_folder = 'ExcelFiles'

if not os.path.exists(excel_output_folder):
    os.makedirs(excel_output_folder)

input_folder = 'ThinnedImages'
output_folder = 'ExcelFiles'
for root, dirs, files in os.walk(input_folder):
    for file in files:
        if file.lower().endswith(('.jpg', '.png', '.bmp')):
            input_path = os.path.join(root, file)
            output_path = os.path.join(output_folder, os.path.relpath(input_path, input_folder) + '.xlsx')
            copy_to_excel(input_path, output_path)
