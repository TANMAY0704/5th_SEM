import os
import cv2
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score, classification_report
import matplotlib.pyplot as plt

def load_images_from_folders(root_folder):
    images = []
    labels = []
    class_counts = {}

    for label in os.listdir(root_folder):
        label_path = os.path.join(root_folder, label)
        if os.path.isdir(label_path):
            class_name = int(label)  # Assuming the folder name is the label
            class_counts[class_name] = 0  # Initialize the count for this class
            for filename in os.listdir(label_path):
                if filename.endswith(".png"):
                    img_path = os.path.join(label_path, filename)
                    img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
                    img = cv2.resize(img, (64, 64))  # Adjust the size as needed
                    img = img.flatten()  # Flatten the image into a 1D array
                    images.append(img)
                    labels.append(class_name)
                    class_counts[class_name] += 1

    return np.array(images), np.array(labels), class_counts

def train_and_test_classifier(train_data, train_labels, test_data, test_labels, classifier):
    classifier.fit(train_data, train_labels)
    pred = classifier.predict(test_data)
    acc = accuracy_score(test_labels, pred)
    report = classification_report(test_labels, pred)
    return acc, report

# Load the training and test datasets
train_root_folder = 'Train'
test_root_folder = 'Test'

train_data, train_labels, train_class_counts = load_images_from_folders(train_root_folder)
test_data, test_labels, test_class_counts = load_images_from_folders(test_root_folder)

# Preprocess the data as needed (e.g., normalize pixel values between 0 and 1)

# Train and test the KNN classifier
knn = KNeighborsClassifier(n_neighbors=5)
knn_acc, knn_report = train_and_test_classifier(train_data, train_labels, test_data, test_labels, knn)

# Train and test the SVM classifier
svm = SVC(kernel='linear')
svm_acc, svm_report = train_and_test_classifier(train_data, train_labels, test_data, test_labels, svm)

# Train and test the Random Forest classifier
rf = RandomForestClassifier(n_estimators=100)
rf_acc, rf_report = train_and_test_classifier(train_data, train_labels, test_data, test_labels, rf)

# Train and test the neural network classifier
nn = MLPClassifier(hidden_layer_sizes=(100,), max_iter=1000)
nn_acc, nn_report = train_and_test_classifier(train_data, train_labels, test_data, test_labels, nn)

# Print the number of images loaded for each class
print('\nNumber of images loaded for each class in the training set:')
for class_name, count in train_class_counts.items():
    print(f'Class {class_name}: {count} images')

print('\nNumber of images loaded for each class in the test set:')
for class_name, count in test_class_counts.items():
    print(f'Class {class_name}: {count} images')

# Print the accuracy of each classifier
print('\nKNN accuracy:', knn_acc)
print('SVM accuracy:', svm_acc)
print('Random Forest accuracy:', rf_acc)
print('Neural Network accuracy:', nn_acc)

# Print classification reports
print('\nKNN Classification Report:\n', knn_report)
print('\nSVM Classification Report:\n', svm_report)
print('\nRandom Forest Classification Report:\n', rf_report)
print('\nNeural Network Classification Report:\n', nn_report)

# Plotting the results (you may customize this based on your preference)
labels = ['KNN', 'SVM', 'Random Forest', 'Neural Network']
accuracies = [knn_acc, svm_acc, rf_acc, nn_acc]

plt.bar(labels, accuracies)
plt.ylabel('Accuracy')
plt.title('Classifier Performance')
plt.show()
