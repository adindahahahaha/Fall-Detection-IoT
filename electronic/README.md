## Introduction
Elderly individuals often experience a decline in physical functions, which limits their ability to perform daily activities. Balance disorders significantly increase the risk of falls, which can lead to severe consequences, including fatalities. Falls among elderly individuals are particularly dangerous due to the potential for complications arising from pre-existing conditions. Quick response times are crucial, as immediate medical attention within the "golden time" can prevent further health deterioration.

In Indonesia (2023):  
- **28-35%** of individuals aged 65+ experience falls annually.  
- **32-42%** of individuals aged 70+ experience falls annually.  

*Source: Salsabila, S. (2024). *Gambaran Tingkat Risiko Jatuh pada Lansia Berdasarkan Berg Balance Scale di Puskesmas Muara Dua Kota Lhokseumawe 2023* (Doctoral dissertation, Universitas Malikussaleh).*

This project aims to mitigate such risks by developing a reliable fall detection system that ensures timely assistance and reduces fatal outcomes.

## Components
1. **MPU6050 Sensor**  
   - This sensor integrates an accelerometer and a gyroscope to monitor motion and orientation.  
   - It detects falls by analyzing sudden changes in acceleration or angular velocity.  
   - **Source:** [MPU6050 Module - Components101](https://components101.com/sensors/mpu6050-module)

2. **ESP32-C6 Microcontroller with Machine Learning Implementation**  
   - The ESP32-C6 microcontroller serves as the core processing unit.  
   - A **machine learning model** is implemented on the microcontroller to enhance detection accuracy by analyzing complex motion patterns.  
   - This approach improves the reliability of fall detection, reducing false positives compared to threshold-based algorithms.  
   - **Source:** [DFRobot ESP32-C6 Beetle](https://wiki.dfrobot.com/SKU_DFR1117_Beetle_ESP32_C6)

3. **Power Source**  
   - The system is powered by a rechargeable battery, ensuring portability and ease of use.
   - **Source:** [Lithium-ion Polymer Battery - Ineltro](https://www.ineltro.ch/media/downloads/SAAItem/45/45958/2b4fb0d5-bfc7-4a45-8c2f-592265c6810f.pdf)
     
## Data Processing and Communication
- The machine learning model evaluates sensor readings directly on the ESP32-C6 to distinguish normal movements from potential falls.  
- Once a fall is detected:  
  1. The system transmits the processed data to **Firebase**, a cloud-based real-time database.  
  2. Firebase triggers a **notification** to the connected mobile application, alerting caregivers or family members.  

## Features
- Real-time fall detection and alerting.  
- Machine learning-based motion analysis for improved accuracy.  
- Lightweight and portable system design.  

## Percobaan Alat
- Integration with a mobile application for instant notifications and event history tracking.  

## Schematic Design 
The schematic design can be seen in the following image:  
![Schematic Design](https://github.com/user-attachments/assets/1dbe3850-54cb-4323-8a48-089a111acfec)  
*The schematic design was created using Fritzing.*

## Percobaan Alat
https://drive.google.com/drive/folders/11pcH7gd18HzQFJxI3yjs_2Pk5uwsSfff?usp=sharing
