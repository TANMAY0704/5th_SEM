# Import necessary libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score, precision_score, recall_score, f1_score, confusion_matrix, roc_curve, auc
from sklearn.preprocessing import LabelEncoder
from sklearn.impute import SimpleImputer
from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from imblearn.over_sampling import SMOTE
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Conv1D, MaxPooling1D, Flatten
import matplotlib.pyplot as plt
import seaborn as sns
import itertools
import numpy as np

# Set random state value
random_state_value = 42

# Function to load data
def load_data(file_path):
    data = pd.read_csv(file_path)
    return data

# Function to clean data
def clean_data(data):
    data.dropna(inplace=True)
    data = data.drop(['Unnamed: 0', 'Sex'], axis=1)
    return data

# Function to preprocess data
def preprocess_data(X, y):
    y_numeric = y.str.extract('(\\d+)').astype(int)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y_numeric, test_size=0.2, random_state=random_state_value)
    imputer = SimpleImputer(strategy='mean')
    X_train_imputed = pd.DataFrame(
        imputer.fit_transform(X_train), columns=X_train.columns)
    X_test_imputed = pd.DataFrame(
        imputer.transform(X_test), columns=X_test.columns)
    k_neighbors_value = min(5, len(X_train) - 1)

    smote = SMOTE(sampling_strategy='auto', k_neighbors=k_neighbors_value, random_state=random_state_value)
    X_train_resampled, y_train_resampled = smote.fit_resample(X_train_imputed, y_train)

    return X_train_resampled, X_test_imputed, y_train_resampled.values.ravel(), y_test.values.ravel()

# Function to plot confusion matrix
def plot_confusion_matrix(y_true, y_pred, classes, normalize=False, title=None, cmap=plt.cm.Blues):
    if not title:
        if normalize:
            title = 'Normalized Confusion Matrix'
        else:
            title = 'Confusion Matrix'

    cm = confusion_matrix(y_true, y_pred)

    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]

    plt.imshow(cm, interpolation='nearest', cmap=cmap)
    plt.title(title)
    plt.colorbar()

    tick_marks = np.arange(len(classes))
    plt.xticks(tick_marks, classes, rotation=45)
    plt.yticks(tick_marks, classes)

    fmt = '.2f' if normalize else 'd'
    thresh = cm.max() / 2.
    for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
        plt.text(j, i, format(cm[i, j], fmt),
                 horizontalalignment="center",
                 color="white" if cm[i, j] > thresh else "black")

    plt.tight_layout()
    plt.ylabel('True label')
    plt.xlabel('Predicted label')

# Function to train and evaluate machine learning models
def train_and_evaluate_ml(classifier, X_train, X_test, y_train, y_test):
    classifier.fit(X_train, y_train)
    predictions = classifier.predict(X_test)

    accuracy = accuracy_score(y_test, predictions)
    precision = precision_score(y_test, predictions, average='weighted')
    recall = recall_score(y_test, predictions, average='weighted')
    f1 = f1_score(y_test, predictions, average='weighted')

    print("Accuracy:", accuracy)
    print("Precision:", precision)
    print("Recall:", recall)
    print("F1 Score:", f1)

    print("\nClassification Report:")
    print(classification_report(y_test, predictions, zero_division=1))

    # Confusion Matrix Plot
    plt.figure(figsize=(6, 4))
    plot_confusion_matrix(y_test, predictions, classes=np.unique(y_test), normalize=True, title='Normalized Confusion Matrix')
    plt.show()

    roc_auc = None

    # AUC-ROC Curve Plot
    y_prob = classifier.predict_proba(X_test)  # Assuming the classifier has a predict_proba method
    n_classes = len(np.unique(y_test))
    fpr = dict()
    tpr = dict()
    roc_auc = dict()
    for i in range(n_classes):
        fpr[i], tpr[i], _ = roc_curve(y_test == i, y_prob[:, i])
        roc_auc[i] = auc(fpr[i], tpr[i])

    # Plot AUC-ROC curve
    plt.figure(figsize=(6, 4))
    for i in range(n_classes):
        plt.plot(fpr[i], tpr[i], label=f'Class {i} (AUC = {roc_auc[i]:.2f})')
    plt.plot([0, 1], [0, 1], 'k--', lw=2)
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('Receiver Operating Characteristic (ROC) Curve')
    plt.legend(loc="lower right")
    plt.show()

    return accuracy, precision, recall, f1, roc_auc
