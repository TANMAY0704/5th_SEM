# main_script.py
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.impute import SimpleImputer
from imblearn.over_sampling import SMOTE
from sklearn.preprocessing import PolynomialFeatures, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline


random_state_value = 42
# Updated load_data and clean_data functions

def load_data(file_path):
    data = pd.read_csv(file_path)
    
    # Assuming 'Category' is the target variable
    X = data.drop('Category', axis=1)
    y = data['Category']

    return X, y

def clean_data(data):
    data.dropna(subset=['column_name'], inplace=True)
    if 'Unnamed: 0' in data.columns:
        data.set_index('Unnamed: 0', inplace=True)
    return data


# Modify preprocess_data function

# data_processing.py
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler, OneHotEncoder

def preprocess_data(X, y, polynomial_degree=2, random_state_value=42):
    # Convert 'y' to numeric values
    y_numeric = pd.to_numeric(y, errors='coerce')

    # Separate categorical and numerical columns
    categorical_cols = ['Sex']
    numerical_cols = X.columns.difference(categorical_cols)

    # Preprocessing pipeline
    preprocessor = ColumnTransformer(
        transformers=[
            ('num', StandardScaler(), numerical_cols),
            ('cat', OneHotEncoder(), categorical_cols)
        ])

    poly_features = PolynomialFeatures(degree=polynomial_degree, include_bias=False)

    # Create a pipeline
    pipeline = Pipeline([
        ('preprocessor', preprocessor),
        ('poly_features', poly_features)
    ])

    # Apply preprocessing
    X_poly = pipeline.fit_transform(X)

    # Split the data into training and testing sets consistently
    X_train, X_test, y_train, y_test = train_test_split(
        X_poly, y_numeric, test_size=0.2, random_state=random_state_value, stratify=y_numeric)

    # Determine the number of neighbors for SMOTE
    k_neighbors_value = min(5, len(X_train) - 1)

    # Apply SMOTE for oversampling
    smote = SMOTE(sampling_strategy='auto', k_neighbors=k_neighbors_value, random_state=random_state_value)
    X_train_resampled, y_train_resampled = smote.fit_resample(X_train, y_train)

    return X_train_resampled, X_test, y_train_resampled.values.ravel(), y_test.values.ravel()
