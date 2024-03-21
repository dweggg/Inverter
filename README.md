<div align="center" style="background-color:#1a1a1a;padding:20px;">
  <img src="https://i.ibb.co/mR0yFfw/logo-daurat-10-anys.png" width="400" alt="e-Tech Racing Logo">
</div>

<div align="center" style="background-color:#1a1a1a;padding:20px;">

[![Status](https://img.shields.io/badge/Status-Active-green)](https://github.com/dweggg/Inverter)
[![Version](https://img.shields.io/badge/Version-v0.1.pre-red)](https://github.com/dweggg/Inverter/releases)
[![License](https://img.shields.io/badge/License-CC--BY--NC--SA--4.0-yellow)](https://github.com/dweggg/Inverter/blob/main/LICENSE.md)

[![e-Tech Racing's GitHub](https://img.shields.io/badge/e--Tech%20Racing's%20GitHub-eTechRacing-green?style=for-the-badge&logo=github)](https://github.com/eTechRacing)
[![Visit Our Website](https://img.shields.io/badge/Visit%20Our%20Website-e--techracing.es-blue?style=for-the-badge)](https://www.e-techracing.es)

</div>

# ⚡ Inverter ⚡
## SiC based, dual 80kW (2x40kW), 600V, 3 phase traction inverter with FOC

This is my Electronics Engineering bachelor thesis, a SiC based, dual 80kW (2x40kW), 600V, 3 phase inverter. The goal is to design and implement a dual bidirectional inverter. The inverter will use field-oriented control, and will implement testing features and a variety of protections, alarms and extras. The target power densities for the inverter are 30 kW/liter and 20 kW/kg, and it will be designed specifically for a Formula Student vehicle. It will be able to control two PMSMs and communicate via CAN with the vehicle in order to get the torque references from the Main ECU and send all relevant information for the car.

## 📁 Repository Contents
This repository contains the following files and directories:

* [🕹️ Control/](https://github.com/dweggg/Inverter/blob/main/Control/): This directory contains the MATLAB / Simulink & PLECS files used to understand and develop the FOC.
* [🛠️ HW/](https://github.com/dweggg/Inverter/blob/main/HW/): This directory contains all the design documents, such as schematics, PCB layouts, and BOM.
* [💾 SW/](https://github.com/dweggg/Inverter/blob/main/SW/): This directory contains the firmware code for the inverter, which is written in C and uses an STM32 microcontroller.

- [🧠 Wiki](https://github.com/dweggg/Inverter/wiki): Here we explain everything related to the development of the inverter, from the mathematical basis, hardware design, software implementation, and car integration.

## 🛠️ Built With
### 🕹️ Control study
* [MATLAB 2022b & Simulink](https://www.mathworks.com/products/matlab.html) - Design of the vector control algorithm and general understanding of FOC. Some scripts for calculations, etc. done in MATLAB
* [PLECS](https://www.plexim.com/products/plecs) - Validation of the control algorithm with thermals and switching

### 🛠️ HW
* [Altium Designer](https://www.altium.com/es/altium-designer) - Schematics and PCB
* [SOLIDWORKS 2022](https://help.solidworks.com/2022/spanish/WhatsNew/c_wn_install.htm?id=7ddf806d182541ffa399d655bb1f99a2#Pg0) - Mechanical assembly
* [Python](https://www.python.org/) - Array sizing / value finding with itertools
* [OrCAD PSPICE](https://www.orcad.com/pspice) - SPICE simulation for TI components
* [LTSpice](https://www.analog.com/en/resources/design-tools-and-calculators/ltspice-simulator.html) - SPICE simulation for LT/AD components

### 💾 SW
* [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) - IDE for STM32 MCUs

## 👤 Author

* **David Redondo** - *Initial work* - [dweggg](https://github.com/dweggg)

See also the list of [contributors](https://github.com/dweggg/Inverter/contributors) who participated in this project.

## 📄 License

This project is licensed under the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License (CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/).

- **Attribution (BY)**: You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  
- **Non-Commercial (NC)**: You may not use the material for commercial purposes. I will go after you if you do, this is an educational project.
  
- **ShareAlike (SA)**: If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

## 👏 Acknowledgments

* e-Tech Racing
* UPC EEBE
* CITCEA - UPC