def train_and_evaluate_ml_before(classifier, X_train, X_test, y_train, y_test):
    classifier.fit(X_train, y_train)
    predictions = classifier.predict(X_test)

    accuracy = accuracy_score(y_test, predictions)
    precision = precision_score(y_test, predictions, average='weighted')
    recall = recall_score(y_test, predictions, average='weighted')
    f1 = f1_score(y_test, predictions, average='weighted')

    print("Accuracy:", accuracy)
    print("Precision:", precision)
    print("Recall:", recall)
    print("F1 Score:", f1)

    print("\nClassification Report:")
    print(classification_report(y_test, predictions, zero_division=1))

    return accuracy, precision, recall, f1

# Function to train and evaluate neural network
def train_and_evaluate_nn(model, X_train, y_train, X_test, y_test, epochs=20, batch_size=32):
    model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, verbose=0)

    y_pred_prob = model.predict(X_test)
    y_pred = y_pred_prob.argmax(axis=1)

    # Accuracy, Precision, Recall, F1 Score
    print("Neural Network Accuracy:", accuracy_score(y_test, y_pred))
    print("Neural Network Precision:", precision_score(y_test, y_pred, average='weighted'))
    print("Neural Network Recall:", recall_score(y_test, y_pred, average='weighted'))
    print("Neural Network F1 Score:", f1_score(y_test, y_pred, average='weighted'))

    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted')
    recall = recall_score(y_test, y_pred, average='weighted')
    f1 = f1_score(y_test, y_pred, average='weighted')

    return accuracy, recall, precision, f1

file_path = "hcvdat0.csv"
data = load_data(file_path)

data.hist(figsize=(10,10))
plt.show()

cleaned_data = clean_data(data)
X = cleaned_data.drop('Category', axis=1)
y = cleaned_data['Category']

# The train_test_split function should be called after defining X and y
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=random_state_value)

# KNN Classifier Before Preprocessing
print("\nKNN Classifier (Before Preprocessing):")
knn_classifier = KNeighborsClassifier(n_neighbors=5)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=random_state_value)
knn_accuracy_before, knn_precision_before, knn_recall_before, knn_f1_before = train_and_evaluate_ml_before(knn_classifier, X_train, X_test, y_train, y_test)

# Decision Tree Classifier Before Preprocessing
print("\nDecision Tree Classifier (Before Preprocessing):")
dt_classifier = DecisionTreeClassifier(random_state=random_state_value)
dt_accuracy_before, dt_precision_before, dt_recall_before, dt_f1_before = train_and_evaluate_ml_before(dt_classifier, X_train, X_test, y_train, y_test)

# Random Forest Classifier Before Preprocessing
print("\nRandom Forest Classifier (Before Preprocessing):")
rf_classifier = RandomForestClassifier(random_state=random_state_value)
rf_accuracy_before, rf_precision_before, rf_recall_before, rf_f1_before = train_and_evaluate_ml_before(rf_classifier, X_train, X_test, y_train, y_test)

# SVM Classifier Before Preprocessing
print("\nSVM Classifier (Before Preprocessing):")
svm_classifier = SVC(probability=True)
svm_accuracy_before, svm_precision_before, svm_recall_before, svm_f1_before = train_and_evaluate_ml_before(svm_classifier, X_train, X_test, y_train, y_test)

def build_cnn_model(input_shape, num_classes):
    model = Sequential()
    model.add(Conv1D(32, kernel_size=3, activation='relu', input_shape=input_shape))
    model.add(MaxPooling1D(pool_size=2))
    model.add(Flatten())
    model.add(Dense(128, activation='relu'))
    model.add(Dense(num_classes, activation='softmax'))
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    return model
# Neural Network Before Preprocessing
print("\nNeural Network (Before Preprocessing):")
X_train_resampled, X_test_imputed, y_train_resampled, y_test = preprocess_data(X, y)
num_classes = len(np.unique(y_train_resampled))
input_shape = (X_train_resampled.shape[1], 1)
X_train_reshaped = X_train_resampled.values.reshape(X_train_resampled.shape[0], X_train_resampled.shape[1], 1)
X_test_reshaped = X_test_imputed.values.reshape(X_test_imputed.shape[0], X_test_imputed.shape[1], 1)
model = build_cnn_model(input_shape, num_classes)
nn_accuracy_before, nn_precision_before, nn_recall_before, nn_f1_before, nn_roc_auc_before = train_and_evaluate_nn(model, X_train_reshaped, y_train_resampled, X_test_reshaped, y_test, epochs=20, batch_size=32)

