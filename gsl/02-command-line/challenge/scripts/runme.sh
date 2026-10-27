#!/bin/bash
# The line above lets the shell know which program will run the script. Other environments that support this preamble are zsh, sh, and even python! It allows you to run a script simply with the ./<file-name> or "./runme.sh" in this case.

echo "This is a script file. It acts as a file that runs a list of commands."
echo "If you open me up, you can see"
echo "That there are three echo commands that are printing out this message, one right after another."

# You can also see that .sh files support comments. Any line with a # at the front will not be executed by the shell

# Task 5 (of 7): Beneath this comment, write three different commands to be executed in this script. They each should have some sort of output that is visible when run. Once this is done, go to the hidden directory inside this folder. 
cat runme.sh
echo "meow meow meow"
echo "cheeseburger"