# IoT-Based Fall Detection System

This project focuses on an IoT-based fall detection system that monitors and responds to falls among elderly individuals, ensuring timely alerts and interventions.

## Architecture Overview

### 1. Start
The system begins operation when the wearable device is activated. This device continuously monitors the user’s movements and orientation.

### 2. Wearable Sensors
The wearable device includes sensors:
- **Accelerometer and Gyroscope (MPU6050):** Tracks the user’s movements and orientation, collecting data on acceleration and angular velocity. This data is critical for detecting irregular motion or falls.

### 3. Microcontroller (ESP32-C6)
The microcontroller processes sensor data locally using:
- **Threshold-Based Algorithms:** Analyzes movement data to identify falls by comparing it to predefined thresholds for normal and abnormal movements.

### 4. Wearable Device Power Supply
Powered by a **LiPo 1300 mAh battery**, the wearable device operates for extended periods and resets automatically after detecting a fall to ensure uninterrupted operation.

### 5. Fall Detection Decision
- **No Fall Detected:** The system continues monitoring the user’s movements.
- **Fall Detected:** The system initiates the alert process.

### 6. Data Transmission
Upon detecting a fall, the **ESP32-C6** transmits movement data to the **Firebase cloud platform** via Wi-Fi. This ensures secure storage and processing of the data.

### 7. Firebase Cloud Platform
- **Data Analysis:** Firebase analyzes transmitted data to categorize movement patterns as **normal** or **abnormal**.
- **Real-Time Alerts:** Firebase Cloud Messaging triggers real-time alerts to notify relevant parties.

### 8. Notification and Alerts
The system:
- Notifies **family members or caregivers** through the mobile application.
- Displays a **user-friendly interface** with real-time status, history, and user profiles.

### 9. Mobile Application
The mobile app acts as the user interface, allowing caregivers or family members to:
- Receive instant notifications.
- View detailed information about the fall event.
- Access historical data and user profiles for ongoing monitoring.

### 10. End
The process concludes with the notification and response phase, ensuring timely intervention to assist the user.

## Key Features
- **Real-Time Monitoring and Alerts:** Caregivers are notified immediately of falls.
- **Local and Cloud Processing:** Combines local data processing (via ESP32-C6) with cloud-based analytics (via Firebase) for reliability and efficiency.
- **Scalability:** Designed to handle multiple users with minimal latency.
- **Power Efficiency:** Wearable device operates for extended periods with a rechargeable battery.

