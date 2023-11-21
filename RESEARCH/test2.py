import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score
from sklearn.preprocessing import LabelEncoder
from sklearn.impute import SimpleImputer
from imblearn.over_sampling import SMOTE
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# Load data and clean
file_path = "hcvdat0.csv"
data = pd.read_csv(file_path)
data.dropna(inplace=True)
data = data.drop(['Unnamed: 0', 'Sex'], axis=1)

X = data.drop('Category', axis=1)
y = data['Category']

# Extract numeric part from the string labels
label_encoder = LabelEncoder()
y_numeric = label_encoder.fit_transform(y)

# Split the data
X_train, X_test, y_train, y_test = train_test_split(
    X, y_numeric, test_size=0.2, random_state=42)

# Impute missing values
imputer = SimpleImputer(strategy='mean')
X_train_imputed = pd.DataFrame(imputer.fit_transform(X_train), columns=X_train.columns)
X_test_imputed = pd.DataFrame(imputer.transform(X_test), columns=X_test.columns)

# Handle class imbalance using SMOTE
k_neighbors_value = min(5, len(X_train[y_train == 1]) - 1)
smote = SMOTE(sampling_strategy='auto', k_neighbors=k_neighbors_value, random_state=42)
X_train_resampled, y_train_resampled = smote.fit_resample(X_train_imputed, y_train)

# Build the neural network model
model = Sequential()
model.add(Dense(128, input_dim=X_train_resampled.shape[1], activation='relu'))
model.add(Dense(64, activation='relu'))
model.add(Dense(5, activation='softmax'))  # 5 classes

# Compile the model
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(X_train_resampled, y_train_resampled, epochs=20, batch_size=32, verbose=1)

# Evaluate the model
y_pred_prob = model.predict(X_test_imputed)
y_pred = y_pred_prob.argmax(axis=1)
print("Neural Network Classification Report:")
print(classification_report(y_test, y_pred))
print("Neural Network Accuracy:", accuracy_score(y_test, y_pred))
