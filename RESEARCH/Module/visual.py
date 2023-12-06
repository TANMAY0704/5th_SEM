import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import  roc_curve, auc
import itertools

def plot_confusion_matrix(y_true, y_pred, classes, normalize=False, title=None, cmap=plt.cm.Blues):
    if not title:
        if normalize:
            title = 'Normalized Confusion Matrix'
        else:
            title = 'Confusion Matrix'

    cm = np.zeros((len(classes), len(classes)))

    for i, j in zip(y_true, y_pred):
        cm[i, j] += 1

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


def calculate_and_plot_auc(y_test, y_pred_prob, num_classes):
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

    return roc_auc


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

def print_and_plot_metrics_bar(classifiers, metrics_before, metrics_after, metric_name):
    print(f"{metric_name} Comparison Before and After Preprocessing:")
    for classifier, before, after in zip(classifiers, metrics_before, metrics_after):
        print(f"{classifier}:")
        print(f"  {metric_name} Before: {before:.4f}")
        print(f"  {metric_name} After: {after:.4f}")
        print()

    fig, ax = plt.subplots(figsize=(10, 6))

    # Before Preprocessing
    ax.bar(classifiers, metrics_before, label=f'{metric_name} (Before)', color='darkred', alpha=0.7)

    # After Preprocessing
    ax.bar(classifiers, metrics_after, label=f'{metric_name} (After)', color='darkorange', alpha=0.7)

    ax.set_ylabel('Score')
    ax.set_title(f'{metric_name} Comparison Before and After Preprocessing')
    ax.set_xticks(np.arange(len(classifiers)))
    ax.set_xticklabels(classifiers)

    # Add legends
    ax.legend(loc='upper left', bbox_to_anchor=(1, 1))

    plt.show()
