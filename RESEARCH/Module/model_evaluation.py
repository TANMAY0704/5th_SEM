import numpy as np
import itertools
import matplotlib.pyplot as plt
from sklearn.metrics import (
    accuracy_score, precision_score, recall_score, f1_score,
    classification_report, confusion_matrix, roc_curve, auc
)

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
    plt.xticks(tick_marks, classes)
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
    # Compute ROC curve and ROC area for each class
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

    plt.figure(figsize=(6, 4))
    plot_confusion_matrix(y_test, predictions, classes=np.unique(y_test), normalize=True, title='Normalized Confusion Matrix')
    plt.show()

    return accuracy, precision, recall, f1

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
    # Classification Report
    print("\nNeural Network Classification Report:")
    print(classification_report(y_test, y_pred, zero_division=1))

    # Confusion Matrix Plot
    plt.figure(figsize=(6, 4))
    plot_confusion_matrix(y_test, y_pred, classes=np.unique(y_test), normalize=True, title='Normalized Confusion Matrix')
    plt.show()

    # AUC-ROC Curve Plot
    num_classes = len(np.unique(y_train))
    fpr = dict()
    tpr = dict()
    roc_auc = dict()

    for i in range(num_classes):
        fpr[i], tpr[i], _ = roc_curve(y_test == i, y_pred_prob[:, i])
        roc_auc[i] = auc(fpr[i], tpr[i])

    # Plot AUC-ROC curve
    plt.figure(figsize=(6, 4))
    for i in range(num_classes):
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



def train_and_evaluate_cnn(model, X_train, y_train, X_test, y_test, epochs=20, batch_size=32):
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

    # Classification Report
    print("\nNeural Network Classification Report:")
    print(classification_report(y_test, y_pred, zero_division=1))

    # Confusion Matrix Plot
    plt.figure(figsize=(6, 4))
    plot_confusion_matrix(y_test, y_pred, classes=np.unique(y_test), normalize=True, title='Normalized Confusion Matrix', cmap=plt.cm.Blues)
    plt.show()

    # AUC-ROC Curve Plot
    num_classes = len(np.unique(y_train))
    fpr = dict()
    tpr = dict()
    roc_auc = dict()

    for i in range(num_classes):
        fpr[i], tpr[i], _ = roc_curve(y_test == i, y_pred_prob[:, i])
        roc_auc[i] = auc(fpr[i], tpr[i])

    # Plot AUC-ROC curve
    plt.figure(figsize=(6, 4))
    for i in range(num_classes):
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


def print_and_plot_metrics_line(classifiers, metrics_before, metrics_after, metric_name):
    print(f"{metric_name} Comparison Before and After Preprocessing:")
    for classifier, before, after in zip(classifiers, metrics_before, metrics_after):
        print(f"{classifier}:")
        print(f"  {metric_name} Before: {before:.4f}")
        print(f"  {metric_name} After: {after:.4f}")
        print()

    fig, ax = plt.subplots(figsize=(10, 6))

    # Before Preprocessing
    ax.plot(classifiers, metrics_before, marker='o', linestyle='-', label=f'{metric_name} (Before)', color='darkred')

    # After Preprocessing
    ax.plot(classifiers, metrics_after, marker='o', linestyle='-', label=f'{metric_name} (After)', color='darkorange')

    # Annotate values on points
    for i, value in enumerate(metrics_before):
        ax.text(i, value + 0.01, f'{round(value, 3)}', ha='center', va='bottom', color='darkred')

    for i, value in enumerate(metrics_after):
        ax.text(i, value - 0.01, f'{round(value, 3)}', ha='center', va='top', color='darkorange')

    ax.set_ylabel('Score')
    ax.set_title(f'{metric_name} Comparison Before and After Preprocessing')
    ax.set_xticks(np.arange(len(classifiers)))
    ax.set_xticklabels(classifiers)
    
    # Add legends
    ax.legend(loc='upper left', bbox_to_anchor=(1, 1))
    
    plt.show()