# STM32F4 Custom Clock Configuration & UART Debug Output

This project demonstrates how to manually configure the **STM32F4 system clocks**, switch to **external high-speed oscillator (HSE)** as system clock source, and output clock frequencies (SYSCLK, HCLK, PCLK1, PCLK2) over **USART2** using the STM32 HAL library.

 Also sets up **SysTick timer**, **enables system exceptions**, and initializes UART GPIO pins and interrupts via **MCU Support Package (MSP)**.

---

##  Features

- Configures **HSE (bypass)** as clock source and disables HSI
- Configures AHB, APB1, and APB2 clock dividers
- Initializes **USART2 (TX → PA2, RX → PA3) at 115200 baud**
- Prints clock frequencies via UART in human-readable format
- Configures **SysTick** for 1ms tick with HCLK
- Sets **NVIC priority grouping** and enables system exceptions (Usage Fault, Memory Fault, Bus Fault)
- Low-level GPIO and interrupt initialization via `HAL_UART_MspInit`

---

## 🛠️ Hardware Requirements

- STM32F4 series MCU (tested on STM32F411RE Nucleo)
- USART2 pins:
  - **TX → PA2**
  - **RX → PA3**
- USB-UART converter (or ST-Link Virtual COM) to monitor UART output

---

##  How It Works

1. Initializes HSE in **bypass mode** and switches system clock to HSE.
2. Configures AHB/APB dividers to reduce clock speed (AHB/2, APB1/2, APB2/2).
3. Initializes USART2 at **115200 baud** for debug output.
4. Prints current **SYSCLK, HCLK, PCLK1, PCLK2** frequencies via UART.
5. Configures **SysTick** to generate 1ms interrupts based on HCLK.
6. Handles low-level peripheral setup inside `HAL_MspInit` and `HAL_UART_MspInit`.

7. ##  Build & Flash

1. Open project in **STM32CubeIDE** or import `.ioc` file.
2. Build the project.
3. Flash to your STM32F4 device.
4. Open serial terminal (TeraTerm, PuTTY) at **115200 baud**, **8N1**.
5. Observe printed clock frequencies.
