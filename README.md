# AlertLens-Gunshot-Detection
AlertLens is an embedded AI system that detects gunshot sounds using a TinyML model on ESP32 and triggers an ESP32-CAM to record video locally. Built using Edge Impulse and I2S audio input, it enables real-time, offline surveillance for safety applications under a low-cost setup.
🚨 AlertLens: Gunshot-Activated Camera Trigger

AlertLens is an AI-powered safety system that uses a microphone and machine learning to detect gunshots (or other critical sounds) and automatically triggers an ESP32-CAM module to record footage for evidence or alert purposes.

🔍 Project Description

This system uses a custom-trained audio classification model (via Edge Impulse) to detect gunshots. Upon detection, an ESP32 DevKit sends a digital trigger signal to an ESP32-CAM, which captures and stores an image or video. This low-cost, real-time solution is ideal for surveillance in vulnerable environments.

⚙️ Technologies Used
	•	Embedded Machine Learning (TinyML)
	•	Edge Impulse for model training and deployment
	•	Arduino (ESP32 DevKit V1 & ESP32-CAM)
	•	Microphone with I2S Interface
	•	Serial communication trigger logic

🧠 AI Model
	•	Model type: Audio Classification (MFCC + Neural Network)
	•	Classes: gunshot, other
	•	Deployed as: Quantized/Float32 Arduino library

🛠️ Hardware Setup
	•	ESP32 DevKit V1 (runs ML inference)
	•	I2S Microphone (connected to ESP32 DevKit)
	•	ESP32-CAM (triggered via GPIO21 for image capture)
	•	Local SD card storage

🚀 How It Works
	1.	Microphone captures audio in real-time.
	2.	Edge Impulse model classifies it as gunshot or other.
	3.	If gunshot > threshold, ESP32 sets GPIO HIGH.
	4.	ESP32-CAM detects the HIGH trigger and captures an image or video.
 📁 Project Structure

 AlertLens/
├── README.md
├── .gitignore
├── Gunshot_Detection_Model/         # Edge Impulse exported library
├── AlertLens_EI_ESP32.ino           # ESP32 DevKit Code
├── AlertLens_ESP32CAM_Trigger.ino   # ESP32-CAM Capture Code
└── hardware_connections.png         # Circuit diagram

💡 Future Enhancements
	•	Integrate emergency SMS/email alerts
	•	Upload captured footage to cloud storage (Firebase/Google Drive)
	•	Detect other acoustic events like glass breaking or screaming

🤖 AI Niche

This project falls under the niche of Embedded AI / TinyML for Audio Event Detection, with applications in Edge AI and Smart Surveillance Systems.
