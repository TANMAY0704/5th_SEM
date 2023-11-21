import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score
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

def load_data(file_path):
    data = pd.read_csv(file_path)
    return data

def clean_data(data):
    data.dropna(inplace=True)
    data = data.drop(['Unnamed: 0', 'Sex'], axis=1)
    return data

def preprocess_data(X, y):
    y_numeric = y['Category'].str.extract('(\d+)').astype(int)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y_numeric, test_size=0.2, random_state=42)
    imputer = SimpleImputer(strategy='mean')
    X_train_imputed = pd.DataFrame(
        imputer.fit_transform(X_train), columns=X_train.columns)
    X_test_imputed = pd.DataFrame(
        imputer.transform(X_test), columns=X_test.columns)
    k_neighbors_value = min(5, len(X_train) - 1)
    smote = SMOTE(sampling_strategy='auto',
                  k_neighbors=k_neighbors_value, random_state=42)
    if len(X_train) <= 5:
        X_train_resampled, y_train_resampled = smote.fit_resample(
            X_train_imputed, y_train)
    else:
        X_train_resampled, y_train_resampled = X_train_imputed, y_train
    return (
        X_train_resampled,
        X_test_imputed,
        y_train_resampled.values.ravel(),
        y_test.values.ravel()
    )


def build_neural_network(X_train_resampled):
    model = Sequential()
    model.add(Dense(128, input_dim=X_train_resampled.shape[1], activation='relu'))
    model.add(Dense(64, activation='relu'))
    model.add(Dense(5, activation='softmax'))  # 5 classes
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    return model

def build_cnn(X_train_resampled):
    model = Sequential()
    model.add(Conv1D(32, kernel_size=3, activation='relu', input_shape=(X_train_resampled.shape[1], 1)))
    model.add(MaxPooling1D(pool_size=2))
    model.add(Flatten())
    model.add(Dense(128, activation='relu'))
    model.add(Dense(5, activation='softmax'))  # 5 classes
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    return model

def train_and_evaluate(classifier, X_train, X_test, y_train, y_test):
    classifier.fit(X_train, y_train)
    predictions = classifier.predict(X_test)
    print("Classification Report:")
    print(classification_report(y_test, predictions, zero_division=1))
    print("Accuracy:", accuracy_score(y_test, predictions))

# Load and clean the data
file_path = "hcvdat0.csv"
data = load_data(file_path)
cleaned_data = clean_data(data)
X = cleaned_data.drop('Category', axis=1)
y = cleaned_data['Category']

# Convert the target variable to numeric format
y = y.str.extract('(\d+)').astype(int)

# Train and evaluate KNN before preprocessing
print("\nKNN Classifier (Before Preprocessing):")
knn_classifier = KNeighborsClassifier(n_neighbors=5)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)
train_and_evaluate(knn_classifier, X_train, X_test, y_train, y_test)

# ... (similar changes for other classifiers)

# Train and evaluate CNN before preprocessing
print("\nCNN Classifier (Before Preprocessing):")
cnn_model = build_cnn(X_train.values.reshape(X_train.shape[0], X_train.shape[1], 1))
cnn_model.fit(X_train.values.reshape(X_train.shape[0], X_train.shape[1], 1), y_train, epochs=20, batch_size=32, verbose=1)
y_pred_prob_cnn = cnn_model.predict(X_test.values.reshape(X_test.shape[0], X_test.shape[1], 1))
y_pred_cnn = y_pred_prob_cnn.argmax(axis=1)
print("CNN Classification Report:")
print(classification_report(y_test, y_pred_cnn))
print("CNN Accuracy:", accuracy_score(y_test, y_pred_cnn))

# ... (similar changes for other classifiers)

# Preprocess data and train/evaluate models
X_train, X_test, y_train, y_test = preprocess_data(X, y)

# Train and evaluate KNN after preprocessing
print("\nKNN Classifier (After Preprocessing):")
train_and_evaluate(knn_classifier, X_train, X_test, y_train, y_test)

# ... (similar changes for other classifiers)

# Train and evaluate CNN after preprocessing
print("\nCNN Classifier (After Preprocessing):")
cnn_model = build_cnn(X_train.values.reshape(X_train.shape[0], X_train.shape[1], 1))
cnn_model.fit(X_train.values.reshape(X_train.shape[0], X_train.shape[1], 1), y_train, epochs=20, batch_size=32, verbose=1)
y_pred_prob_cnn = cnn_model.predict(X_test.values.reshape(X_test.shape[0], X_test.shape[1], 1))
y_pred_cnn = y_pred_prob_cnn.argmax(axis=1)
print("CNN Classification Report:")
print(classification_report(y_test, y_pred_cnn))
print("CNN Accuracy:", accuracy_score(y_test, y_pred_cnn))

# ... (similar changes for other classifiers)

# Build, train, and evaluate Neural Network after preprocessing
print("\nNeural Network Classifier (After Preprocessing):")
nn_model = build_neural_network(X_train)
nn_model.fit(X_train, y_train, epochs=20, batch_size=32, verbose=1)
y_pred_prob_nn = nn_model.predict(X_test)
y_pred_nn = y_pred_prob_nn.argmax(axis=1)
print("Neural Network Classification Report:")
print(classification_report(y_test, y_pred_nn))
print("Neural Network Accuracy:", accuracy_score(y_test, y_pred_nn))
