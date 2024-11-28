#  Electronics: Fall Detection System

This project focuses on the development of a fall detection system for the elderly, utilizing advanced electronic components, cloud-based data management, and a mobile application for real-time monitoring.

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

2. **ESP32-C6 Microcontroller with Machine Learning Implementation**  
   - The ESP32-C6 microcontroller serves as the core processing unit.  
   - A **machine learning model** is implemented on the microcontroller to enhance detection accuracy by analyzing complex motion patterns.  
   - This approach improves the reliability of fall detection, reducing false positives compared to threshold-based algorithms.

3. **Power Source**  
   - The system is powered by a rechargeable battery, ensuring portability and ease of use.

4. **Mobile Application for Monitoring**  
   - A mobile application is used to monitor the system in real time.  
   - It provides notifications of fall incidents and maintains a **history of fall events**, enabling caregivers to track patterns and offer better care.

## Data Processing and Communication
- The machine learning model evaluates sensor readings directly on the ESP32-C6 to distinguish normal movements from potential falls.  
- Once a fall is detected:  
  1. The system transmits the processed data to **Firebase**, a cloud-based real-time database.  
  2. Firebase triggers a **notification** to the connected mobile application, alerting caregivers or family members.  

## Features
- Real-time fall detection and alerting.  
- Machine learning-based motion analysis for improved accuracy.  
- Lightweight and portable system design.  
- Integration with a mobile application for instant notifications and event history tracking.  

## Scematic Design 
The schematic design can be seen in the following image: ![Schematic Design](https://github.com/user-attachments/assets/43a23409-976c-47a9-b0d9-8fc2375d2083)