# Continue with the plotting code and any other analysis you want to perform
# ...


print("\nCNN (Before Preprocessing):")
X_train_resampled, X_test_imputed, y_train_resampled, y_test = preprocess_data(X, y)
num_classes = len(np.unique(y_train_resampled))
input_shape = (X_train_resampled.shape[1], 1)
X_train_reshaped = X_train_resampled.values.reshape(X_train_resampled.shape[0], X_train_resampled.shape[1], 1)
X_test_reshaped = X_test_imputed.values.reshape(X_test_imputed.shape[0], X_test_imputed.shape[1], 1)
model = build_cnn_model(input_shape, num_classes)
cnn_accuracy_before, cnn_precision_before, cnn_recall_before, cnn_f1_before, cnn_roc_auc_before = train_and_evaluate_cnn(model, X_train_reshaped, y_train_resampled, X_test_reshaped, y_test, epochs=20, batch_size=32)

# Preprocess data for other classifiers
X_train, X_test, y_train, y_test = preprocess_data(X, y)

# KNN After Preprocessing
print("\nKNN Classifier (After Preprocessing):")
knn_accuracy_after, knn_precision_after, knn_recall_after, knn_f1_after, _ = train_and_evaluate_ml(KNeighborsClassifier(n_neighbors=5), X_train, X_test, y_train, y_test)

# Decision Tree After Preprocessing
print("\nDecision Tree Classifier (After Preprocessing):")
dt_accuracy_after, dt_precision_after, dt_recall_after, dt_f1_after, _ = train_and_evaluate_ml(DecisionTreeClassifier(random_state=random_state_value), X_train, X_test, y_train, y_test)

# Random Forest After Preprocessing
print("\nRandom Forest Classifier (After Preprocessing):")
rf_accuracy_after, rf_precision_after, rf_recall_after, rf_f1_after, _ = train_and_evaluate_ml(RandomForestClassifier(random_state=random_state_value), X_train, X_test, y_train, y_test)

# SVM After Preprocessing
print("\nSVM Classifier (After Preprocessing):")
svm_accuracy_after, svm_precision_after, svm_recall_after, svm_f1_after, _ = train_and_evaluate_ml(SVC(probability=True), X_train, X_test, y_train, y_test)

# Neural Network After Preprocessing
X_train_nn, X_test_nn, y_train_nn, y_test_nn = preprocess_data(X, y)
print("\nNeural Network Classifier (After Preprocessing):")
model_nn = Sequential()
model_nn.add(Dense(128, input_dim=X_train_nn.shape[1], activation='relu'))
model_nn.add(Dense(64, activation='relu'))
model_nn.add(Dense(num_classes, activation='softmax'))  
model_nn.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
nn_accuracy_after, nn_precision_after, nn_recall_after, nn_f1_after, nn_roc_auc_after = train_and_evaluate_nn(model_nn, X_train_nn, y_train_nn, X_test_nn, y_test_nn)

# CNN After Preprocessing
input_shape_cnn = (X_train_nn.shape[1], 1) 
X_train_nn_cnn = X_train_nn.values.reshape(X_train_nn.shape[0], X_train_nn.shape[1], 1)
X_test_nn_cnn = X_test_nn.values.reshape(X_test_nn.shape[0], X_test_nn.shape[1], 1)
print("\nCNN Classifier (After Preprocessing):")
cnn_model_after = build_cnn_model(input_shape_cnn, num_classes)
cnn_accuracy_after, cnn_precision_after, cnn_recall_after, cnn_f1_after, _ = train_and_evaluate_nn(cnn_model_after, X_train_nn_cnn, y_train_nn, X_test_nn_cnn, y_test_nn)
import numpy as np
import matplotlib.pyplot as plt

# Assuming you have defined these variables somewhere in your code
# with appropriate values before running the following code.

classifiers_before = ['KNN', 'Decision Tree', 'Random Forest', 'SVM', 'Neural Network', 'CNN']

# Accuracy values
accuracy_values_before = [knn_accuracy_before, dt_accuracy_before, rf_accuracy_before, svm_accuracy_before, nn_accuracy_before, cnn_accuracy_before]

# Precision values
precision_values_before = [knn_precision_before, dt_precision_before, rf_precision_before, svm_precision_before, nn_precision_before, cnn_precision_before]

# Recall values
recall_values_before = [knn_recall_before, dt_recall_before, rf_recall_before, svm_recall_before, nn_recall_before, cnn_recall_before]

