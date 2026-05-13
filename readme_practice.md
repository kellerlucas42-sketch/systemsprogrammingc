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
  
* The VSCode development environment was then set up using the Remote-SSH extension and then GitHub was configured to be able to utilize a repository to be able to download the future lab files to the Pi. 

* The Pi was then powered down using ```sudo shutdown now```to keep it from bugging out, and then the display was connected to the Pi and fully assembled into a doorbell. 
 

<br>

## Lab 02 - Command Line Practice
### Description

This lab was a command line challenge meant to teach how to create directories, files, and bash scripts using the terminal. 

### Usage Instructions

* First we familiarize ourselves with the basic Linux terminal commands and shortcuts.
* Then open the 02-command-line folder within the repository and check the first README which says to change the current directory to the mov directory.
* This can be done using ```cd mov```.
* Once in the mov directory use the ```ls -la``` command to find the hidden directory, which are marked with a '.' in front of their name to hide them from the normal ```ls``` command.
* Inside the sneaky.txt you are supposed to create a new directory called bannana, this can be done using ```mkdir banana```. Then you are instructed to create a file named after a fruit, with the name of a different fruit inside of it. To do this you can use ```echo grape > banana/apple.txt```.
* Then you are supposed to run the bash script called ```runme.sh```, located inside the challenge folder. 
* A file is then to be created named solution.txt and you are meant to write the command for changing permissions of a file there. ```chmod 777 runme.sh```
* Then run the bash script, runme.sh which is located inside the scripts folder. Inside the bash script you are tasked to add three commands, these could be things such as ```echo "meow meow meow"``` which will print to the terminal when the script is executed. 
* You are then tasked move to the .environs folder and to create a .sh file, which is a bash script and contains commands and can be made executable. The script should create two new variables and use them along with one system variable in a new script. This script should also create a file as an output.
* Variables in a script can be declared using ```export "variable" = "value"``` Variable can be changed to whatever, and for system variables like USER you don't want to change the value to anything because it is declared by the system.
* ```  export Hamburger=21
       export USER
       export Cheeseburger="Yummy"
       touch text.txt```
* Then navigate to the top folder and check for anything you haven't finished. Then you can do the final task. You are meant to install the package called tree and use it at the top folder to create a beautiful list of all the folders inside the "challenge" directory.
* Once the package is installed you can run the command ```tree -a```, this should create a tree.txt file that shows your full tree results. The -a flag is important as it reveals the hidden directories and files and allows them to be included in the tree.

* ```.
  ├── .admin
  │   └── runme.sh
  ├── apple
  │   └── orange.txt
  ├── mov
  │   ├── congratulations.txt
  │   └── .whats_this
  │       └── sneaky.txt
  ├── README.txt
  ├── runme.sh
  ├── scripts
  │   ├── .environs
  │   │   └── instructions.txt  
  │   ├── hamburger.sh
  │   ├── runme.sh
  │   └── text.txt
  ├── solution.txt
  └── tree.txt

  7 directories, 12 files```

*Your final result should include 7 directories and 12 files, as shown above.* 




<br>
 


## Lab 03 - Programming in C - Part 1

### Description

This lab was an introduction to programming in C, and was mostly focused on how to output values in different formats. 

### Usage Instructions

*Refer to the code block below to see how these were implemented*

* First we must create a new file called data.c, this can be done with the command ```touch data.c``` in the terminal or just creating the file within the folder on VSCode. 
  
* Then we must utilize the ```printf``` formats in C to complete the following instructions.
  
* Print out the hex equivalent of the unsigned int: 3735928559, this is done in the ```printf("%x\n", meow);``` line in the code below. This is because the %x flag prints out the integer as a hex. 
  
* Create a function that takes in a uint8_t as a parameter and prints the char equivalent. Use it at least 3 times in your main().
  
* Use the printf() function at least once that has multiple formatting specifiers/placeholders.
  
* Use at least 5 different format specifier types in 5 different printf() statements
  
* Use some format specifiers/placeholders in printf() in unexpected ways. Your program must compile. In a comment next to or above this statement, explain the behavior and why you think it works that way.

*  ```
     #include <stdio.h>
     #include <stdint.h>

      void numberer(uint8_t input)
      {
          char barf = (char) input;
          printf("%c\n", barf);
      }
      int main()
      {   // print meow as hex :3
          unsigned int meow = 3735928559;
          uint8_t donkey = 38;
          uint8_t horse = 37;
          uint8_t honkey = 39;
          numberer(donkey);
          numberer(horse);
          numberer(honkey);
          printf("%x\n", meow);
          printf("%o\n", donkey);
          printf("%d\n", horse);
          printf("%i\n", honkey);
          unsigned int barfsicle = 37373737;
          printf("%f\n", barfsicle);
          return 0;
        }
   ```

* Complile your code into an executable called data. This can be done using the ```gcc``` command. The -o flag makes the file executable. ```gcc data.c -o data```. Data becomes the name of the executable file, which can be run using ```./data```. 


<br>

## Lab 04 - Programming in C - Part 2

### Description

This was a debugging lab meant to increase understanding on how C programs work. 

### Usage Instructions

* In this lab there are several files, each with functions that either need to be debugged or written entirely.

#### First we have custom_strings.c and it's accompanying header file.
*custom_strings.c has five functions that we are expected to write: getStringLength, toUpper, findLastChar, getFileExtension, and combinePath*

* getStringLength
To implement this function we can utilize a while loop, which will increment an integer, j, as long as the string is continuing. A length variable is also set and incremented at the same time. 
```
uint32_t getStringLength(char string[]) {
    int j = 0;
    int length = 0;
    while(string[j]){
        length++;
        j++;
    }
    return length;
}
```

* toUpper
To implement this function a similar loop is used to iterate through the input and write the correct values to the output. The while loop stops at '\0' which is the null character at the end of all the strings. 

```void toUpper(char output[], char input[]) {
    int i = 0;
    while (input[i] != '\0'){
        if (input[i] >= 'a' && input[i] <= 'z')
        output[i] = input[i] - 'a' + 'A';
        else
            output[i] = input[i];
        i++;

    }
    output[i] = '\0';


}
```


#### Then we have the data.c file and it's accompanying header file.



<br>

## Lab 05 - Image Manipulation

### Description

This lab was an introduction to bitmap image manipulation using bitwise operations on pixel values. 

### Usage Instructions

< some instructions >


