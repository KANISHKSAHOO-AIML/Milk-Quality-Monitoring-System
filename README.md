Milk Quality Monitoring System 
A low-cost, portable embedded system designed to ensure milk safety for small-scale dairy farmers and household consumers.


Overview
This project uses an Arduino Uno and electronic sensors to instantly detect bacterial spoilage and estimate fat content. It provides a clear "Safe/Unsafe" status, making it accessible for non-technical users.


Features

Spoilage Detection: Uses a custom conductivity probe to detect the sharp increase in voltage caused by lactic acid in sour milk.



Fat Estimation: Utilizes an optical turbidity chamber (Green LED + LDR) to approximate fat percentage.



Instant Feedback: Displays results on a 16x2 LCD screen within 1 second.



Low Cost: Built using off-the-shelf components to ensure affordability.


Hardware Components

Microcontroller: Arduino Uno (ATmega328P) 


Display: 16x2 LCD with I2C Module 


Sensors: LDR (GL5528) and Custom Conductivity Probes 


Light Source: 5mm Green LED 

How it Works
The system initializes and reads the analog values from the sensors.


Decision 1: If conductivity > 710, the milk is flagged as "SPOILED!" and the alarm LED turns ON.



Decision 2: If conductivity is normal but fat % < 3%, it is flagged as "SKIM/WATERY".

Otherwise, the status displays "GOOD MILK".
