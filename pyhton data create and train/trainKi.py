import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_absolute_error, r2_score
import joblib

df = pd.read_csv("TrainTest.csv")
head = df.head()
# print(head)
x = df.iloc[:, 0:3]
y = df.iloc[:, 3]
# print(x)
# print(y)

x_train, x_test, y_train, y_test = train_test_split(
    x, y, random_state=42, test_size=0.2
)

rf = RandomForestRegressor(random_state=42)
rf.fit(x_train, y_train)

y_pred = rf.predict(x_test)
mae = mean_absolute_error(y_test, y_pred)
accuracy = r2_score(y_test, y_pred) * 100
print(f"Model Accuracy (R2-Score): {accuracy:.2f} %")
print(f"Average error: +/- {mae:.2f} hours")


joblib.dump(rf, "./random_forest_hours_until_dry.joblib")
