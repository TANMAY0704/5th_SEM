import pandas as pd
from sklearn.preprocessing import LabelEncoder
from imblearn.over_sampling import SMOTE
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import train_test_split

# Load the dataset
df = pd.read_csv('hcvdat0.csv')

# Check for missing values
df = df.dropna()

# Encode categorical variables
label_encoder = LabelEncoder()
df['Category'] = label_encoder.fit_transform(df['Category'])
df['Sex'] = label_encoder.fit_transform(df['Sex'])

# Apply SMOTE for balancing classes
X = df.drop(['Unnamed: 0', 'Category'], axis=1)  
y = df['Category']  
smote = SMOTE(random_state=42)
X_resampled, y_resampled = smote.fit_resample(X, y)

# Build a simple model for multiclass classification
model = Sequential()
model.add(Dense(units=len(np.unique(y)), activation='softmax', input_dim=X_resampled.shape[1]))

# Compile and fit the model
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
model.fit(X_resampled, y_resampled, epochs=10, batch_size=32, validation_split=0.2)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X_resampled, y_resampled, test_size=0.2, random_state=42)

# Evaluate the model on the test data
y_pred_prob = model.predict(X_test)
y_pred = np.argmax(y_pred_prob, axis=1)

# Print classification report
print("Classification Report:")
print(classification_report(y_test, y_pred, labels=np.unique(y), target_names=label_encoder.classes_))

# Print confusion matrix
print("Confusion Matrix:")
print(confusion_matrix(y_test, y_pred))
