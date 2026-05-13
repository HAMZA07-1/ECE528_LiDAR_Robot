import serial
import time

PORT = "/dev/serial0"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)

print("UART test started")
print("Commands: F L R B U S")

try:
    while True:
        cmd = input("Enter command: ").strip().upper()

        if not cmd:
            continue

        cmd = cmd[0]

        if cmd not in ["F","L","R","B","U","S"]:
            print("Invalid")
            continue

        ser.write(cmd.encode())
        print("Sent:", cmd)

except KeyboardInterrupt:
    print("Stopping...")
    ser.write(b"S")

finally:
    ser.close()
