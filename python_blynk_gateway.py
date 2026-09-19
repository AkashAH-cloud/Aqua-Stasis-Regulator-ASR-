import serial
import requests

PORT = "COM3"
BAUD = 9600
TOKEN = "YOUR_BLYNK_TOKEN"

ser = serial.Serial(PORT, BAUD, timeout=1)

print("Aqua Stasis Regulator Blynk Gateway Started")

while True:
    try:
        line = ser.readline().decode("utf-8").strip()

        if not line:
            continue

        data = {}

        for item in line.split(","):
            key, value = item.split(":")
            data[key] = value

        ph = data["pH"]
        temp = data["Temp"]
        level = data["Level"]

        requests.get(
            "https://blynk.cloud/external/api/update",
            params={
                "token": TOKEN,
                "V0": ph,
                "V1": temp,
                "V2": level
            },
            timeout=5
        )

        print(f"Sent → pH={ph}, Temp={temp}, Level={level}")

    except Exception as e:
        print("Error:", e)