#!/bin/bash

if [[ $(/usr/bin/id -u) -ne 0 ]]; then
    echo "Permission denied. Need to be administrator to run"
    exit
fi

echo "Congratulations! You have almost reached the end of the challenge!"
echo " "
echo "For the last task (Task 7), install the package called tree and use it at the top folder (challenge). Make sure that tree shows ALL of the files and folders, including the hidden ones. Save the output of this command to a file called tree.txt. If you can't remember how to install something, again try asking google something like: \"How do I install tree on a rasberry pi?\" !"
