import joblib
import pandas as pd

loaded_rf = joblib.load("random_forest_hours_until_dry.joblib")


df = pd.read_csv("testData.csv")
head = df.head()
# print(head)
x = df.iloc[:, 0:3]
print(x)
# print(x)
# print(y)
y_pred = loaded_rf.predict(x)

print(y_pred)
