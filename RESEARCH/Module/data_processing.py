# data_processing.py
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.impute import SimpleImputer
from imblearn.over_sampling import SMOTE
from sklearn.preprocessing import PolynomialFeatures

random_state_value = 42

def load_data(file_path):
    data = pd.read_csv(file_path)
    return data

def clean_data(data):
    data.dropna(inplace=True)
    data = data.drop(['Unnamed: 0'], axis=1)
    return data

def preprocess_data(X, y, polynomial_degree=2):
    y_numeric = y.str.extract('(\d+)').astype(int)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y_numeric, test_size=0.2, random_state=random_state_value)

    # Retaining 'Sex' column
    sex_train = X_train['Sex']
    sex_test = X_test['Sex']

    # Drop 'Sex' column before imputing
    X_train = X_train.drop(['Sex'], axis=1)
    X_test = X_test.drop(['Sex'], axis=1)

    imputer = SimpleImputer(strategy='mean')
    X_train_imputed = pd.DataFrame(
        imputer.fit_transform(X_train), columns=X_train.columns)
    X_test_imputed = pd.DataFrame(
        imputer.transform(X_test), columns=X_test.columns)

    # Polynomial Features
    poly_features = PolynomialFeatures(degree=polynomial_degree, include_bias=False)
    X_train_poly = poly_features.fit_transform(X_train_imputed)
    X_test_poly = poly_features.transform(X_test_imputed)

    # Concatenate 'Sex' column back to the data
    X_train_poly = pd.concat([pd.DataFrame(X_train_poly), sex_train.reset_index(drop=True)], axis=1)
    X_test_poly = pd.concat([pd.DataFrame(X_test_poly), sex_test.reset_index(drop=True)], axis=1)

    k_neighbors_value = min(5, len(X_train_poly) - 1)

    smote = SMOTE(sampling_strategy='auto', k_neighbors=k_neighbors_value, random_state=random_state_value)
    X_train_resampled, y_train_resampled = smote.fit_resample(X_train_poly, y_train)
    
    return X_train_resampled, X_test_poly, y_train_resampled.values.ravel(), y_test.values.ravel()
