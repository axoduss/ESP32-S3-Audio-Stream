# 🎙️ ESP32-S3 Audio Streaming System
Real-time audio streaming from ESP32-S3 with INMP441 microphone to web browser via WiFi, featuring live waveform visualization and spectrum analysis.


## 🌟 Overview

This project enables real-time audio streaming from an ESP32-S3 board with an INMP441 I2S microphone to any web browser. The system uses UDP for low-latency audio transmission from the ESP32 to a Python bridge server, which converts it to WebSocket for browser compatibility.
Perfect for:
- 🎤 Live microphone monitoring
- 📊 Audio visualization and analysis
- 🎵 DIY intercom systems
- 🔊 Remote audio sensing applications


## ✨ Features
| Feature                 | Description                                                |
| ----------------------- | -----------------------------------------------------------|
| 🎧 Real-time Audio      | Stream audio with ~100-200ms latency                       |
| 📊 Waveform Display     | Live oscilloscope-style waveform visualization             |
| 🎵 Spectrum Analyzer    | FFT-based frequency spectrum display                       |
| 💾 WAV Recording        | Record and download audio directly from browser            |
| 📈 Live Statistics      | Monitor packets, volume, and latency in real-time          |
| 🌐 Web Interface        | No app installation required - works in any modern browser |
| 🔌 Easy Setup           | Simple Python bridge server with minimal dependencies       |
	

	

## 🔧 Hardware Requirements

|      Component     | Quantity |                      Notes                      |
|------------------|:--------:|-----------------------------------------------|
| ESP32-S3 Dev Board | 1x       | Any ESP32-S3 variant (e.g., ESP32-S3-DevKitC-1) |
| INMP441 Microphone | 1x       | I2S omnidirectional MEMS microphone             |
| Jumper Wires       | 5x       | For connecting microphone to ESP32              |
| USB Cable          | 1x       | For programming and power                       |


## 🔌 Wiring Diagram

## 💻 Software Requirements
On ESP32-S3
- Arduino IDE 2.x or PlatformIO
- ESP32 Arduino Core 3.x (by Espressif)
- Libraries: WiFi, WiFiUdp 
On PC/Server
- Python 3.8+
- Dependencies: 
> pip install websockets asyncio

On Browser
- Modern Browser: Chrome, Firefox, Edge (with WebSocket & Web Audio API support)


## 🏗️ System Architecture

## 📥 Installation


## ⚙️ Configuration


## 🚀 Usage

## 📊 Performance

## 📬 Contact
For questions, issues, or suggestions, please open an issue on GitHub or contact the maintainer.
Happy Streaming! 🎧🎙️

Made with ❤️ for the maker community


