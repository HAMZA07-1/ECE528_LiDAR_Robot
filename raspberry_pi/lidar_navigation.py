import subprocess
import serial
import time

LIDAR_PROGRAM = "/home/pi/rplidar_sdk/output/Linux/Release/simple_grabber"
LIDAR_PORT = "/dev/ttyUSB0"
LIDAR_BAUD = "460800"

MSP432_PORT = "/dev/serial0"
MSP432_BAUD = 115200

FRONT_THRESHOLD = 180
SIDE_THRESHOLD = 180
OPEN_DISTANCE = 300

LOOP_DELAY = 0.3

ser = serial.Serial(MSP432_PORT, MSP432_BAUD, timeout=1)

def safe_min(values):
    return min(values) if values else 9999

def send_cmd(cmd):
    ser.write(cmd.encode())
    print("Sent:", cmd)

print("LiDAR navigation started")

try:
    while True:

        proc = subprocess.Popen(
            [
                "stdbuf", "-oL",
                LIDAR_PROGRAM,
                "--channel",
                "--serial",
                LIDAR_PORT,
                LIDAR_BAUD
            ],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            text=True
        )

        time.sleep(0.4)

        try:
            proc.stdin.write("y\n")
            proc.stdin.flush()
        except:
            proc.terminate()
            continue

        front = []
        left = []
        right = []

        for line in proc.stdout:

            if not line.startswith("theta:"):
                continue

            try:
                parts = line.split()
                angle = float(parts[1])
                dist = float(parts[3])
            except:
                continue

            if dist == 0:
                continue

            if angle >= 340 or angle <= 20:
                front.append(dist)
            elif 60 <= angle <= 120:
                left.append(dist)
            elif 240 <= angle <= 300:
                right.append(dist)

        proc.terminate()

        f = safe_min(front)
        l = safe_min(left)
        r = safe_min(right)

        print(f"F:{f:.0f} L:{l:.0f} R:{r:.0f}")

        if f > OPEN_DISTANCE:
            cmd = "F"
        else:
            if r > l:
                cmd = "R"
            elif l > r:
                cmd = "L"
            else:
                cmd = "U"

        send_cmd(cmd)

        time.sleep(LOOP_DELAY)

except KeyboardInterrupt:
    print("Stopping...")

finally:
    ser.write(b"S")
    ser.close()
