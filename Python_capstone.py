"""
The Python script is designed to communicate with an Arduino device, sending specific 
commands and reading back sensor data sent from the Arduino. The Arduino sketch has
functionality for reading from flow and pressure sensors, controlling servo positions 
based on commands received via Serial communication, and sending the sensor data back 
through Serial. This design is meant to work together, with the Python script acting
as a user interface and command center, while the Arduino handles direct interaction 
with the hardware.

Must install this first : pip install pyserial where the VSC is located
"""

import serial
import time
import serial.tools.list_ports
from datetime import datetime
import os

# List available COM ports and allow the user to select the Arduino's COM port
ports = serial.tools.list_ports.comports()
portsList = []

print("Available COM Ports:")
for one in ports:
    portsList.append(str(one))
    print(str(one))

com = input("Select COM Port for Arduino (e.g., 3 for COM3): ")

global use
use = ""

for i in range(len(portsList)):
    if portsList[i].startswith("COM" + str(com)):
        use = "COM" + str(com)
        print("Selected port:", use)
        print("Please select the same port in the Arduino UI!")
        print()
        break

if use == "":
    print("COM port not found. Please check the connection and try again.")
    print()
    exit()

# Setup serial connection with the selected COM port
ser = serial.Serial(use, 9600, timeout=1)
time.sleep(2)  # Wait for the connection to establish 

def request_sensor_data():
    ser.write("READ\n".encode())
    while ser.in_waiting <= 0:
        time.sleep(0.1)
    data = ser.readline().decode().strip()
    return data

def update_conditions(servo1, servo2, servo3, pump_rate_left, pump_rate_right, fluid_temp):
    command = f"{servo1},{servo2},{servo3},{pump_rate_left},{pump_rate_right},{fluid_temp}\n"
    ser.write(command.encode())
    return servo1, servo2, servo3, pump_rate_left, pump_rate_right, fluid_temp

def collect_and_send_conditions():
    servo1 = input("Enter servo PV position (0-100%): ")
    servo2 = input("Enter servo CR1 position (0-100%): ")
    servo3 = input("Enter servo CR2 position (0-100%): ")
    pump_rate_left = input("Enter left pump rate (L/min): ")
    pump_rate_right = input("Enter right pump rate (L/min): ")
    fluid_temp = input("Enter fluid temperature in Celsius: ")
    return servo1, servo2, servo3, pump_rate_left, pump_rate_right, fluid_temp

def format_table(conditions, sensor_data=",,,,,"):
    # Formats conditions and sensor data into a table format. If sensor_data is not provided, leaves blanks.
    flow1, flow2, flow3, pressure1, pressure2, pressure3 = sensor_data.split(',')
    servo1, servo2, servo3, pump_rate_left, pump_rate_right, fluid_temp = conditions
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    output = (
        f"Timestamp: {timestamp}\n"
        f"Port selected: {use}\n"
        "Output Name                  | Reading\n"
        "-----------------------------|----------------\n"
        f"Servo PV Openness (%)        | {servo1}\n"
        f"Servo CR1 Openness (%)       | {servo2}\n"
        f"Servo CR2 Openness (%)       | {servo3}\n"
        f"Left Pump Rate (L/min)       | {pump_rate_left}\n"
        f"Right Pump Rate (L/min)      | {pump_rate_right}\n"
        f"Fluid Temperature (°C)       | {fluid_temp} \n"
        f"FL1 Rate (L/min)             | {flow1}\n"
        f"FL2 Rate (L/min)             | {flow2}\n"
        f"FL3 Rate (L/min)             | {flow3}\n"
        f"P1 Pressure (mmHg)           | {pressure1}\n"
        f"P2 Pressure (mmHg)           | {pressure2}\n"
        f"P3 Pressure (mmHg)           | {pressure3}\n"
        "-----------------------------|----------------\n"
    )
    return output

def beta_run(conditions):
    # Simulate the operation without Arduino communication
    output = format_table(conditions,'-,-,-,-,-,-')
    print(output)
    print()
    return output

def main():
    # Setup initial conditions
    conditions = collect_and_send_conditions()

    # Get the directory of the current script
    script_dir = os.path.dirname(os.path.realpath(__file__))
    
    # Filename for storing the output, ensuring it's created in the same folder as the script
    filename = os.path.join(script_dir, datetime.now().strftime("Output - %Y-%m-%d - %Hh%Mm%Ss.txt"))
    
    while True:
        print("\n1. Get sensor readings")
        print("2. Update inputted conditions")
        print("3. Beta run")
        print("4. Exit")
        print()
        user_choice = input("What would you like to do? ")
        print()

        if user_choice == '1':
            # Request sensor data and print it
            sensor_data = request_sensor_data()
            output = format_table(conditions, sensor_data)
            print(output)
            print()
            with open(filename, "a") as file:
                file.write(output + "\n")
            print("Sensor data received successfully!")
            print()
        elif user_choice == '2':
            # Update conditions
            conditions = collect_and_send_conditions()
            print("Conditions updated successfully!")
            print()
        elif user_choice == '3':
            # Beta run
            output = beta_run(conditions)
            with open(filename, "a") as file:
                file.write(output + "\n")
            print("Beta run executed successfully!")
            print()
        elif user_choice == '4':
            # Exit the program
            print("Exiting.")
            print()
            return
        else:
            print("Invalid input. Please enter a valid option.")
            print()

if __name__ == "__main__":
    main()


