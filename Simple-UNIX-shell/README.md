# UNIX Shell and History Feature

This is the first project in the second chapter of _Operating System Concepts._ It is required to recreate a simple UNIX shell that works in Linux environments. Detailed description can be found in the book.

The source code of this project can be found in the <a href="https://github.com/rafi007akhtar/oslab/blob/master/Simple-UNIX-shell/shell.c"> shell.c </a> file.

## Instructions

1. Open a terminal and enter the current folder.
	``` 
	cd Simple-UNIX-shell 
	```
2. Link the `pthreads` library and compile the program. Ignore warnings, if any.
	```
	gcc shell.c -pthread -o myShell
	```
3. Run the executable generated.
	```
	./myShell
	```

## Demo

The following GIF shows a demo of how you can use the project, once you have created and run the executable. 

**Note that this might be an old recording, and the latest version might have changed.**

![](https://raw.githubusercontent.com/rafi007akhtar/oslab/master/Simple-UNIX-shell/shell-demo.gif)

## Disclaimer

Like stated in the root README file, this program is not an official solution, nor does it exist to serve as a solution to any homework problem. Refer to it only if it helps you, but do not copy-paste my code.
