# ECEN 225 README #1 

Author: Lucas Keller

Date: 05/13/2026


## Lab 01 - Getting Started
### Description

In this lab we set up the Raspberry Pi that will be used for the furture labs. 

### Usage Instructions

* First we flashed the SD card for the Pi. This included running a bash script to run the imager which installs the OS. 

* ```wget https://raw.githubusercontent.com/philipbl/ecen225-image/refs/heads/main/imager.sh```
  ```chmod +x imager.sh```
  ```./imager.sh```

* Then once that finished running the Pi was assembled in order to connect to it. After plugging in the Pi to the ethernet cable adapter, giving it connection and power, the Pi was pinged to check if it had connected.
```# replace NETID with your NetID ping doorbell-NETID.local``` If the command is successful then the Pi was able to connect and is online and ready to be connected to via SSH. ```ssh NETID@doorbell-NETID.local``` 

* Once logged in to the Pi the terminal should change to ZSH. And the prompt will change to ```➜ ~```.
  
* The VSCode development environment was then set up using the Remote-SSH extension. 

* Then GitHub was configured to be able to utilize a repository to be able to download the future lab files to the Pi. 

* The Pi was then powered down using ```sudo shutdown now```to keep it from bugging out, and then the display was connected to the Pi and fully assembled into a doorbell. 
 



## Lab 02 - Command Line Practice
### Description

This lab was a command line challenge meant to teach how to create directories, files, and bash scripts using the terminal. 

### Usage Instructions

First we should familiarize ourselves with the basic Linux terminal commands and shortcuts. 


## Lab 03 - Programming in C - Part 1

### Description

This lab was an introduction to programming in C, and was mostly focused on how to output values in different formats. 

### Usage Instructions

< some instructions >



## Lab 04 - Programming in C - Part 2

### Description

This was a debugging lab meant to increase understanding on how C programs work. 

### Usage Instructions

< some instructions >



## Lab 05 - Image Manipulation

### Description

This lab was an introduction to bitmap image manipulation using bitwise operations on pixel values. 

### Usage Instructions

< some instructions >


