# ⚡Inverter⚡
80kW (2x40kW), 600V, 3 phase inverter with FOC 

This is my Electronics Engineering bachelor thesis, a dual 40kW, 600V, 3 phase inverter. The goal is to design and implement a bidirectional inverter that is somewhat fault-tolerant. The inverter will use Field-Oriented Control, as well as having autotuning and testing features. The target power densities for the inverter are 50 kW/liter and 30 kW/kg, and it will be designed with a variety of control and power requirements in mind.

## 📁 Repository Contents
This repository contains the following files and directories:

* [🕹️ Control/](https://github.com/dweggg/Inverter/blob/main/Control/): This directory contains the MATLAB & Simulink files used to undestand and develop the FOC.
* [🛠️ HW/](https://github.com/dweggg/Inverter/blob/main/HW/): This directory contains all the design documents, such as schematics, PCB layouts, and BOM.
* [💾 SW/](https://github.com/dweggg/Inverter/blob/main/SW/): This directory contains the firmware code for the inverter, which is written in C and uses a STM32 microcontroller.

## 🛠️ Built With
### 🕹️ Control study
* [MATLAB 2022b & Simulink](https://www.mathworks.com/products/matlab.html) - Design of the vector control algorithm and general understanding of FOC

### 🛠️ HW
* [Altium Designer](www.https://www.altium.com/es/altium-designer/) - Schematics and PCB

### 💾 SW
* [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) - IDE for STM32 MCUs


## 🤝 Contributing

Please read [CONTRIBUTING.md](https://github.com/dweggg/Inverter/blob/master/CONTRIBUTING.md) Not ready for contributions yet.

## 👤 Author

* **David Redondo** - *Initial work* - [dweggg](https://github.com/dweggg)

See also the list of [contributors](https://github.com/dweggg/Inverter/contributors) who participated in this project.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## 👏 Acknowledgments

* e-Tech Racing
* UPC EEBE
* CITCEA
