# System-Programming-with-Linux-Assignment-5
## Introduction
This program serves as a shell interface. The shell interface accepts user commands and then executes a separate process. In response to the user, the command prompt is entered as follows, then the system waits for the user to enter the command and the entered command is executed.



## Functionality and Limitations
The Shell supports the following features:

### Built-in commands and Features: 
- `echo`
- `cd`
- `exit`
- `set` print local variables 
- `export` export local variables,ex: $export x y ,
- A prompt that shows the username, hostname and the current working directory
- history and <kbd>up</kbd> arrow command recall across sessions
- Press up arrow key to show the last 10 commands you entered.
- Auto complete support on the press of <kbd>tab</kbd>.
- Take user variables and Save them.
- You can Export multiple variables in the same line 
- I/O Redirection using <kbd>></kbd> and <kbd><</kbd>.
- Appropriate error handling

### Limitations to be Implemented
- Error Redirection isn't implemented
- I/O Redirection for build-in commands like `echo` isn't implemented yet
- Aliasing
- User profiles
- Piping
- Signal handling for signals like  <kbd>SIGINT</kbd> and  <kbd>SIGTSTP</kbd>.
- Process management including foreground and background processes and switching between them.

### Make instructions
```
$ sudo apt-get install libreadline-dev 
$ make
$ cd objects/executables
$ ./myshell
```
### To clean up object and binary files, execute:
```
$ make clean
```




### Video
https://youtu.be/P-wtWxcEG6Y
