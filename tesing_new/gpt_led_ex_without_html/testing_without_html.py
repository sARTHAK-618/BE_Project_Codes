import tkinter as tk
import requests

def toggle_led():
    url = "http://192.168.0.103"
    requests.get(url)

# Create Tkinter window
root = tk.Tk()
root.title("ESP32 LED Control")

# Create a button to toggle LED
led_button = tk.Button(root, text="Toggle LED", command=toggle_led)
led_button.pack(pady=20)

# Run Tkinter event loop
root.mainloop()
