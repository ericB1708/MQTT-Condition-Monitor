import random
import pandas as pd

RANGES = {
    "temperature": {"min": 15, "max": 35},
    "humidity_in_percent": {"min": 40, "max": 100},
    "light_in_lux": {"min": 50, "max": 20000},
}


def hours_until_dirt_is_dry(temp, humidity, lux):
    CONSTPERCENTVALUE = 5

    base_Time = humidity
    temp_factor = 1
    light_factor = 1
    noise = 0
    # Für jedes Grad über 20°C zieht man 5% der Zeit ab. Für jedes Grad unter 20°C addiert man 5%.
    if temp > 20:
        temp_over = temp - 20
        factor = temp_over * CONSTPERCENTVALUE
        temp_factor = temp_factor - (factor * 0.01)
    elif temp < 20:
        temp_under = 20 - temp
        factor = temp_under * CONSTPERCENTVALUE
        temp_factor = temp_factor + (factor * 0.01)

    if lux < 500:
        light_factor = 1.2
    elif lux >= 500 and lux < 2500:
        light_factor = 1.0
    elif lux >= 2500 and lux < 10000:
        light_factor = 0.8
    elif lux >= 10000:
        light_factor = 0.6

    noise = round(random.uniform(0.9, 1.1), 2)
    print("temp factor : ", temp_factor)
    print("light factor : ", light_factor)
    print("base time : ", base_Time)
    print("noise :", noise)

    hours_without_noise = round(base_Time * temp_factor * light_factor, 2)
    hours_with_noise = round(hours_without_noise * noise, 2)
    print("hours without noise :", hours_without_noise)
    print("hours with noise :", hours_with_noise)
    return hours_with_noise


def get_random_data(count_days):
    data = {
        "temperature": [],
        "humidity_in_percent": [],
        "light_in_lux": [],
        "hours_until_dry": [],
    }
    for x in range(count_days):
        temperature = random.randint(
            RANGES["temperature"]["min"], RANGES["temperature"]["max"]
        )
        data["temperature"].append(temperature)
        humidity_in_percent = random.randint(
            RANGES["humidity_in_percent"]["min"], RANGES["humidity_in_percent"]["max"]
        )
        data["humidity_in_percent"].append(humidity_in_percent)
        light_in_lux = random.randint(
            RANGES["light_in_lux"]["min"], RANGES["light_in_lux"]["max"]
        )
        data["light_in_lux"].append(light_in_lux)
        hours_until_dry = hours_until_dirt_is_dry(
            temperature, humidity_in_percent, light_in_lux
        )
        data["hours_until_dry"].append(hours_until_dry)

    return data


def write_into_csv(data):
    df = pd.DataFrame(data)
    df.to_csv("data.csv", index=False)


data = get_random_data(400)
write_into_csv(data)
