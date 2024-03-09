import tkinter as tk
import requests

def turn_on_led():
    url = "http://192.168.0.103/on"
    requests.get(url)

def turn_off_led():
    url = "http://192.168.0.103/off"
    requests.get(url)

# Create Tkinter window
root = tk.Tk()
root.title("ESP32 LED Control")

# Create buttons to control LED
on_button = tk.Button(root, text="Turn LED ON", command=turn_on_led)
on_button.pack(pady=20)

off_button = tk.Button(root, text="Turn LED OFF", command=turn_off_led)
off_button.pack(pady=20)

# Run Tkinter event loop
root.mainloop()
