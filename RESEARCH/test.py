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
        y_train_resampled.values.ravel(),  # Convert to numpy array
        y_test.values.ravel()  # Convert to numpy array
    )



def train_and_evaluate(classifier, X_train, X_test, y_train, y_test):
    classifier.fit(X_train, y_train)
    predictions = classifier.predict(X_test)
    print("Classification Report:")
    print(classification_report(y_test, predictions, zero_division=1))
    print("Accuracy:", accuracy_score(y_test, predictions))

file_path = "hcvdat0.csv"
data = load_data(file_path)
cleaned_data = clean_data(data)
X = cleaned_data.drop('Category', axis=1)
y = cleaned_data['Category']

# Train and evaluate KNN before preprocessing
print("\nKNN Classifier (Before Preprocessing):")
knn_classifier = KNeighborsClassifier(n_neighbors=5)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)
train_and_evaluate(knn_classifier, X_train, X_test, y_train, y_test)

# Train and evaluate Decision Tree before preprocessing
print("\nDecision Tree Classifier (Before Preprocessing):")
dt_classifier = DecisionTreeClassifier(random_state=42)
train_and_evaluate(dt_classifier, X_train, X_test, y_train, y_test)

# Train and evaluate Random Forest before preprocessing
print("\nRandom Forest Classifier (Before Preprocessing):")
rf_classifier = RandomForestClassifier(random_state=42)
train_and_evaluate(rf_classifier, X_train, X_test, y_train, y_test)

# Train and evaluate SVM before preprocessing
print("\nSVM Classifier (Before Preprocessing):")
svm_classifier = SVC()
train_and_evaluate(svm_classifier, X_train, X_test, y_train, y_test)

# Preprocess data and train/evaluate models
X_train, X_test, y_train, y_test = preprocess_data(X, y)

# Train and evaluate KNN after preprocessing
print("\nKNN Classifier (After Preprocessing):")
train_and_evaluate(knn_classifier, X_train, X_test, y_train, y_test)

# Train and evaluate Decision Tree after preprocessing
print("\nDecision Tree Classifier (After Preprocessing):")
train_and_evaluate(dt_classifier, X_train, X_test, y_train, y_test)

# Train and evaluate Random Forest after preprocessing
print("\nRandom Forest Classifier (After Preprocessing):")
train_and_evaluate(rf_classifier, X_train, X_test, y_train, y_test)

# Train and evaluate SVM after preprocessing
print("\nSVM Classifier (After Preprocessing):")
train_and_evaluate(svm_classifier, X_train, X_test, y_train, y_test)
