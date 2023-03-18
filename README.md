# Inverter
40kW, 600V, 3 phase inverter with FOC

This is my Electronics Engineering final project, a 40kW, 600V, 3 phase inverter. The goal is to design and implement a bidirectional power inverter that is fault-tolerant. The inverter will use Field-Oriented Control, and will be capable of operating in both sensored and sensorless modes, as well as having autotuning and testing features. The target power densities for the inverter are 50 kW/liter and 30 kW/kg, and it will be designed with a variety of control and power requirements in mind. A desktop application will be developed in C++ using Qt and Boost libraries, and will enable live plots, serial communication, and data logging for monitoring the inverter states.

## Repository Contents
This repository contains the following files and directories:

* ´HW/´: This directory contains all the design documents, such as schematics, PCB layouts, and BOM.
* ´FW/´: This directory contains the firmware code for the inverter, which is written in C and uses a PIC32MK microcontroller.
* ´app/´: This directory contains the C++ code for the desktop application, which is developed using the Qt and Boost libraries.
* ´README.md´: This file is the README you are currently reading, which provides an overview of the project and repository contents.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

### Installing

A step by step series of examples that tell you how to get a development environment running

## Deployment

Add additional notes about how to deploy this on a live system

## Built With
### Control study
* [MATLAB 2022b & Simulink](https://www.mathworks.com/products/matlab.html) - Design of the vector control algorithm and general understanding of FOC

### HW
* [KiCad EDA](https://www.kicad.org/) - Schematics and PCB

### FW
* [MPLAB X w/ Harmony](https://www.microchip.com/en-us/tools-resources/configure/mplab-harmony) - IDE for PIC32 MCUs

### Desktop App
* [Qt](https://www.qt.io/) - C++ framework used for the desktop application
* [Boost](https://www.boost.org/) - C++ libraries used for the desktop application

## Contributing

Please read [CONTRIBUTING.md](https://github.com/username/projectname/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **David Redondo** - *Initial work* - [dweggg](https://github.com/dweggg)

See also the list of [contributors](https://github.com/dweggg/Inverter/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* e-Tech Racing
* UPC EEBE
* CITCEA
