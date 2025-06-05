# Secure-Electronic-Lock-System-on-STM32F446-Embedded-Project-with-RTOS-Integration
Modular embedded password lock built on STM32F4 with FreeRTOS, featuring interrupt-driven input, task separation, and watchdog safety.
An RTOS-based electronic lock system developed on STM32F446, featuring UART input, keypad interrupts, LED indicators, and robust task separation using FreeRTOS. This project demonstrates real-time multitasking, inter-task synchronization, and modular firmware architecture.

📂 Project Structure
stm32f4-password-lock-rtos/

├── Core/

│   ├── Inc/

│   │   ├── main.h

│   │   ├── freertos_tasks.h

│   │   ├── gpio.h

│   │   └── usart.h

│   └── Src/

│       ├── main.c

│       ├── freertos_tasks.c

│       ├── gpio.c

│       ├── usart.c

│       └── stm32f4xx_it.c

├── FreeRTOS/                ← RTOS kernel & CMSIS adapter

├── Drivers/                 ← HAL drivers

├── README.md

└── .gitignore



⚙️ Features

🟢 RTOS Task-Based Design – Modular task for password handling, LED reset, keypad monitoring, and watchdog feed

⌨️ UART Input – Password input handled via USART2 + RX interrupt

🔘 Keypad Interrupt – Triggers password change mode via EXTI line

🧠 FreeRTOS Integration – Uses CMSIS-RTOS2 API with Queue, Semaphore

💡 LED Indication – Green for success, Red for error

🛡️ Watchdog Reset – Feeds IWDG to prevent system lockup

🔄 Non-blocking ISR – ISR offloads data to tasks via inter-task queue


🛠️ Getting Started

Clone the project
git clone https://github.com/your_username/stm32f4-password-lock-rtos.git

Open in STM32CubeIDE

Connect STM32F446 Board

Build & Flash

Connect Serial Terminal (e.g., TeraTerm)

Baud rate: 9600

Input password followed by Enter

Button (PC13) triggers change-password mode


🧩 Why RTOS?

✅ Modular – Tasks are isolated and easy to extend

✅ Stable – No blocking ISR logic, handled by threads

✅ Maintainable – New features = New thread

✅ Scalable – Easy to add keypad input, EEPROM storage, UI







