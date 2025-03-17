# variable_message_signs

Variable Message Signs Display using STM32 & Raspberry Pi Pico

Project Overview

This project implements a Variable Message Sign (VMS) Display that can print text, images, and videos on a 256x256 HUB75 RGB LED display. The project is built using STM32 (dmd_stm32 library) and Raspberry Pi Pico, with data received through a server using the WIZnet W5500 Ethernet module.

Features

256x256 HUB75 LED Display for high-resolution graphics

Text, Images, and Video Display capabilities

Data Transmission via Ethernet using the WIZnet W5500

Server Communication for dynamic content updates

Real-time Updates for seamless message changes

STM32 with dmd_stm32 Library for efficient display control

Raspberry Pi Pico for Additional Processing

Hardware Components

STM32 Microcontroller (for HUB75 display control)

Raspberry Pi Pico (for processing and interfacing)

HUB75 256x256 LED Display

WIZnet W5500 Ethernet Module (for network communication)

Server Backend (to send data to the display)

Software Components

dmd_stm32 Library (for driving HUB75 display on STM32)

MicroPython/C++ (for Raspberry Pi Pico)

Ethernet Communication Protocol (using W5500)

Server-side Scripts (to send messages, images, and videos)

System Workflow

Server Sends Data: The server transmits text, images, or video data over Ethernet.

Raspberry Pi Pico Receives Data: The Pico processes and forwards the data.

STM32 Controls Display: The STM32 microcontroller, using the dmd_stm32 library, drives the HUB75 LED matrix.

Display Updates in Real-Time: The message sign dynamically updates based on the received content.

Installation & Setup

Set up the STM32 and upload the dmd_stm32 firmware.

Flash Raspberry Pi Pico with MicroPython/C++ code for data handling.

Connect WIZnet W5500 for Ethernet communication.

Run the server script to send display data.

Power up and test the real-time updates on the HUB75 display.
