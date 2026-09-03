import joblib
import pandas as pd

loaded_rf = joblib.load("random_forest_hours_until_dry.joblib")

# print(x)
# print(y)


def predict_data(values):

    df_actual = pd.DataFrame([values])

    expected_features = ['temperature', 'humidity_in_percent', 'light_in_lux']
    df_actual = df_actual[expected_features]
    y_pred = loaded_rf.predict(df_actual)
    return round(y_pred[0],2)
