# System-Programming-with-Linux-Assignment-5
This program serves as a shell interface. The shell interface accepts user commands and then executes a separate process. In response to the user, the command prompt is entered as follows, then the system waits for the user to enter the command and the entered command is executed.

Another special feature of the project is that it supports a special history command. For example, the most commonly used 10 commands are listed together when you press the up arrow key.

You can also press tab button to auto-complete commands.


### Commands
- sudo apt-get install libreadline-dev 
- gcc -o myshell myshell.c -lreadline
- ./myshell


### Features
- Press up arrow key to show the last 10 commands you entered.
- Auto complete support on the press of tab.
- Take user variables and Save them.
- You can Export multiple variables in the same line ex: $export x y z
