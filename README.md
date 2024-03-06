| Supported Targets | ESP32 NodeMCU Module |
| ----------------- | -------------------- |

# _B31DG_Assignment1_

About the project: This is a project based on Assignment 1 of B31DG, it aims to  generate a sequence of signals based on the input from two buttons. 

- It uses the Arduino or ESP-IDF to control GPIOs on an ESP32 board.
- The timing of signals can be adjusted for production or debugging

## Example folder contents

Below is short explanation of remaining files in the project folder.

```
|   .gitignore
|   CMakeLists.txt
|   README.md
|
+---docs
|       B31DG-Assignment1-H00364918-Shiyu Lu.pdf
|       【Requirement】B31DG - Assignment 1 - v1.0.pdf
|
+---src
|   +---Adurino_main
|   |   \---Coursework_Adurino
|   |           Coursework_Adurino.ino
|   |
|   \---main
|           CMakeLists.txt
|           main.c
|
+---tools
|   +---Task_Board_Blink_Demo
|   |       Task_Board_Blink_Demo.ino
|   |
|   \---Test_Button
|           Test_Button.ino
|
\---video
        demonstration_video.mp4
```

- **B31DG-Assignment1-H00364918-Shiyu Lu.pdf** is the report of this repository。
- **demonstration_video.mp4** is the demo video of actually running the program on the ESP32 board and showing it through an oscilloscope
- **Coursework_Arduino.ino** is the code for Arduino IDE
- **main.c** is the code for ESP-IDF extension
- **tools** contains test programs to test whether the ESP32 board is working properly and whether the buttons are working properly

