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
from tensorflow.keras.layers import Dense

# Define random state for reproducibility
random_state_value = 42

def load_data(file_path):
    data = pd.read_csv(file_path)
    return data

def clean_data(data):
    data.dropna(inplace=True)
    data = data.drop(['Unnamed: 0', 'Sex'], axis=1)
    return data

def preprocess_data(X, y):
    y_numeric = y.str.extract('(\d+)').astype(int)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y_numeric, test_size=0.2, random_state=random_state_value)
    imputer = SimpleImputer(strategy='mean')
    X_train_imputed = pd.DataFrame(
        imputer.fit_transform(X_train), columns=X_train.columns)
    X_test_imputed = pd.DataFrame(
        imputer.transform(X_test), columns=X_test.columns)
    k_neighbors_value = min(5, len(X_train) - 1)
    
    # Apply SMOTE for handling class imbalances
    smote = SMOTE(sampling_strategy='auto', k_neighbors=k_neighbors_value, random_state=random_state_value)
    X_train_resampled, y_train_resampled = smote.fit_resample(X_train_imputed, y_train)
    
    return X_train_resampled, X_test_imputed, y_train_resampled.values.ravel(), y_test.values.ravel()

def train_and_evaluate_ml(classifier, X_train, X_test, y_train, y_test):
    classifier.fit(X_train, y_train)
    predictions = classifier.predict(X_test)
    print("Classification Report:")
    print(classification_report(y_test, predictions, zero_division=1))
    print("Accuracy:", accuracy_score(y_test, predictions))

def train_and_evaluate_nn(model, X_train, y_train, X_test, y_test, epochs=20, batch_size=32):
    model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, verbose=1)
    y_pred_prob = model.predict(X_test)
    y_pred = y_pred_prob.argmax(axis=1)
    print("Neural Network Classification Report:")
    print(classification_report(y_test, y_pred, zero_division=1))
    print("Neural Network Accuracy:", accuracy_score(y_test, y_pred))

# Load and clean data
file_path = "hcvdat0.csv"
data = load_data(file_path)
cleaned_data = clean_data(data)
X = cleaned_data.drop('Category', axis=1)
y = cleaned_data['Category']

# Train and evaluate traditional ML models before preprocessing
print("\nKNN Classifier (Before Preprocessing):")
knn_classifier = KNeighborsClassifier(n_neighbors=5)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=random_state_value)
train_and_evaluate_ml(knn_classifier, X_train, X_test, y_train, y_test)

print("\nDecision Tree Classifier (Before Preprocessing):")
dt_classifier = DecisionTreeClassifier(random_state=random_state_value)
train_and_evaluate_ml(dt_classifier, X_train, X_test, y_train, y_test)

print("\nRandom Forest Classifier (Before Preprocessing):")
rf_classifier = RandomForestClassifier(random_state=random_state_value)
train_and_evaluate_ml(rf_classifier, X_train, X_test, y_train, y_test)

print("\nSVM Classifier (Before Preprocessing):")
svm_classifier = SVC()
train_and_evaluate_ml(svm_classifier, X_train, X_test, y_train, y_test)

# Evaluate neural network before preprocessing
print("\nNeural Network Classifier (Before Preprocessing):")
label_encoder = LabelEncoder()
y_numeric = label_encoder.fit_transform(y)
num_classes = len(label_encoder.classes_)
X_train_nn, X_test_nn, y_train_nn, y_test_nn = train_test_split(X, y_numeric, test_size=0.2, random_state=random_state_value)
imputer_nn = SimpleImputer(strategy='mean')
X_train_imputed_nn = pd.DataFrame(imputer_nn.fit_transform(X_train_nn), columns=X_train_nn.columns)
X_test_imputed_nn = pd.DataFrame(imputer_nn.transform(X_test_nn), columns=X_test_nn.columns)
model_nn = Sequential()
model_nn.add(Dense(128, input_dim=X_train_imputed_nn.shape[1], activation='relu'))
model_nn.add(Dense(64, activation='relu'))
model_nn.add(Dense(num_classes, activation='softmax'))  # Adjust the number of output nodes
model_nn.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
train_and_evaluate_nn(model_nn, X_train_imputed_nn, y_train_nn, X_test_imputed_nn, y_test_nn)

# Preprocess data and train/evaluate traditional ML models after preprocessing
X_train, X_test, y_train, y_test = preprocess_data(X, y)

print("\nKNN Classifier (After Preprocessing):")
train_and_evaluate_ml(knn_classifier, X_train, X_test, y_train, y_test)

print("\nDecision Tree Classifier (After Preprocessing):")
train_and_evaluate_ml(dt_classifier, X_train, X_test, y_train, y_test)

print("\nRandom Forest Classifier (After Preprocessing):")
train_and_evaluate_ml(rf_classifier, X_train, X_test, y_train, y_test)

print("\nSVM Classifier (After Preprocessing):")
train_and_evaluate_ml(svm_classifier, X_train, X_test, y_train, y_test)

# Preprocess data for the neural network model
X_train_nn, X_test_nn, y_train_nn, y_test_nn = preprocess_data(X, y)

# Build and evaluate the neural network model
print("\nNeural Network Classifier (After Preprocessing):")
model_nn = Sequential()
model_nn.add(Dense(128, input_dim=X_train_nn.shape[1], activation='relu'))
model_nn.add(Dense(64, activation='relu'))
model_nn.add(Dense(num_classes, activation='softmax'))  # Adjust the number of output nodes
model_nn.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
train_and_evaluate_nn(model_nn, X_train_nn, y_train_nn, X_test_nn, y_test_nn)
model_nn.summary()
