import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    classification_report,
)
from .visual import plot_confusion_matrix, calculate_and_plot_auc
from .data_processing import clean_data, preprocess_data

def train_and_evaluate_model(model, X_train, y_train, X_test, y_test, is_nn=False, is_cnn=False, epochs=20, batch_size=32, after_preprocessing=False):
    # Data Cleaning
    X_train_cleaned = clean_data(X_train)
    X_test_cleaned = clean_data(X_test)

    # Data Preprocessing
    if not after_preprocessing:
        X_train, X_test, y_train, y_test = preprocess_data(X_train_cleaned, y_train)
    else:
        X_train, X_test, y_train, y_test = preprocess_data(X_train_cleaned, y_train, polynomial_degree=2, X_test=X_test_cleaned)

    # Model Training
    if is_nn or is_cnn:
        model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, verbose=0)
        y_pred_prob = model.predict(X_test)
        y_pred = y_pred_prob.argmax(axis=1)
    else:
        model.fit(X_train, y_train)
        y_pred = model.predict(X_test)

    # Metrics Evaluation
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted')
    recall = recall_score(y_test, y_pred, average='weighted')
    f1 = f1_score(y_test, y_pred, average='weighted')

    # Print Metrics
    print("Accuracy:", accuracy)
    print("Precision:", precision)
    print("Recall:", recall)
    print("F1 Score:", f1)

    # Classification Report
    print("\nClassification Report:")
    print(classification_report(y_test, y_pred, zero_division=1))

    # Confusion Matrix Plot
    plt.figure(figsize=(6, 4))
    plot_confusion_matrix(y_test, y_pred, classes=np.unique(y_test), normalize=True, title='Normalized Confusion Matrix')
    plt.show()

    roc_auc = None

    if is_nn or is_cnn:
        # AUC-ROC Curve Plot for Neural Network or CNN
        num_classes = len(np.unique(y_train))
        roc_auc = calculate_and_plot_auc(y_test, y_pred_prob, num_classes)

    return accuracy, precision, recall, f1, roc_auc