# F1 Score values
f1_values_before = [knn_f1_before, dt_f1_before, rf_f1_before, svm_f1_before, nn_f1_before, cnn_f1_before]

classifiers_after = ['KNN', 'Decision Tree', 'Random Forest', 'SVM', 'Neural Network', 'CNN']

# Accuracy values after preprocessing
accuracy_values_after = [knn_accuracy_after, dt_accuracy_after, rf_accuracy_after, svm_accuracy_after, nn_accuracy_after, cnn_accuracy_after]

# Precision values after preprocessing
precision_values_after = [knn_precision_after, dt_precision_after, rf_precision_after, svm_precision_after, nn_precision_after, cnn_precision_after]

# Recall values after preprocessing
recall_values_after = [knn_recall_after, dt_recall_after, rf_recall_after, svm_recall_after, nn_recall_after, cnn_recall_after]

# F1 Score values after preprocessing
f1_values_after = [knn_f1_after, dt_f1_after, rf_f1_after, svm_f1_after, nn_f1_after, cnn_f1_after]

# Print values before preprocessing
print("Before Preprocessing:")
for classifier, accuracy, precision, recall, f1 in zip(classifiers_before, accuracy_values_before, precision_values_before, recall_values_before, f1_values_before):
    print(f"{classifier}:")
    print(f"  Accuracy: {accuracy:.4f}")
    print(f"  Precision: {precision:.4f}")
    print(f"  Recall: {recall:.4f}")
    print(f"  F1 Score: {f1:.4f}")
    print()

# Print values after preprocessing
print("After Preprocessing:")
for classifier, accuracy, precision, recall, f1 in zip(classifiers_after, accuracy_values_after, precision_values_after, recall_values_after, f1_values_after):
    print(f"{classifier}:")
    print(f"  Accuracy: {accuracy:.4f}")
    print(f"  Precision: {precision:.4f}")
    print(f"  Recall: {recall:.4f}")
    print(f"  F1 Score: {f1:.4f}")
    print()

# Plotting Accuracy
fig, ax = plt.subplots(figsize=(10, 6))
bar_width = 0.35
bar_positions_before = np.arange(len(classifiers_before))
bar_positions_after = bar_positions_before + bar_width

# Before Preprocessing
ax.bar(bar_positions_before, accuracy_values_before, width=bar_width, label='Before Preprocessing', alpha=0.7)

# After Preprocessing
ax.bar(bar_positions_after, accuracy_values_after, width=bar_width, label='After Preprocessing', alpha=0.7)

# Annotate values on bars
for i, (before, after) in enumerate(zip(accuracy_values_before, accuracy_values_after)):
    ax.text(i, before + 0.01, f'{before:.4f}', ha='center', va='bottom', fontsize=8)
    ax.text(i + bar_width, after + 0.01, f'{after:.4f}', ha='center', va='bottom', fontsize=8)

ax.set_title('Accuracy Comparison Before and After Preprocessing')
ax.set_xlabel('Classifier')
ax.set_ylabel('Accuracy')
ax.set_xticks(bar_positions_before + bar_width / 2)
ax.set_xticklabels(classifiers_before)
ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

# Plotting Precision, F1-Score, and Recall
fig, ax = plt.subplots(figsize=(10, 6))

# Before Preprocessing
ax.plot(classifiers_before, precision_values_before, marker='o', label='Precision (Before)', color='darkred')
ax.plot(classifiers_before, f1_values_before, marker='o', label='F1-Score (Before)', color='blue')
ax.plot(classifiers_before, recall_values_before, marker='o', label='Recall (Before)', color='purple')

# After Preprocessing
ax.plot(classifiers_before, precision_values_after, marker='o', label='Precision (After)', color='darkorange')
ax.plot(classifiers_before, f1_values_after, marker='o', label='F1-Score (After)', color='green')
ax.plot(classifiers_before, recall_values_after, marker='o', label='Recall (After)', color='brown')

# Annotate values on points
for i, value in enumerate(precision_values_before):
    ax.text(i, value + 0.01, f'{round(value, 3)}', ha='center', va='bottom', color='darkred')

for i, value in enumerate(precision_values_after):
    ax.text(i, value - 0.01, f'{round(value, 3)}', ha='center', va='top', color='darkorange')

ax.legend(loc='upper left', bbox_to_anchor=(1, 1))
ax.set_ylabel('Score')
plt.title('Precision, F1-Score, and Recall Comparison Before and After Preprocessing')
plt.show()


